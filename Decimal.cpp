#include <iostream>
#include <string>
#include <sstream>
#include "Number.h"

using namespace std;

/* ********** DECIMAL ********** */

char Decimal::fraction_delimiter = '#';

Decimal::Decimal()
{
    Number zero;
    int a[1] = {1};
    Number one(a, 1, true);
    this->numerator = zero;
    this->denominator = one;
    this->isPositive = true;
}

Decimal::Decimal(const Number &num)
{
    this->numerator = num;
    this->isPositive = num.getSign();
    if (!num.getSign())
        this->numerator.changeSign();
    int a[1] = {1};
    Number den(a, 1, true);
    this->denominator = den;
}

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

const Decimal Decimal::operator+(const Decimal &num) const
{
    Number lcm = this->denominator;

    if (!(this->denominator == num.denominator))
        lcm = getLCM(this->denominator, num.denominator);

    Number temp1 = this->numerator;
    Number temp2 = num.numerator;

    Number div_1 = lcm / this->denominator;
    Number div_2 = lcm / num.denominator;

    // Change signs (since the sign is stored in the isPositive variable)
    if (!this->isPositive)
        temp1.changeSign();
    if (!num.isPositive)
        temp2.changeSign();

    temp1 = temp1 * div_1;
    temp2 = temp2 * div_2;

    Number temp_num = temp1 + temp2;
    return Decimal(temp_num, lcm);
}

const Decimal Decimal::operator-(const Decimal &num) const
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

const Decimal Decimal::operator-() const
{
    Decimal zero;
    return zero - *this;
}

const Decimal Decimal::operator/(const Decimal &num) const
{
    int x[] = {0};
    Number int_zero(x, 1, true);
    Decimal zero(int_zero, int_zero);
    Decimal a = *this;
    Decimal b = num;
    bool isPos = true;

    a = simplify(a);
    b = simplify(b);
    if (b.denominator == int_zero || b.numerator == int_zero)
    {
        cout << "[Error]: Can not divide by zero (at Decimal::operator/).\n";
        return zero;
    }
    if (a.denominator == int_zero || a.numerator == int_zero)
        return zero;

    if (!a.isPositive)
    {
        if (b.isPositive)
            isPos = false;
    }
    else if (!b.isPositive)
        isPos = false;

    Number new_den = a.denominator * b.numerator;
    Number new_num = a.numerator * b.denominator;

    if (!isPos)
        new_num.changeSign();

    return Decimal(new_num, new_den);
}

const Decimal Decimal::operator*(const Decimal &num) const
{
    Number int_zero;
    Decimal zero;
    Decimal a = *this;
    Decimal b = num;
    bool isPos = true;

    a = simplify(a);
    b = simplify(b);
    if (a.denominator == int_zero || a.numerator == int_zero)
        return zero;
    if (b.denominator == int_zero || b.numerator == int_zero)
        return zero;
    if (!a.isPositive)
    {
        if (b.isPositive)
            isPos = false;
    }
    else if (!b.isPositive)
        isPos = false;

    Number new_den = a.denominator * b.denominator;
    Number new_num = a.numerator * b.numerator;

    if (!isPos)
        new_num.changeSign();

    return Decimal(new_num, new_den);
}

void Decimal::printFraction()
{
    cout << "   ";
    cout << this->numerator;
    if (!this->isPositive)
        cout << "- ";
    cout << "******" << endl;
    cout << "   ";
    cout << this->denominator;
}

bool Decimal::isInteger()
{
    Number zero;
    Number reminder = this->numerator % this->denominator;
    if (reminder == zero)
        return true;
    return false;
}

void Decimal::divideSelf()
{
    Number temp1 = this->numerator;
    Number temp2 = this->denominator;

    // Change all numbers to positive
    bool aa = true;
    if (temp1.getSign())
    {
        if (!temp2.getSign())
        {
            temp2.changeSign();
            aa = false;
        }
    }
    else
    {
        temp1.changeSign();
        if (temp2.getSign())
            aa = false;
        else
            temp2.changeSign();
    }

    Number quotient = temp1 / temp2;
    Number reminder = temp1 % temp2;

    int ten_dig[2] = {0, 1};
    int one_dig[1] = {1};
    Number ten(ten_dig, 2, true);
    Number one(one_dig, 1, true);
    Number zero;
    int ten_times = 0;

    while (!(reminder == zero))
    {
        ten_times++;
        reminder = reminder * ten;
        Number quot_temp = reminder / temp2;
        // In this step, we assume that quotient is always one digit
        quotient.insertFront(quot_temp[0]);
        reminder = reminder % temp2;

        // 100 decimal digits of precision
        if (ten_times == 100)
            break;
    }

    Number one_temp(one_dig, 1, true);
    for (int i = 0; i < ten_times; i++)
        one_temp = one_temp * ten;

    if (!aa)
        quotient.changeSign();

    this->numerator = quotient;
    this->denominator = one_temp;
}

