#ifndef _ABOUTDIALOG_H
#define _ABOUTDIALOG_H

#include <QDialog>

namespace Ui {
class _AboutDialog;
}

class _AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit _AboutDialog(QWidget *parent = nullptr);
    ~_AboutDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::_AboutDialog *ui;
    void initialization();
};

#endif // _ABOUTDIALOG_H
