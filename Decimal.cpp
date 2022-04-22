#include <iostream>
#include "Number.h"

using namespace std;

/* ********** DECIMAL ********** */
Decimal::Decimal(const Number &num, const Number &den)
{
    Number temp_num = num;
    Number temp_den = den;

    this->isPositive = true;
    // The numerator's sign determines the Decimal's sign
    if (temp_num.getSign())
    {
        if (!temp_den.getSign())
        {
            this->isPositive = false;
            temp_den.changeSign();
        }
    }
    else
    {
        temp_num.changeSign();
        if (temp_den.getSign())
            this->isPositive = false;
        else
            temp_den.changeSign();
    }

    this->numerator = temp_num;
    this->denominator = temp_den;
}

Decimal Decimal::operator+(const Decimal &num)
{
    Number lcm = this->denominator;

    if (!(this->denominator == num.denominator))
        lcm = getLCM(this->denominator, num.denominator);

    Number temp1 = this->numerator;
    Number temp2 = num.numerator;

    temp2.printNumber();
    cout << temp2.getSign() << endl;

    if (!this->isPositive)
        temp1.changeSign();
    if (!num.isPositive)
        temp2.changeSign();

    Number temp_num = temp1 * (lcm / this->denominator) + temp2 * (lcm / num.denominator);

    return Decimal(temp_num, lcm);
}

Decimal Decimal::operator-(const Decimal &num)
{
    Number lcm = this->denominator;

    if (!(this->denominator == num.denominator))
        lcm = getLCM(this->denominator, num.denominator);

    Number temp1 = this->numerator;
    Number temp2 = num.numerator;

    if (!this->isPositive)
        temp1.changeSign();
    if (!num.isPositive)
        temp2.changeSign();

    Number temp_num = temp1 * (lcm / this->denominator) - temp2 * (lcm / num.denominator);

    return Decimal(temp_num, lcm);
}

void Decimal::printFraction()
{
    cout << "   ";
    this->numerator.printNumber();
    if (!this->isPositive)
        cout << "- ";
    cout << "******" << endl;
    cout << "   ";
    this->denominator.printNumber();
}

void Decimal::printDecimal()
{
    if (!this->isPositive)
        cout << "-";

    int noZeroPositions = this->numerator.getSize() - this->denominator.getSize() + 1;

    for (int i = 0; i < this->numerator.getSize(); i++)
    {
        if (i == noZeroPositions)
            cout << ".";
        cout << this->numerator[i];
    }
    cout << endl;
}

bool Decimal::isInteger()
{
    int a[1] = {0};
    Number zero(a, 1, true);
    Number reminder = this->numerator % this->denominator;
    if (reminder == zero)
        return true;
    return false;
}
