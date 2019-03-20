#include "customtitlebar.h"
#include "ui_custometitlebar.h"

customeTitleBar::customeTitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::customeTitleBar)
{
    ui->setupUi(this);
}

customeTitleBar::~customeTitleBar()
{
    delete ui;
}
