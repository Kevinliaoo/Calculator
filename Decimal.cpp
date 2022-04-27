#include <iostream>
#include "Number.h"

using namespace std;

/* ********** DECIMAL ********** */

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

Decimal Decimal::operator+(const Decimal &num)
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
{
    int a[1] = {1};
    int b[2] = {0, 1};
    Number one(a, 1, true);
    Number ten(b, 2, true);

    string numberString;
    strm >> numberString;
    int size = numberString.size();

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
                cout << "Error: Invalid input\n";
                return strm;
            }
        }

        int intDigit = currentDigit - '0';
        if (intDigit < 0 || intDigit > 9)
        {
            cout << "Error: Invalid input\n";
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