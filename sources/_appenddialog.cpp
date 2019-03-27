#include "headers/_appenddialog.h"
#include "ui__appenddialog.h"
#include "headers/mainwindow.h"
#include "headers/_utility.h"

_appendDialog::_appendDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::_appendDialog)
{
    ui->setupUi(this);
    initialization();
}

_appendDialog::~_appendDialog()
{
    delete ui;
}

void _appendDialog::initialization(){
    setWindowTitle("Appending....");
    style();
    ui->progressBar->setRange(0, 10000);
    ui->progressBar->setValue(10);
}

void _appendDialog::style(){
    /* Custom Logo Font */
    int fontID = QFontDatabase::addApplicationFont(tr(":/font/share/fonts/InfoDisplayWeb_Bold.ttf"));
    QString msyh = QFontDatabase::applicationFontFamilies(fontID).at(0);
    QFont _font(msyh, 9);
    ui->label_num->setFont(_font); ui->label_start->setFont(_font);
    ui->label_end->setFont(_font); ui->label_period->setFont(_font);
    ui->label_offt->setFont(_font); ui->label_arrt->setFont(_font);
    ui->label_model->setFont(_font); ui->label_price->setFont(_font);
    ui->lineEd_num->setStyleSheet("border:1.5px dashed #A3A3A3;");   ui->lineEd_sta->setStyleSheet("border:1.5px dashed #A3A3A3;");
    ui->lineEd_end->setStyleSheet("border:1.5px dashed #A3A3A3;");   ui->lineEd_per->setStyleSheet("border:1.5px dashed #A3A3A3;");
    ui->lineEd_offt->setStyleSheet("border:1.5px dashed #A3A3A3;");  ui->lineEd_arrt->setStyleSheet("border:1.5px dashed #A3A3A3;");
    ui->lineEd_model->setStyleSheet("border:1.5px dashed #A3A3A3;"); ui->lineEd_price->setStyleSheet("border:1.5px dashed #A3A3A3;");
    ui->lineEd_num->setFont(_font);   ui->lineEd_sta->setFont(_font);
    ui->lineEd_end->setFont(_font);   ui->lineEd_per->setFont(_font);
    ui->lineEd_offt->setFont(_font);  ui->lineEd_arrt->setFont(_font);
    ui->lineEd_model->setFont(_font); ui->lineEd_price->setFont(_font);
    ui->pushButton->setStyleSheet("border:1.5px groove gray;border-radius:10px;");
    QIcon icon;
    icon.addFile(tr(":/images/share/images/btn.png"));
    ui->pushButton->setIcon(icon);
    ui->pushButton->setFont(QFont("Courier New"));
}


void _appendDialog::on_pushButton_clicked()
{
    ui->progressBar->setValue(10);
    for(int i = 11;i < 10000 - 20;i ++)
        ui->progressBar->setValue(i);
    std::string s1,s2,s3,s4,s5,s6,s7,s8;
    s1 = ui->lineEd_num->text().toStdString();   s2 = ui->lineEd_sta->text().toStdString();
    s3 = ui->lineEd_end->text().toStdString();   s4 = ui->lineEd_per->text().toStdString();
    s5 = ui->lineEd_offt->text().toStdString();  s6 = ui->lineEd_arrt->text().toStdString();
    s7 = ui->lineEd_model->text().toStdString(); s8 = ui->lineEd_price->text().toStdString();
    Airplane tmp(s1, s2, s3, s4, stoi(s5), stoi(s6), s7, stoi(s8));
    MainWindow *ptr = dynamic_cast<MainWindow*>(parentWidget());
    ptr->appendAirline(tmp);
    ptr->sortAgain();
    ptr->appendMainText(_format(&tmp));
    using std::fstream;
    const char *path = "D://info.txt";
    fstream fs;
    fs.open(path, fstream::app);
    try {
        fs << "\n" <<s1 << " " << s2 << " " << s3 << " " << s4 << " "
           << s5 << " " << s6 << " " <<s7 << " " << s8;
    } catch (const fstream::failure &e) {
        std::cout << e.what() << std::endl;
    }
    fs.close();
    ui->lineEd_num->setText("");   ui->lineEd_sta->setText("");
    ui->lineEd_end->setText("");   ui->lineEd_per->setText("");
    ui->lineEd_offt->setText("");  ui->lineEd_arrt->setText("");
    ui->lineEd_model->setText(""); ui->lineEd_price->setText("");
}
