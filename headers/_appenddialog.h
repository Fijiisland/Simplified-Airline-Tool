#ifndef _APPENDDIALOG_H
#define _APPENDDIALOG_H

#include <QDialog>

namespace Ui {
class _appendDialog;
}

class _appendDialog : public QDialog
{
    Q_OBJECT

public:
    explicit _appendDialog(QWidget *parent = nullptr);
    ~_appendDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::_appendDialog *ui;
    void initialization();
    void style();
};

#endif // _APPENDDIALOG_H
