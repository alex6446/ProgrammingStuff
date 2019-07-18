#include "fraction.h"
#include <iostream>
#include <cmath>

Fraction::Fraction(int num, int denom) {
    numerator   = num;
    denominator = denom;
}

Fraction::Fraction(int num) {
    numerator   = num;
    denominator = 1;
}

std::ostream& operator<<(std::ostream& os, const Fraction& f) {
    if(f.numerator == f.denominator)
        os << 1;
    else if(f.denominator == 1)
        os << f.numerator;
    else
        os << f.numerator << "/" << f.denominator;
    return os;
}

Fraction& Fraction::Reduce() {
    int divisor;
    int num = abs(numerator);
    int denom = abs(denominator);
    if(num < denom)
        divisor = num;
    else
        divisor = denom;

    for(int i = divisor; i > 1; i--) {
        if(numerator % i == 0 && denominator % i == 0) {
            numerator /= i;
            denominator /= i;
            break;
        }
    }
    return *this;
}

////////////////    Multiply    /////////////////////////////////////////////////

Fraction Fraction::operator*(const Fraction& f) const {
     int num = numerator * f.numerator;
     int denom = denominator * f.denominator;
     Fraction result(num, denom);
     return result;
}

Fraction Fraction::operator*(const int f) const {
     int num = numerator * f;
     int denom = denominator;
     Fraction result(num, denom);
     return result;
}

Fraction operator*(const int n, const Fraction& f) {
    int num = n * f.numerator;
    int denom = f.denominator;
    Fraction result(num, denom);
    return result;
}

////////////////    Divide    /////////////////////////////////////////////////

Fraction Fraction::operator/(const Fraction& f) const {
    int num = numerator * f.denominator;
    int denom = denominator * f.numerator;
    Fraction result(num, denom);
    return result;
}

Fraction Fraction::operator/(const int f) const {
     int num = numerator;
     int denom = denominator * f;
     Fraction result(num, denom);
     return result;
}

Fraction operator/(const int n, const Fraction& f) {
    int num = f.numerator;
    int denom = n * f.denominator;
    Fraction result(num, denom);
    return result;
}

////////////////    Add    /////////////////////////////////////////////////

Fraction Fraction::operator+(const Fraction& f) const {
    int num = numerator * f.denominator + f.numerator * denominator;
    int denom = denominator * f.denominator;
    Fraction result(num, denom);
    return result;
}

Fraction Fraction::operator+(const int f) const {
     int num = numerator + f * denominator;
     int denom = denominator;
     Fraction result(num, denom);
     return result;
}

Fraction operator+(const int n, const Fraction& f) {
    int num = n * f.denominator + f.numerator;
    int denom = f.denominator;
    Fraction result(num, denom);
    return result;
}

////////////////    Subtract    /////////////////////////////////////////////////

Fraction Fraction::operator-(const Fraction& f) const {
    int num = numerator * f.denominator - f.numerator * denominator;
    int denom = denominator * f.denominator;
    Fraction result(num, denom);
    return result;
}

Fraction Fraction::operator-(const int f) const {
     int num = numerator - f * denominator;
     int denom = denominator;
     Fraction result(num, denom);
     return result;
}

Fraction operator-(const int n, const Fraction& f) {
    int num = n * f.denominator - f.numerator;
    int denom = f.denominator;
    Fraction result(num, denom);
    return result;
}



