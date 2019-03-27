#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "_airplane.h"
#include "_aboutdialog.h"
#include "_appenddialog.h"
#include "_utility.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

     void          appendMainText(QString str);
     void          appendAirline(Airplane a);
     void          sortAgain();

protected:
      virtual void paintEvent( QPaintEvent * e);

      virtual void mousePressEvent(QMouseEvent *event);

      virtual void mouseMoveEvent(QMouseEvent *event);

      virtual void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_pushButton_read_clicked();

    void on_pushButton_search_clicked();

    void setProgressNOTVis();

    void on_pushBtn_close_clicked();

    void on_pushBtn_minimize_clicked();

    void on_pushBtn_help_clicked();

    void on_pushBtn_about_clicked();

    void on_pushBtn_append_clicked();

private:
    Ui::MainWindow       *ui;
    _AboutDialog         *aboutDialog;
    _appendDialog        *appendDialog;
    std::vector<Airplane> planes;
    QTimer               *timer;
    QFont                *myFont;
    QPoint                m_startPoint;
    QPoint                m_windowPoint;
    bool                  m_move;
    const Airplane* bSearch(std::string tnum);
    void            initialization();
    void            style();
    void            onShakeWindow();
    QWizardPage*    createPage1();
    QWizardPage*    createPage2();
};

#endif // MAINWINDOW_H
