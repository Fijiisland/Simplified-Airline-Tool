#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <QString>
#include <string>
#include <QMessageBox>
#include <QFont>
#include <QPropertyAnimation>
#include <QIcon>
using std::stringstream;
using std::string;

string cntBlanks(string &e);
string cntBlanks(int &e);

int cntLenInt(int num);
int cmp(const Airplane &x, const Airplane &y);
QString _format(const Airplane *tmp);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮
    //setWindowFlags(Qt::FramelessWindowHint);                        // 设置窗口无边框
    setFixedSize(this->width(),this->height());                     // 禁止拖动窗口大小
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->pushButton_read->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->pushButton_search->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->progressBar->setRange(1,100000);
    ui->progressBar->setVisible(false);
    QIcon icon;
    icon.addFile(tr(":/new/prefix1/btn.png"));
    ui->pushButton_read->setIcon(icon);
    ui->pushButton_search->setIcon(icon);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(setProgressVis()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::on_pushButton_read_clicked()
{
    if(ui->textBrowser_main->document()->isEmpty()){
        using std::fstream;
        const char *path = "D://info.txt";
        fstream fs;
        try {
            fs.open(path, fstream::in);
            if(!fs)
                QMessageBox::information(this, "啊哦", "你并没有在D盘创建相应文件哦", QMessageBox::Yes, QMessageBox::Yes);
            else{
                ui->progressBar->setVisible(true);
                ui->progressBar->setMinimum(0);
                ui->progressBar->setMaximum(0);
                timer->start(3500);
                ui->textBrowser_main->append("num        start      end        period     offT       arrT       model      price      ");
                QFont font;
                font.setBold(true);
                font.setPointSize(10);
                ui->textBrowser_welcome_2->append("Please input an airline sequence to search.");
                ui->textBrowser_welcome_2->setFont(font);
                string line, t;
                stringstream ss;
                std::vector<std::string> storage;
                while (getline(fs, line)) {
                    ss << line;
                    while (ss >> t)
                        storage.push_back(t);
                    Airplane airtmp(storage[0], storage[1], storage[2], storage[3],
                        stoi(storage[4]), stoi(storage[5]), storage[6],
                        stoi(storage[7]));
                    planes.push_back(airtmp);
                    ui->textBrowser_main->append(_format(&airtmp));
                    ss.clear();
                    ss.str("");
                    storage.clear();
                }
            }
        }
        catch (const fstream::failure &e) {
            std::cout << e.what() << std::endl;
        }
        std::sort(planes.begin(), planes.end(), cmp);
    }
}

void MainWindow::on_pushButton_search_clicked()
{
    if(!ui->lineEdit_search->text().isEmpty()){
        if(!ui->textBrowser_minor->document()->isEmpty())
            ui->textBrowser_minor->setText("");
        ui->progressBar->setMinimum(1);
        ui->progressBar->setMaximum(100000);
        ui->progressBar->setVisible(true);
        ui->progressBar->setValue(1);
        for(int i = 1;i < 100000;i ++)
            ui->progressBar->setValue(i);
        QString str = ui->lineEdit_search->text();
        ui->lineEdit_search->setText("");
        const Airplane *tmp = bSearch(str.toStdString());
        if (tmp) {
            str = "num        start      end        period     offT       arrT       model      price      ";
            ui->textBrowser_minor->append(str);
            ui->textBrowser_minor->append(_format(tmp));
        }
        else
            ui->textBrowser_minor->append("Sorry, cannot find it!");
    }
}

int cmp(const Airplane &x, const Airplane &y){
    return x.airNum < y.airNum;
}

const Airplane* MainWindow::bSearch(std::string tnum) {
    int left = 0;
    int right = planes.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (planes[mid].airNum == tnum)
            return &planes[mid];
        else if (planes[mid].airNum < tnum)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return nullptr;
}

int cntLenInt(int num){
    int cnt = 0;
    while(num != 0){
        num /= 10;
        cnt ++;
    }
    return cnt;
}

string cntBlanks(const int &e){
    const unsigned WIDTH = 11;
    int wordL = cntLenInt(e);
    return string(WIDTH - wordL, ' ');
}
string cntBlanks(const string &e){
    const unsigned WIDTH = 11;
    int wordL = e.length();
    return string(WIDTH - wordL, ' ');
}

QString _format(const Airplane *tmp){
    stringstream s;
    s << tmp->airNum << cntBlanks(tmp->airNum) << tmp->start   << cntBlanks(tmp->start)
      << tmp->end    << cntBlanks(tmp->end)    << tmp->period  << cntBlanks(tmp->period)
      << tmp->offT   << cntBlanks(tmp->offT)   << tmp->arriveT << cntBlanks(tmp->arriveT)
      << tmp->model  << cntBlanks(tmp->model)  << tmp->price   << cntBlanks(tmp->price);
    return QString::fromLocal8Bit(s.str().c_str());
}

void MainWindow::setProgressVis(){
    ui->progressBar->setVisible(false);
}
