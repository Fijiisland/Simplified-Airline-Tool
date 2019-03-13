#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <iostream>
#include <string>
#include <vector>

class Airplane {
    friend void print(const std::vector<Airplane> &e);
    friend void printSingle(const Airplane &tmp);
public:
    explicit Airplane() = default;
    explicit Airplane(std::string &ai, std::string &st, std::string &en, std::string &pe,
        int of, int ar, std::string &mo, int pr)
        : airNum(ai), start(st), end(en), period(pe), offT(of), arriveT(ar), model(mo), price(pr) {}
public:
    std::string airNum;
    std::string start;
    std::string end;
    std::string period;
    int offT, arriveT;
    std::string model;
    int price;
};

#endif // AIRPLANE_H
