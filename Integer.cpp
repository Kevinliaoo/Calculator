#include <string>
#include <sstream>
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
// There are two input mode for storing a Decimal
// Mode 1: Insert an integer directly
// Mode 2: Using the # to separate between numerator and denominator,
//         in this case, an integer division will be computed
{
    string data, numerator, denominator;
    strm >> data;

    stringstream ss(data);
    getline(ss, numerator, Decimal::fraction_delimiter);

    if (data.size() == numerator.size())
    {
        ss.clear();
        ss.str(data);
        Number zero;
        ss >> zero;
        integer.numerator = zero;
        integer.isPositive = zero.getSign();
    }
    else
    {
        getline(ss, denominator);
        Number nume, deno;
        ss.clear();
        ss.str(numerator);
        ss >> nume;
        ss.clear();
        ss.str(denominator);
        ss >> deno;
        nume = nume / deno;
        integer = Integer(nume);
    }
    return strm;
}

ostream &operator<<(ostream &strm, Integer &integer)
{
    strm << integer.numerator;
    return strm;
}

string Integer::toString() const
{
    return this->numerator.toString();
}

Integer Integer::factorial() const
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