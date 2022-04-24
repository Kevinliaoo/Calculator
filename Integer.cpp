#include "Number.h"

Integer::Integer() : Decimal()
{
    int a[1] = {1};
    Number one(a, 1, true);
    Number zero;
    this->numerator = zero;
    this->denominator = one;
}

Integer::Integer(const Number &num) : Decimal()
{
    this->isPositive = true;
    this->numerator = num;
    int a[1] = {1};
    Number one(a, 1, true);
    this->denominator = one;
}

Integer Integer::operator+(const Integer &integer)
{
    Number newNum = this->numerator + integer.numerator;
    return Integer(newNum);
}

Integer Integer::operator-(const Integer &integer)
{
    Number newNum = this->numerator - integer.numerator;
    return Integer(newNum);
}

Integer Integer::operator*(const Integer &integer)
{
    Number newNum = this->numerator * integer.numerator;
    return Integer(newNum);
}

Integer Integer::operator/(const Integer &integer)
{
    Number newNum = this->numerator / integer.numerator;
    return Integer(newNum);
}

Integer &Integer::operator=(const Integer &integer)
{
    this->numerator = integer.numerator;
    return *this;
}

bool Integer::operator==(const Integer &integer) const
{
    return this->numerator == integer.numerator;
}

istream &operator>>(istream &strm, Integer &integer)
{
    Number zero;
    strm >> zero;
    integer.numerator = zero;
    return strm;
}

ostream &operator<<(ostream &strm, Integer &integer)
{
    strm << integer.numerator;
    return strm;
}