#include "Number.h"

Integer::Integer(const Number &num) : Decimal(num)
{
    this->isPositive = num.getSign();
    // this->numerator stores object's sign
    if (!this->numerator.getSign())
        this->numerator.changeSign();
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

Integer Integer::operator-()
{
    Integer zero;
    return zero - *this;
}

Integer Integer::operator*(const Integer &integer)
{
    Number newNum = this->numerator * integer.numerator;
    return Integer(newNum);
}

Integer Integer::operator/(const Integer &integer)
{
    Number newNum = this->numerator / integer.numerator;
    Integer res(newNum);
    return res;
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
    integer.isPositive = zero.getSign();
    return strm;
}

ostream &operator<<(ostream &strm, Integer &integer)
{
    strm << integer.numerator;
    return strm;
}

string Integer::toString()
{
    return this->numerator.toString();
}

Integer Integer::factorial()
{
    Number temp;
    temp = this->numerator.factorial();
    return Integer(temp);
}