#ifndef AIRPLANE_H
#define AIRPLANE_H
#define STR const std::string
#include <iostream>
#include <string>
#include <vector>

class Airplane {
public:
    explicit Airplane() = default;
    explicit Airplane(STR &ai, STR &st, STR &en, STR &pe,
        int of, int ar, STR &mo, int pr)
        : airNum(ai), start(st), end(en), period(pe), offT(of), arriveT(ar), model(mo), price(pr) {}
public:
    std::string airNum;
    std::string start;
    std::string end;
    std::string period;
    int         offT;
    int         arriveT;
    std::string model;
    int         price;
};

#endif // AIRPLANE_H
