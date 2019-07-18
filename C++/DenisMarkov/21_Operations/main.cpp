#include <iostream>
#include "fraction.h"
using namespace std;

int main()
{
    Fraction num(2, 5);
    cout << num << endl;

    Fraction fum(12, 3);
    cout << fum << endl;

    cout << endl << "Multiply" << endl;
    cout << fum << " * " << num << " = " << (fum*num).Reduce() << endl;

    cout << endl << "Divide" << endl;
    cout << fum << " / " << num << " = " << (fum/num).Reduce() << endl;

    cout << endl << "Add" << endl;
    cout << fum << " + " << num << " = " << (fum+num).Reduce() << endl;

    cout << endl << "Subtract" << endl;
    cout << fum << " - " << num << " = " << (fum-num).Reduce() << endl;

    cout << endl << "Reduce" << endl;
    Fraction reduce(16, 128);
    cout << reduce << endl;
    reduce.Reduce();
    cout << reduce << endl;

    ////////////// Program //////////////

    cout << endl << "Enter fraction problem: ";
    int numerator, denominnator;
    char sign, divider;
    int subnumerator, subdenominnator;

    cin >> numerator >> divider >> denominnator;
    cin >> sign;
    cin >> subnumerator >> divider >> subdenominnator;

    Fraction fract(numerator, denominnator);
    Fraction subfract(subnumerator, subdenominnator);

    cout << "Solution: " << endl;
    cout << fract << " " << sign << " " << subfract << " = ";
    if(sign == '*')
        cout << (fract * subfract).Reduce() << endl;
    else if(sign == '/')
        cout << (fract / subfract).Reduce() << endl;
    else if(sign == '+')
        cout << (fract + subfract).Reduce() << endl;
    else if(sign == '-')
        cout << (fract - subfract).Reduce() << endl;
    else
        cout << endl << "!!! Sign ERROR !!!" << endl;

    return 0;
}









