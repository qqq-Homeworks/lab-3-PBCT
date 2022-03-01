// Copyright 2021 qqq <polyakovdd@student.bmstu.ru>


#include "Fraction.hpp"


Fraction::Fraction() {
    Integer = 0;
    Numerator = 0;
    Denominator = 0;
}

Fraction::Fraction(int intgr, int num, int den) {
    if (intgr < 0) {
        Sign = 1;
    } else
        Sign = 0;
    Integer = abs(intgr);
    Numerator = num;
    Denominator = den;
    this->Normalize();
}

Fraction::Fraction(int num, int den) {
    Integer = 0;
    if (num < 0) {
        Sign = 1;
    } else
        Sign = 0;
    Numerator = abs(num);
    Denominator = den;
    this->Normalize();
}
Fraction::Fraction(int q){
    if (q<0)
    {
        Sign = true;
    }
    else Sign = false;
    Integer = q;
    Numerator = 0;
    Denominator = 1;
}
Fraction::Fraction(const double fr) {
    double q = fr;
    if (fr < 0) {
        Sign = 1;
    } else
        Sign = 0;
    q = abs(fr);
    Integer = static_cast<int>(q);
    q -= Integer;
    Numerator = static_cast<int>(q * pow(10, N_DEC));
    Denominator = static_cast<int>(pow(10, N_DEC));

    this->Normalize();
}

int Fraction::getNod(int a, int b) {
    if (b == 0)
        return a;
    return getNod(b, a % b);
}

void Fraction::Normalize() {
    Integer += Numerator / Denominator;
    Numerator = Numerator % Denominator;

    int nod = getNod(Numerator, Denominator);
    Denominator /= nod;
    Numerator /= nod;
}

std::istream &operator>>(std::istream &istr, Fraction &fraction) {
    int tempFirst, tempSecond, tempThird;
    istr >> tempFirst;
    if (istr.peek() == '/') {
        istr.get();
        istr >> tempSecond;
        fraction = Fraction(tempFirst, tempSecond);
    } else if (istr.peek() == '\n') {
        fraction = Fraction(tempFirst);
    } else {
        istr >> tempSecond;
        istr.get();
        istr >> tempThird;
        fraction = Fraction(tempFirst, tempSecond, tempThird);
        fraction.Normalize();
    }
    return istr;
}

std::ostream &operator<<(std::ostream &ostr, Fraction &fraction) {
    if (fraction.Numerator != 0) {
        ostr << '\n';
        ostr << "     " << fraction.Numerator << "\n ";
        if (fraction.Sign) ostr << '-';
        if (fraction.Integer != 0) ostr << fraction.Integer;
        ostr << "  ---\n";
        ostr << "     " << fraction.Denominator << '\n';
        return ostr;
    } else {
        if (fraction.Sign) ostr << '-';
        ostr << fraction.Integer;
        return ostr;
    }

}

Fraction operator+(const Fraction &fraction1, const Fraction &fraction2) {
    Fraction fr1 = fraction1;
    Fraction fr2 = fraction2;
    double q1 = fr1.ToDouble();
    double q2 = fr2.ToDouble();
    q1 = q1 + q2;
    Fraction result = q1;
    return result;
}

Fraction operator+(const Fraction &fraction1, const double &dbl) {
    Fraction fr = fraction1;
    double q1 = fr.ToDouble();
    q1 = q1 + dbl;
    Fraction result = q1;
    return result;
}

Fraction operator+(const double &dbl, const Fraction &fraction1) {
    Fraction fr = fraction1;
    double q1 = fr.ToDouble();
    q1 = q1 + dbl;
    Fraction result = q1;
    return result;
}

Fraction operator+(const Fraction &fraction1, const int &intgr) {
    Fraction fr = fraction1;
    if (fr.Sign) fr.Integer = fr.Integer * (-1) + intgr;
    else
        fr.Integer += intgr;
    if (fr.Integer < 0) {
        fr.Sign = true;
    } else fr.Sign = false;
    fr.Normalize();
    return fr;
}

Fraction operator+(const int &intgr, const Fraction &fraction1) {
    Fraction fr = fraction1;
    if (fr.Sign) fr.Integer = fr.Integer * (-1) + intgr;
    else
        fr.Integer += intgr;
    if (fr.Integer < 0) {
        fr.Sign = true;
    } else fr.Sign = false;
    fr.Normalize();
    return fr;
}

Fraction &operator+=(Fraction &left, const Fraction &right) {
    //left = left+right;//бред с константной перегрузкой сначала просто суммы, а потом ломающимся toDouble
    Fraction q = right;
    left = left + q;
    return left;
}

double Fraction::ToDouble() {
    double qwe = static_cast<double>(Numerator) / Denominator;
    double q = static_cast<double>(this->Integer) + qwe;
    if (Sign) q *= (-1);
    return q;
}
