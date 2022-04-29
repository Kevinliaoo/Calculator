#include <string>
#include "Number.h"

Integer::Integer(const Number &num) : Decimal(num)
{
    // this->numerator stores object's sign
    if (!num.getSign())
        this->numerator.changeSign();
}

const Integer Integer::operator+(const Integer &integer) const
{
    Number newNum = this->numerator + integer.numerator;
    return Integer(newNum);
}

const Integer Integer::operator-(const Integer &integer) const
{
    Number newNum = this->numerator - integer.numerator;
    return Integer(newNum);
}

const Integer Integer::operator-() const
{
    Integer zero;
    return zero - *this;
}

const Integer Integer::operator*(const Integer &integer) const
{
    Number newNum = this->numerator * integer.numerator;
    return Integer(newNum);
}

const Integer Integer::operator/(const Integer &integer) const
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

Integer Integer::power(const Integer &times)
{
    Number temp = this->numerator.power(times.numerator);
    return Integer(temp);
}