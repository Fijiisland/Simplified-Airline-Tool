#pragma once

#include <QWidget>

namespace Ui {
class CustomTitleBar;
}

class CustomTitleBar : public QWidget
{
    Q_OBJECT

public:

    explicit CustomTitleBar(QWidget *parent = 0);
    ~CustomTitleBar();

signals:

    void callback_close();
    void callback_minimize();


private slots:

    void on_ButtonClicked();

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void resizeEvent(QResizeEvent *event);

private:
    Ui::CustomTitleBar *ui;
};
