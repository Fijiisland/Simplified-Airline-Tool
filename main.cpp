#include "mainwindow.h"
#include <QApplication>
#include <QFont>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QFont f("Courier New", 8);
    a.setFont(f);
    return a.exec();
}
