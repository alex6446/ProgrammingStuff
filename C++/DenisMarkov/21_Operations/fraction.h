#pragma once
#include <iostream>

class Fraction {
    private:
        int numerator; //Числитель
        int denominator; //Знаменатель
    public:
        Fraction(int, int);
        Fraction(int);
        Fraction& Reduce();
        Fraction operator*(const Fraction&) const;
        Fraction operator*(const int) const;
        friend Fraction operator*(const int, const Fraction&);

        Fraction operator/(const Fraction&) const;
        Fraction operator/(const int) const;
        friend Fraction operator/(const int, const Fraction&);

        Fraction operator+(const Fraction&) const;
        Fraction operator+(const int) const;
        friend Fraction operator+(const int, const Fraction&);

        Fraction operator-(const Fraction&) const;
        Fraction operator-(const int) const;
        friend Fraction operator-(const int, const Fraction&);

        friend std::ostream& operator<<(std::ostream&, const Fraction&);
};

