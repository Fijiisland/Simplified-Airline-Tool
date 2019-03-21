#ifndef CUSTOMETITLEBAR_H
#define CUSTOMETITLEBAR_H

#include <QWidget>

namespace Ui {
class customeTitleBar;
}

class customeTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit customeTitleBar(QWidget *parent = nullptr);
    ~customeTitleBar();

private:
    Ui::customeTitleBar *ui;
};

#endif // CUSTOMETITLEBAR_H