string Decimal::toFractString() const
// This function returns a string in fraction mode
// # -> Separator between numerator and denominator
{
    string res;
    if (!this->isPositive)
        res += "-";
    res += this->numerator.toString();
    res += Decimal::fraction_delimiter;
    res += this->denominator.toString();

    return res;
}

string Decimal::toString() const
{
    string res;
    Decimal temp = *this;

    temp.divideSelf();

    if (!temp.isPositive)
        res += "-";

    int noZeroPositions = temp.numerator.getSize() - temp.denominator.getSize() + 1;

    if (noZeroPositions == 0)
        res += "0";
    else if (noZeroPositions < 0)
    {
        res += "0.";
        for (int i = 0; i < -noZeroPositions; i++)
            res += "0";
    }

    for (int i = 0; i < temp.numerator.getSize(); i++)
    {
        if (i == noZeroPositions)
            res += ".";
        res += to_string(temp.numerator[i]);
    }

    return res;
}

const Decimal Decimal::simplify(const Decimal &num) const
{
    Decimal object = num;
    Number GCD = getGCD(object.denominator, object.numerator);
    object.denominator = object.denominator / GCD;
    object.numerator = object.numerator / GCD;
    return object;
}

ostream &operator<<(ostream &strm, const Decimal &num)
{
    Decimal temp = num;

    temp.divideSelf();

    if (!temp.isPositive)
        strm << "-";

    int noZeroPositions = temp.numerator.getSize() - temp.denominator.getSize() + 1;

    if (noZeroPositions == 0)
        strm << "0";
    else if (noZeroPositions < 0)
    {
        strm << "0.";
        for (int i = 0; i < -noZeroPositions; i++)
            strm << "0";
    }

    for (int i = 0; i < temp.numerator.getSize(); i++)
    {
        if (i == noZeroPositions)
            strm << ".";
        strm << temp.numerator[i];
    }
    strm << endl;

    return strm;
}

istream &operator>>(istream &strm, Decimal &num)
// There are two input mode for storing a Decimal
// Mode 1: Using the . to separate Integer part with Decimal part
// Mode 2: Using the # to separate between numerator and denominator
{
    int a[1] = {1};
    int b[2] = {0, 1};
    Number one(a, 1, true);
    Number ten(b, 2, true);

    string numberString;
    strm >> numberString;
    int size = numberString.size();

    // Determines the input mode
    bool hasFractDel = false;
    for (int i = 0; i < size; i++)
    {
        if (numberString[i] == Decimal::fraction_delimiter)
        {
            hasFractDel = true;
            break;
        }
    }

    // Dot mode
    if (!hasFractDel)
    {
        vector<int> numDigits;
        bool isPositive = true;
        int decimalPlaces = 0;
        bool decimalActivated = false;

        for (int i = size - 1; i >= 0; i--)
        {
            char currentDigit = numberString[i];
            if (i == 0)
            {
                if (currentDigit == '-')
                {
                    isPositive = false;
                    continue;
                }
            }

            if (currentDigit == '.')
            {
                if (decimalActivated == false)
                {
                    decimalActivated = true;
                    continue;
                }
                else
                {
                    cout << "[Error]: Invalid input (at Decimal::operator>>).\n";
                    return strm;
                }
            }

            int intDigit = currentDigit - '0';
            if (intDigit < 0 || intDigit > 9)
            {
                cout << "[Error]: Invalid input (at Decimal::operator>>).\n";
                return strm;
            }

            numDigits.push_back(intDigit);
            if (decimalActivated)
                decimalPlaces++;
        }

        decimalPlaces = numDigits.size() - decimalPlaces;
        if (!decimalActivated)
            decimalPlaces = 0;

        for (int i = 0; i < decimalPlaces; i++)
            one = one * ten;

        for (int i = numDigits.size() - 1; i >= 0; i--)
        {
            if (numDigits[i] != 0)
                break;
            numDigits.pop_back();
        }

        if (numDigits.size() == 0)
            numDigits.push_back(0);

        int *c = &numDigits[0];
        Number numerator(c, numDigits.size(), isPositive);

        // Simplify zeros
        if (decimalActivated)
        {
            for (int i = numerator.getSize() - 1; i >= 0; i--)
            {
                if (numerator[i] != 0)
                    break;
                numerator = numerator / ten;
                one = one / ten;
            }
        }

        Decimal temp(numerator, one);
        num = temp;
    }
    // Fraction mode
    else
    {
        string nume, den;
        stringstream ss(numberString);

        getline(ss, nume, Decimal::fraction_delimiter);
        getline(ss, den);

        // cout << "[log]: Numerator: " << nume << endl;
        // cout << "[log]: Denominator: " << den << endl;

        Number numerator, denominator;
        ss.clear();
        ss.str(nume);
        ss >> numerator;
        ss.clear();
        ss.str(den);
        ss >> denominator;

        Decimal res(numerator, denominator);
        num = res;
    }

    return strm;
}

