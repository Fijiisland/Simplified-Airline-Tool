#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include "airplane.h"
#include <QtCore>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_read_clicked();

    void on_pushButton_search_clicked();

    void setProgressVis();

private:
    const Airplane* bSearch(std::string tnum);

private:
    Ui::MainWindow *ui;
    std::vector<Airplane> planes;
    QTimer *timer;
};

#endif // MAINWINDOW_H
