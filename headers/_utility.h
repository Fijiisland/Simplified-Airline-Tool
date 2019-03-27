#pragma once

#include "_airplane.h"
#include "_blendSort.h"
#include <QString>
#include <sstream>
#include <QFontDatabase>
#include <fstream>
#include <QMainWindow>
#include <vector>
#include <QtCore>
#include <QFont>
#include <QWizard>
#include <algorithm>
#include <QMouseEvent>
#include <QMessageBox>
#include <QIcon>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QBitmap>
#include <QPropertyAnimation>

extern int cmp(const Airplane &x, const Airplane &y);

extern unsigned cntLenInt(int num);

extern std::string cntBlanks(const int &e);

extern std::string cntBlanks(const std::string &e);

extern QString _format(const Airplane *tmp);



