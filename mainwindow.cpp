#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "_utility.h"       // 自定义算法包

#include <fstream>
#include <sstream>
#include <algorithm>

#include <QMessageBox>
#include <QFont>
#include <QString>
#include <QIcon>
#include <QDebug>
#include <QFontDatabase>
#include <QScrollBar>
#include <QGraphicsDropShadowEffect>
#include <QPainter>

using std::stringstream;
using std::string;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(this->width(),this->height());                     // 设置窗口大小固定

    this->setAttribute(Qt::WA_TranslucentBackground);//特别注意这句

    int fontID = QFontDatabase::addApplicationFont(tr(":/font/InfoDisplayWeb_Bold.ttf"));
    QString msyh = QFontDatabase::applicationFontFamilies(fontID).at(0);
    ui->label->setFont(QFont(msyh, 13));
    ui->label_2->setFont(QFont(msyh, 13));
    ui->label_3->setFont(QFont(msyh, 13));
    ui->label->setStyleSheet("color:#8B8386;");
    ui->label_2->setStyleSheet("color:#8B8386;");
    ui->label_3->setStyleSheet("color:#8B8386;");

    myFont = new QFont("Courier New", 9, QFont::Bold);
    ui->pushButton_read->setFont(*myFont);
    ui->pushButton_search->setFont(*myFont);
    myFont->setPointSize(8);
    myFont->setBold(false);
    ui->label_right->setFont(*myFont);
    myFont->setPointSize(9);

    /*圆角矩形*/
    ui->pushButton_read->setStyleSheet("border:1.5px groove gray;border-radius:10px;");
    ui->pushButton_search->setStyleSheet("border:1.5px groove gray;border-radius:10px;");
    ui->textBrowser_main->setStyleSheet("border:1.5px groove gray;border-radius:10px;");
    ui->textBrowser_minor->setStyleSheet("border:1.5px groove gray;border-radius:10px;");

    QIcon icon;
    icon.addFile(tr(":/images/btn.png"));
    ui->pushButton_read->setIcon(icon);
    ui->pushButton_search->setIcon(icon);
    QIcon icon0;
    icon0.addFile(tr(":/images/quit0.png"));
    ui->pushButton_close->setIcon(icon0);
    ui->progressBar->setRange(1,100000);
    setProgressNOTVis();

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(setProgressNOTVis()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete myFont;
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
                /*进度条繁忙状态*/
                ui->progressBar->setMinimum(0);
                ui->progressBar->setMaximum(0);
                timer->start(3500);
                ui->textBrowser_main->append("num        start      end        period     offT       arrT       model      price      \n");
                QFont font("Courier New", 10, QFont::Bold);
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
                ui->textBrowser_main->setFont(*myFont);
            }
        }
        catch (const fstream::failure &e) {
            std::cout << e.what() << std::endl;
        }
        mySort::sort(planes.begin(), planes.end(), cmp);
    }
}

void MainWindow::on_pushButton_search_clicked()
{
    if(!ui->lineEdit_search->text().isEmpty()){
        ui->lineEdit_search->setFont(*myFont);
        if(!ui->textBrowser_minor->document()->isEmpty())
            ui->textBrowser_minor->setText("");
        ui->progressBar->setMinimum(1);
        ui->progressBar->setMaximum(50000);
        ui->progressBar->setVisible(true);
        ui->progressBar->setValue(1);
        for(int i = 1;i < 50000;i ++)
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
        ui->textBrowser_minor->setFont(*myFont);
    }
}

void MainWindow::setProgressNOTVis(){
    ui->progressBar->setVisible(false);
}

const Airplane* MainWindow::bSearch(std::string tnum) {
    unsigned left = 0;
    unsigned right = planes.size() - 1;
    while (left <= right) {
        unsigned mid = (left + right) / 2;
        if (planes[mid].airNum == tnum)
            return &planes[mid];
        else if (planes[mid].airNum < tnum)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return nullptr;
}

void MainWindow::on_pushButton_clicked()
{
    QWizard wizard(this);
    wizard.setWindowTitle(tr("How to use"));
    wizard.addPage(createPage1());
    wizard.addPage(createPage2());
    wizard.exec();
}

QWizardPage* MainWindow::createPage1(){
    QWizardPage* page = new QWizardPage;
    page->setTitle(tr("首先在D盘根目录创建一个叫info,格式为txt的信息文件。"));
    return page;
}

QWizardPage* MainWindow::createPage2(){
    QWizardPage* page = new QWizardPage;
    page->setTitle(tr("按下Read读取，用Search!来查找你想要的航班号信息。"));
    return page;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QRect rect(10,10,this->width(),this->height());
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(rect);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(0, 0, 0, 50);
    unsigned bod = 15;
    for(int i=0; i<bod; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(bod-i, bod-i, this->width()-(bod-i)*2, this->height()-(bod-i)*2);
        color.setAlpha(194 - qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
}

