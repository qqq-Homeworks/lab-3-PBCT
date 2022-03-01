// Copyright 2021 qqq <polyakovdd@student.bmstu.ru>


#ifndef CODE_FRACTION_HPP
#define CODE_FRACTION_HPP

#define N_DEC 4
#define MAX_LENGTH 18

#include "includes.hpp"

class Fraction {
    bool Sign;
    int Integer;
    int Numerator;
    int Denominator;

    void Normalize();


    int getNod(int, int);

public:


    Fraction();

    Fraction(int, int, int);

    Fraction(int, int);
    Fraction(int);

    Fraction(double);

    double ToDouble();

    Fraction &operator=(const char *frStr) {
        int tempFrist, tempSecond, tempThird;
        std::stringstream istr(frStr);
        istr >> tempFrist;
        if (istr.peek() == '/') {
            istr.get();
            istr >> tempSecond;
            *this = Fraction(tempFrist, tempSecond);
        } else {
            istr >> tempSecond;
            istr.get();
            istr >> tempThird;
            *this = Fraction(tempFrist, tempSecond, tempThird);
        }
        this->Normalize();
        return *this;
    }

    Fraction &operator=(const Fraction &fr) {
        Sign = fr.Sign;
        Integer = fr.Integer;
        Numerator = fr.Numerator;
        Denominator = fr.Denominator;

        this->Normalize();
        return *this;
    }

    Fraction &operator=(const double &fr) {
        double q = fr;
        if (q < 0) {
            Sign = 1;
        } else
            Sign = 0;
        q = abs(q);
        Integer = static_cast<int>(q);
        q -= Integer;
        Numerator = static_cast<int>(q * pow(10, N_DEC));
        Denominator = static_cast<int>(pow(10, N_DEC));

        this->Normalize();
        return *this;
    }

    friend Fraction &operator+=(Fraction &left, const Fraction &right);

    friend std::istream &operator>>(std::istream &, Fraction &);

    friend std::ostream &operator<<(std::ostream &, Fraction &);

    friend Fraction operator+(const Fraction &, const Fraction &);

    friend Fraction operator+(const Fraction &, const int &); //как тут лучше то, чтобы не плодить перегрузки
    friend Fraction operator+(const int &, const Fraction &);

    friend Fraction operator+(const Fraction &, const double &);

    friend Fraction operator+(const double &,const Fraction &);
};


#endif //CODE_FRACTION_HPP
