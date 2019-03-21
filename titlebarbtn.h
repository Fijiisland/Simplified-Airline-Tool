#pragma once

#include <QPushButton>
#include <QMainWindow>
#include <QWidget>
#include <QString>

enum BTNTYPE{
MINIMIZE, CLOSE
};

class titleBarBtn : public QPushButton
{
    Q_OBJECT
public:
    explicit titleBarBtn(BTNTYPE type, QWidget *parent = nullptr);

protected:
    virtual void leaveEvent(QEvent*);
    virtual void hoverEvent(QEvent*);
    virtual void pressEvent(QEvent*);

private:
    BTNTYPE _type;
    QString path;
};

