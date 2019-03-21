#include "titlebarbtn.h"
#include "mainwindow.h"

#include <QPixmap>
#include <QBitmap>

titleBarBtn::titleBarBtn(BTNTYPE type, QWidget *parent):
    QPushButton (parent), _type(type)
{
    switch(type){
    case BTNTYPE::MINIMIZE:
        path = ":/image/minimize";
        break;
    case BTNTYPE::CLOSE:
        path = ":/image/quit";
        break;
    }
    QPixmap pixmap(path + "0.png");
    this->resize(pixmap.size());
    this->setMask(QBitmap(pixmap.mask()));		// 设置自定义按钮有效区域
    this->setStyleSheet("QPushButton{border-image: url(" + path + "0.png);}");
}

void titleBarBtn::leaveEvent(QEvent *){
    this->setStyleSheet("QPushButton{border-image: url(" + path + "0.png);}");
}

void titleBarBtn::hoverEvent(QEvent *){
    this->setStyleSheet("QPushButton{border-image: url(" + path + "1.png);}");
}

void titleBarBtn::pressEvent(QEvent *){
    this->setStyleSheet("QPushButton{border-image: url(" + path + "3.png);}");
}