bool Decimal::operator==(const Decimal &num) const
{
    return (this->isPositive == num.isPositive && this->numerator == num.numerator && this->denominator == num.denominator);
}

Decimal &Decimal::operator=(const Decimal &num)
{
    this->isPositive = num.isPositive;
    this->numerator = num.numerator;
    this->denominator = num.denominator;

    return *this;
}

Decimal Decimal::power(const Decimal &times)
{
    int x[] = {0, 1, 2};
    Number zero_num(x, 1, true);
    Number one_num(x + 1, 1, true);
    Number two_num(x + 2, 1, true);
    Number NumTimes = times.numerator;
    Number product = one_num;
    Number DecTimes = times.denominator;

    Decimal zero(zero_num, zero_num);
    Decimal one(one_num, one_num);
    Decimal two(two_num, one_num);
    Decimal temp = one;
    Decimal compare = times;

    if (times.denominator == zero_num || times.numerator == zero_num)
    {
        temp = one;
        return temp;
    }
    if (!times.isPositive)
    {
        if (!this->isPositive)
        {
            if (compare.numerator % two_num == zero_num)
            {
                while (1)
                {
                    temp.denominator = temp.denominator * this->numerator;
                    temp.numerator = temp.numerator * this->denominator;
                    NumTimes = NumTimes - one_num;
                    if (NumTimes == zero_num)
                        break;
                }
                while (1)
                {
                    NumTimes = NumTimes + one_num;
                    DecTimes = times.denominator;
                    product = one_num;
                    while (1)
                    {
                        product = product * NumTimes;
                        DecTimes = DecTimes - one_num;
                        if (DecTimes == zero_num)
                            break;
                    }
                    if (temp.numerator == product)
                    {
                        temp.numerator = NumTimes;
                        break;
                    }
                }
                NumTimes = zero_num;
                while (1)
                {
                    NumTimes = NumTimes + one_num;
                    DecTimes = times.denominator;
                    product = one_num;
                    while (1)
                    {
                        product = product * NumTimes;
                        DecTimes = DecTimes - one_num;
                        if (DecTimes == zero_num)
                            break;
                    }
                    if (temp.denominator == product)
                    {
                        temp.denominator = NumTimes;
                        break;
                    }
                }
                return temp;
            }
            temp.isPositive = false;
            while (1)
            {
                temp.denominator = temp.denominator * this->numerator;
                temp.numerator = temp.numerator * this->denominator;
                NumTimes = NumTimes - one_num;
                if (NumTimes == zero_num)
                    break;
            }
            while (1)
            {
                NumTimes = NumTimes + one_num;
                DecTimes = times.denominator;
                product = one_num;
                while (1)
                {
                    product = product * NumTimes;
                    DecTimes = DecTimes - one_num;
                    if (DecTimes == zero_num)
                        break;
                }
                if (temp.numerator == product)
                {
                    temp.numerator = NumTimes;
                    break;
                }
            }
            NumTimes = zero_num;
            while (1)
            {
                NumTimes = NumTimes + one_num;
                DecTimes = times.denominator;
                product = one_num;
                while (1)
                {
                    product = product * NumTimes;
                    DecTimes = DecTimes - one_num;
                    if (DecTimes == zero_num)
                        break;
                }
                if (temp.denominator == product)
                {
                    temp.denominator = NumTimes;
                    break;
                }
            }
            return temp;
        }
        while (1)
        {
            temp.denominator = temp.denominator * this->numerator;
            temp.numerator = temp.numerator * this->denominator;
            NumTimes = NumTimes - one_num;
            if (NumTimes == zero_num)
                break;
        }
        while (1)
        {
            NumTimes = NumTimes + one_num;
            DecTimes = times.denominator;
            product = one_num;
            while (1)
            {
                product = product * NumTimes;
                DecTimes = DecTimes - one_num;
                if (DecTimes == zero_num)
                    break;
            }
            if (temp.numerator == product)
            {
                temp.numerator = NumTimes;
                break;
            }
        }
        NumTimes = zero_num;
        while (1)
        {
            NumTimes = NumTimes + one_num;
            DecTimes = times.denominator;
            product = one_num;
            while (1)
            {
                product = product * NumTimes;
                DecTimes = DecTimes - one_num;
                if (DecTimes == zero_num)
                    break;
            }
            if (temp.denominator == product)
            {
                temp.denominator = NumTimes;
                break;
            }
        }
        return temp;
    }
    if (!this->isPositive)
    {
        if (compare.numerator % two_num == zero_num)
        {
            while (1)
            {
                temp.denominator = temp.denominator * this->denominator;
                temp.numerator = temp.numerator * this->numerator;
                NumTimes = NumTimes - one_num;
                if (NumTimes == zero_num)
                    break;
            }
            while (1)
            {
                NumTimes = NumTimes + one_num;
                DecTimes = times.denominator;
                product = one_num;
                while (1)
                {
                    product = product * NumTimes;
                    DecTimes = DecTimes - one_num;
                    if (DecTimes == zero_num)
                        break;
                }
                if (temp.numerator == product)
                {
                    temp.numerator = NumTimes;
                    break;
                }
            }
            NumTimes = zero_num;
            while (1)
            {
                NumTimes = NumTimes + one_num;
                DecTimes = times.denominator;
                product = one_num;
                while (1)
                {
                    product = product * NumTimes;
                    DecTimes = DecTimes - one_num;
                    if (DecTimes == zero_num)
                        break;
                }
                if (temp.denominator == product)
                {
                    temp.denominator = NumTimes;
                    break;
                }
            }
            return temp;
        }
        temp.isPositive = false;
        while (1)
        {
            temp.denominator = temp.denominator * this->denominator;
            temp.numerator = temp.numerator * this->numerator;
            NumTimes = NumTimes - one_num;
            if (NumTimes == zero_num)
                break;
        }
        while (1)
        {
            NumTimes = NumTimes + one_num;
            DecTimes = times.denominator;
            product = one_num;
            while (1)
            {
                product = product * NumTimes;
                DecTimes = DecTimes - one_num;
                if (DecTimes == zero_num)
                    break;
            }
            if (temp.numerator == product)
            {
                temp.numerator = NumTimes;
                break;
            }
        }
        NumTimes = zero_num;
        while (1)
        {
            NumTimes = NumTimes + one_num;
            DecTimes = times.denominator;
            product = one_num;
            while (1)
            {
                product = product * NumTimes;
                DecTimes = DecTimes - one_num;
                if (DecTimes == zero_num)
                    break;
            }
            if (temp.denominator == product)
            {
                temp.denominator = NumTimes;
                break;
            }
        }
        return temp;
    }
    while (1)
    {
        temp.denominator = temp.denominator * this->denominator;
        temp.numerator = temp.numerator * this->numerator;
        NumTimes = NumTimes - one_num;
        if (NumTimes == zero_num)
            break;
    }
    while (1)
    {
        NumTimes = NumTimes + one_num;
        DecTimes = times.denominator;
        product = one_num;
        while (1)
        {
            product = product * NumTimes;
            DecTimes = DecTimes - one_num;
            if (DecTimes == zero_num)
                break;
        }
        if (temp.numerator == product)
        {
            temp.numerator = NumTimes;
            break;
        }
    }
    NumTimes = zero_num;
    while (1)
    {
        NumTimes = NumTimes + one_num;
        DecTimes = times.denominator;
        product = one_num;
        while (1)
        {
            product = product * NumTimes;
            DecTimes = DecTimes - one_num;
            if (DecTimes == zero_num)
                break;
        }
        if (temp.denominator == product)
        {
            temp.denominator = NumTimes;
            break;
        }
    }
    return temp;
}