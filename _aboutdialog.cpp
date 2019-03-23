#include "_aboutdialog.h"
#include "ui__aboutdialog.h"

#include <QFontDatabase>
#include <QDesktopServices>
#include <QUrl>

_AboutDialog::_AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::_AboutDialog)
{
    ui->setupUi(this);
    initialization();
}

_AboutDialog::~_AboutDialog()
{
    delete ui;
}

void _AboutDialog::initialization(){
    /* Custom Logo Font */
    setWindowTitle(QString("Good to see you"));
    int fontID = QFontDatabase::addApplicationFont(tr(":/font/InfoDisplayWeb_Bold.ttf"));
    QString msyh = QFontDatabase::applicationFontFamilies(fontID).at(0);
    ui->label_logo_text->setFont(QFont(msyh, 22));
    ui->label_logo_text->setStyleSheet("color:#8B8386;");
    ui->label_brief->setFont(QFont(msyh, 15, QFont::Normal, true));
    ui->label_brief->setStyleSheet("color:#8B8386;");
}

void _AboutDialog::on_pushButton_clicked()
{
    QDesktopServices::openUrl(QUrl(QString("https://github.com/Fijiisland/Simplified-Airline-Tool")));
}
