#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "_utility.h"       // Customized Algorithm Jar

#include <fstream>
#include <sstream>
#include <algorithm>

#include <QMouseEvent>
#include <QMessageBox>
#include <QFont>
#include <QString>
#include <QIcon>
#include <QDebug>
#include <QFontDatabase>
#include <QPainter>
#include <QPixmap>
#include <QBitmap>
#include <QPropertyAnimation>

using std::stringstream;
using std::string;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_move(false)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(this->width(),this->height());
    this->setAttribute(Qt::WA_TranslucentBackground);
    myFont = new QFont("Courier New", 9, QFont::Bold);
    initialization();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(setProgressNOTVis()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete myFont;
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

void MainWindow::on_pushButton_read_clicked()
{
    if(ui->textBrowser_main->document()->isEmpty()){
        using std::fstream;
        const char *path = "/Users/1kasshole/Desktop/info.txt";
        fstream fs;
        try {
            fs.open(path, fstream::in);
            if(!fs){
                onShakeWindow();
                QMessageBox::information(this, "啊哦", "你并没有在D盘创建相应文件哦", QMessageBox::Yes);
            }
            else{
                ui->pushButton_search->setEnabled(true);
                ui->progressBar->setVisible(true);
                /*进度条繁忙状态*/
                ui->progressBar->setMinimum(0);
                ui->progressBar->setMaximum(0);
                /*进度条繁忙状态*/
                timer->start(3500);
                ui->textBrowser_main->append("num        start      end        period     offT       arrT       model      price      \n");
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
                ui->textBrowser_main->setFont(_instance(myFont));
                mySort::sort(planes.begin(), planes.end(), cmp);           // 自定义sort算法
            }
        }
        catch (const fstream::failure &e) {
            std::cout << e.what() << std::endl;
        }
    }
}

void MainWindow::on_pushButton_search_clicked()
{
    if(!ui->lineEdit_search->text().isEmpty()){
        ui->lineEdit_search->setFont(_instance(myFont));
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
        ui->textBrowser_minor->setFont(_instance(myFont));
    }
}

void MainWindow::setProgressNOTVis(){
    ui->progressBar->setVisible(false);
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

void MainWindow::paintEvent(QPaintEvent *)          // Draw shadow effect
{
    unsigned radius = 5;
    unsigned bod = 10;
    QRect rect(10,10,this->width() - 20,this->height() - 20);
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRoundedRect(rect, radius, radius);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));
    painter.drawRoundedRect(rect, radius, radius);
    QColor color(0, 0, 0, 50);
    for(int i = 0; i< bod; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        QRect tmp(bod-i, bod-i, this->width()-(bod-i)*2, this->height()-(bod-i)*2);
        path.addRoundedRect(tmp,radius,radius);
        color.setAlpha(150 - sqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
}

void MainWindow::initialization(){
    /* Custom Logo Font */
    int fontID = QFontDatabase::addApplicationFont(tr(":/font/InfoDisplayWeb_Bold.ttf"));
    QString msyh = QFontDatabase::applicationFontFamilies(fontID).at(0);
    ui->label_font1->setFont(QFont(msyh, 13));
    ui->label_font2->setFont(QFont(msyh, 13));
    ui->label_font3->setFont(QFont(msyh, 13));
    ui->label_font1->setStyleSheet("color:#8B8386;");
    ui->label_font2->setStyleSheet("color:#8B8386;");
    ui->label_font3->setStyleSheet("color:#8B8386;");

    ui->pushButton_read->setFont(_instance(myFont));
    ui->pushButton_search->setFont(_instance(myFont));   
#ifdef Q_OS_MACOS
    myFont->setPointSize(11);
#else
    myFont->setPointSize(8);
#endif
    ui->label_logo_text->setFont(_instance(myFont));
    myFont->setPointSize(8);
    myFont->setBold(false);
    ui->label_right->setFont(_instance(myFont));
    myFont->setPointSize(9);

    ui->pushBtn_minimize->setStyleSheet("QPushButton{border-image: url(:/images/minimize0.png);}"
                                        "QPushButton:hover{border-image: url(:/images/minimize1.png);}"
                                        "QPushButton:pressed{border-image: url(:/images/minimize3.png);}");

    ui->pushBtn_close->setStyleSheet("QPushButton{border-image: url(:/images/quit0.png);}"
                                     "QPushButton:hover{border-image: url(:/images/quit1.png);}"
                                     "QPushButton:pressed{border-image: url(:/images/quit3.png);}");

    ui->pushBtn_about->setStyleSheet("QPushButton{border-image: url(:/images/about0.png);}"
                                     "QPushButton:hover{border-image: url(:/images/about1.png);}"
                                     "QPushButton:pressed{border-image: url(:/images/about3.png);}");


    ui->pushButton_read->setStyleSheet("border:1.5px groove gray;border-radius:10px;");
    ui->pushButton_search->setStyleSheet("border:1.5px groove gray;border-radius:10px;");
    ui->textBrowser_main->setStyleSheet("border:1.5px dashed #A3A3A3;");
    ui->textBrowser_minor->setStyleSheet("border:1.5px dashed #A3A3A3;");

    ui->pushButton_search->setEnabled(false);

    QIcon icon;
    icon.addFile(tr(":/images/btn.png"));
    ui->pushButton_read->setIcon(icon);
    ui->pushButton_search->setIcon(icon);
    ui->progressBar->setRange(1,100000);
    setProgressNOTVis();
}

/* 右上角自定义按钮事件 */
void MainWindow::on_pushBtn_close_clicked()
{
    this->close();
}

void MainWindow::on_pushBtn_minimize_clicked()
{
    if(this->windowState() != Qt::WindowMinimized)
        this->setWindowState(Qt::WindowMinimized);    // 在macOS下有bug
}


/* Defination of mouse event */
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //当鼠标左键点击时.
    if (event->button() == Qt::LeftButton)
    {
        m_move = true;
        //记录鼠标的世界坐标.
        m_startPoint = event->globalPos();
        //记录窗体的世界坐标.
        m_windowPoint = this->frameGeometry().topLeft();
    }
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //移动中的鼠标位置相对于初始位置的相对位置.
        QPoint relativePos = event->globalPos() - m_startPoint;
        //然后移动窗体即可.
        this->move(m_windowPoint + relativePos );
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //改变移动状态.
        m_move = false;
    }
}

