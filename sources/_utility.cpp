#include "headers/_utility.h"

int cmp(const Airplane &x, const Airplane &y){
    return x.airNum < y.airNum;
}

unsigned cntLenInt(int num){
    unsigned cnt = 0;
    while(num != 0){
        num /= 10;
        cnt ++;
    }
    return cnt;
}

std::string cntBlanks(const int &e){
    const unsigned WIDTH = 11;
    unsigned wordL = cntLenInt(e);
    return std::string(WIDTH - wordL, ' ');
}

std::string cntBlanks(const std::string &e){
    const unsigned WIDTH = 11;
    unsigned wordL = e.length();
    return std::string(WIDTH - wordL, ' ');
}

QString _format(const Airplane *tmp){
    std::stringstream s;
    s << tmp->airNum << cntBlanks(tmp->airNum) << tmp->start   << cntBlanks(tmp->start)
      << tmp->end    << cntBlanks(tmp->end)    << tmp->period  << cntBlanks(tmp->period)
      << tmp->offT   << cntBlanks(tmp->offT)   << tmp->arriveT << cntBlanks(tmp->arriveT)
      << tmp->model  << cntBlanks(tmp->model)  << tmp->price   << cntBlanks(tmp->price);
    return QString::fromLocal8Bit(s.str().c_str());
}


