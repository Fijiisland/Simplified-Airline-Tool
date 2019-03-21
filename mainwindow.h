#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include <QtCore>
#include <QFont>
#include <QWizard>
#include "airplane.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
      virtual void paintEvent( QPaintEvent * e);
private slots:
    void on_pushButton_read_clicked();

    void on_pushButton_search_clicked();

    void setProgressNOTVis();

    void on_pushButton_clicked();

    void on_pushBtn_close_clicked();

    void on_pushBtn_minimize_clicked();

private:
    const Airplane* bSearch(std::string tnum);

    void initialization();

private:
    Ui::MainWindow *ui;
    std::vector<Airplane> planes;
    QTimer *timer;
    QFont *myFont;
    QWizardPage* createPage1();
    QWizardPage* createPage2();
};

#endif // MAINWINDOW_H