void MainWindow::on_pushBtn_help_clicked()
{
    QWizard wizard(this);
    wizard.setWindowTitle(tr("How to use"));
    wizard.addPage(createPage1());
    wizard.addPage(createPage2());
    wizard.exec();
}



void MainWindow::on_pushBtn_about_clicked()
{
    aboutDialog = new _AboutDialog(this);
    aboutDialog->setModal(true);
    aboutDialog->show();
}

void MainWindow::onShakeWindow()
{
    QPropertyAnimation *pAnimation = new QPropertyAnimation(this, "pos");
    pAnimation->setDuration(500);
    pAnimation->setLoopCount(2);
    pAnimation->setKeyValueAt(0, QPoint(geometry().x() - 3, geometry().y() - 3));
    pAnimation->setKeyValueAt(0.1, QPoint(geometry().x() + 3, geometry().y() + 3));
    pAnimation->setKeyValueAt(0.2, QPoint(geometry().x() - 3, geometry().y() + 3));
    pAnimation->setKeyValueAt(0.3, QPoint(geometry().x() + 3, geometry().y() - 3));
    pAnimation->setKeyValueAt(0.4, QPoint(geometry().x() - 3, geometry().y() - 3));
    pAnimation->setKeyValueAt(0.5, QPoint(geometry().x() + 3, geometry().y() + 3));
    pAnimation->setKeyValueAt(0.6, QPoint(geometry().x() - 3, geometry().y() + 3));
    pAnimation->setKeyValueAt(0.7, QPoint(geometry().x() + 3, geometry().y() - 3));
    pAnimation->setKeyValueAt(0.8, QPoint(geometry().x() - 3, geometry().y() - 3));
    pAnimation->setKeyValueAt(0.9, QPoint(geometry().x() + 3, geometry().y() + 3));
    pAnimation->setKeyValueAt(1, QPoint(geometry().x() - 3, geometry().y() - 3));
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}
