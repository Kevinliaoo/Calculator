#include <iostream>
#include <string>
#include <sstream>
#include "Number.h"

using namespace std;

/* ********** DECIMAL ********** */

char Decimal::fraction_delimiter = '#';
char Decimal::decimal_point = '.';
int Decimal::max_decimal_digits = 100;

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

    {
        // Check if the denominator is already y power of 10
        int i = 0;
        for (i = 0; i < temp2.getSize(); i++)
        {
            if (i == 0 && temp2[i] == 1)
                continue;
            if (i > 0 && temp2[i] != 0)
                break;
        }
        if (i == temp2.getSize() && i > 1)
            return;
    }

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

    int decimalPlaces = temp.numerator.getSize() - 1;

    for (int i = 0; i < Decimal::max_decimal_digits - decimalPlaces; i++)
        res += '0';

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
    string output = num.toString();
    strm << output << endl;
    return strm;
}

istream &operator>>(istream &strm, Decimal &num)
// There are two input mode for storing a Decimal
// Mode 1: Using the . to separate Integer part with Decimal part
// Mode 2: Using the # to separate between numerator and denominator
{
    string numberString;
    strm >> numberString;

    bool isPositive = numberString[0] == Number::minus_sign ? false : true;
    // Remove the negative sign
    if (!isPositive)
        numberString.erase(0, 1);

    // Determines the input mode
    int dotIndex = -1;
    int fdelIndex = -1;
    for (int i = 0; i < numberString.size(); i++)
    {
        if (numberString[i] == Decimal::fraction_delimiter && fdelIndex == -1 && dotIndex == -1)
            fdelIndex = i;
        else if (numberString[i] == Decimal::decimal_point && dotIndex == -1 && fdelIndex == -1)
            dotIndex = i;
        else if (numberString[i] - '0' >= 0 && numberString[i] - '0' <= 9)
            continue;
        else
        {
            if (fdelIndex != -1 && i == (fdelIndex + 1) && numberString[i] == Number::minus_sign)
                continue;
            cout << "[Error]: Invalid input (at Decimal::operator>>).\n";
            return strm;
        }
    }

    // No decimal point nor fraction
    if (dotIndex == -1 && fdelIndex == -1)
    {
        Number numerator;
        stringstream ss(numberString);
        ss >> numerator;
        if (!isPositive)
            numerator.changeSign();
        Decimal res(numerator);
        num = res;
    }
    // Decimal point
    else if (dotIndex >= 0 && fdelIndex == -1)
    {
        string denominator_s = "1";
        const char zero_c = '0';

        int decimalPlaces = dotIndex != -1 ? numberString.size() - dotIndex - 1 : 0;
        if (dotIndex >= 0)
            numberString.erase(dotIndex, 1);

        for (int i = 0; i < decimalPlaces; i++)
            denominator_s += zero_c;

        // Remove unnecessary zeros on the back
        int num_i = numberString.size() - 1;
        int den_i = denominator_s.size() - 1;
        while (numberString[num_i] == zero_c && numberString.size() > 0 && denominator_s.size() > 1)
        {
            numberString.erase(num_i, 1);
            denominator_s.erase(den_i, 1);

            num_i--;
            den_i--;
        }

        Number numerator, denominator;

        stringstream ss(numberString);
        ss >> numerator;
        ss.clear();
        ss.str(denominator_s);
        ss >> denominator;

        if (!isPositive)
            numerator.changeSign();

        Decimal res(numerator, denominator);
        num = res;
    }
    // Fraction mode
    else if (dotIndex == -1 && fdelIndex >= 0)
    {
        string num_s, den_s;

        num_s = numberString.substr(0, fdelIndex);
        den_s = numberString.substr(fdelIndex + 1, numberString.size() - 1);

        if (den_s[0] == Number::minus_sign)
        {
            isPositive = !isPositive;
            den_s.erase(0, 1);
        }

        Number numerator, denominator;
        stringstream ss(num_s);
        ss >> numerator;
        ss.clear();
        ss.str(den_s);
        ss >> denominator;

        if (!isPositive)
            numerator.changeSign();

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

Decimal Decimal::power(const Decimal &times) const
{
    int x[] = {0, 1, 2};
    Number zero_num(x, 1, true);
    Number one_num(x + 1, 1, true);
    Number two_num(x + 2, 1, true);

    Number product = one_num;

    Decimal zero(zero_num, one_num);
    Decimal one(one_num, one_num);
    Decimal two(two_num, one_num);
    Decimal temp = one;
    Decimal compare = times;
    compare = compare.simplify(compare);
    Number NumTimes = compare.numerator;
    Number DecTimes = compare.denominator;
    if (compare.denominator == zero_num || compare.numerator == zero_num)
    {
        temp = one;
        return temp;
    }
    if (!compare.isPositive)
    {
        if (!this->isPositive)
        {
            if (compare.numerator % two_num == zero_num)
            {
                temp.denominator = this->denominator;
                temp.numerator = this->numerator;
                DecTimes = DecTimes / two_num;
                while (1)
                {
                    if (DecTimes == zero_num)
                        break;
                    temp = temp.square();
                    DecTimes = DecTimes - one_num;
                }
                Decimal take = temp;
                temp = one;
                while (1)
                {
                    temp.denominator = temp.denominator * take.numerator;
                    temp.numerator = temp.numerator * take.denominator;
                    NumTimes = NumTimes - one_num;
                    if (NumTimes == zero_num)
                        break;
                }
                return temp;
            }
            temp.isPositive = false;
            temp.denominator = this->denominator;
            temp.numerator = this->numerator;
            DecTimes = DecTimes / two_num;
            while (1)
            {
                if (DecTimes == zero_num)
                    break;
                temp = temp.square();
                DecTimes = DecTimes - one_num;
            }
            Decimal take = temp;
            temp = one;
            while (1)
            {
                temp.denominator = temp.denominator * take.numerator;
                temp.numerator = temp.numerator * take.denominator;
                NumTimes = NumTimes - one_num;
                if (NumTimes == zero_num)
                    break;
            }
            return temp;
        }
        temp.denominator = this->denominator;
        temp.numerator = this->numerator;
        DecTimes = DecTimes / two_num;
        while (1)
        {
            if (DecTimes == zero_num)
                break;
            temp = temp.square();
            DecTimes = DecTimes - one_num;
        }
        Decimal take = temp;
        temp = one;
        while (1)
        {
            temp.denominator = temp.denominator * take.numerator;
            temp.numerator = temp.numerator * take.denominator;
            NumTimes = NumTimes - one_num;
            if (NumTimes == zero_num)
                break;
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
            DecTimes = DecTimes / two_num;
            while (1)
            {
                if (DecTimes == zero_num)
                    break;
                temp = temp.square();
                DecTimes = DecTimes - one_num;
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
        DecTimes = DecTimes / two_num;
        while (1)
        {
            if (DecTimes == zero_num)
                break;
            temp = temp.square();
            DecTimes = DecTimes - one_num;
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
    DecTimes = DecTimes / two_num;
    while (1)
    {
        if (DecTimes == zero_num)
            break;
        temp = temp.square();
        DecTimes = DecTimes - one_num;
    }
    return temp;
}

Decimal Decimal::square() const
{
    int x[] = {0, 1, 2};
    int y[] = {0, 2};
    int z[] = {0, 0, 1};
    Number int_zero(x, 1, true);
    Number int_one(x + 1, 1, true);
    if (!this->isPositive)
    {
        cout << "[Error]: Negative number does not admit square root.\n";
        return int_zero;
    }
    if (*this == int_zero)
        return int_zero;
    Number int_100(z, 3, true);
    Number int_ten(x, 2, true);
    Number int_twenty(y, 2, true);
    Decimal This = *this;
    This.divideSelf();
    int decSize = This.denominator.getSize();
    int numSize = This.numerator.getSize();
    int Int = numSize - decSize + 1;
    vector<int> temp_num;
    if (Int < 0)
    {
        Number remainder(x, 1, true);
        int time = 0;
        while (time < 100)
        {
            Number test(x + 1, 1, true);
            Number compare(x + 1, 1, true);
            int temp[2];
            Number now = remainder;
            if (time * 2 + 1 + Int < numSize && time * 2 + 1 + Int >= 0)
                temp[0] = This.numerator[time * 2 + 1 + Int];
            else
                temp[0] = 0;
            if (time * 2 + Int < numSize && time * 2 + Int >= 0)
                temp[1] = This.numerator[time * 2 + Int];
            else
                temp[1] = 0;
            if ((time * 2 + Int < numSize && time * 2 + Int >= 0) || (time * 2 + 1 + Int < numSize && time * 2 + 1 + Int >= 0))
            {
                Number t(temp, 2, true);
                now = now + t;
            }

            if (now == int_zero)
                temp_num.push_back(0);
            else
            {
                int *ptr = new int[temp_num.size()];
                for (int i = 0; i < temp_num.size(); i++)
                {
                    ptr[i] = temp_num[temp_num.size() - i - 1];
                }
                remainder = now;
                while (now > compare)
                {
                    compare = int_zero;
                    if (temp_num.size() > 0)
                    {
                        Number product(ptr, temp_num.size(), true);
                        compare = product * int_twenty;
                    }
                    compare = compare + test;
                    compare = compare * test;
                    Number r = now - compare;
                    if (r.getSign())
                        remainder = r;
                    test = test + int_one;
                }
                if (now == int_one)
                {
                    remainder = int_zero;
                    temp_num.push_back(test[0]);
                }
                else if (compare == now)
                {
                    remainder = int_zero;
                    test = test - int_one;
                    temp_num.push_back(test[0]);
                }
                else
                {
                    test = test - int_one;
                    test = test - int_one;
                    temp_num.push_back(test[0]);
                }
            }
            remainder = remainder * int_100;
            time++;
        }

        int *out_num = new int[temp_num.size()];
        for (int i = 0; i < temp_num.size(); i++)
        {
            out_num[i] = temp_num[temp_num.size() - i - 1];
        }
        Number new_num(out_num, temp_num.size(), true);
        Number dec(x + 1, 1, true);
        for (int i = 0; i < 100; i++)
        {
            dec = dec * int_ten;
        }
        return Decimal(new_num, dec);
    }
    if (Int % 2 == 1)
    {
        Number remainder(x, 1, true);
        int time = 0;

        while (time * 2 < Int)
        {
            Number test(x + 1, 1, true);
            Number compare(x + 1, 1, true);
            int temp[2];
            if (time != 0)
            {
                temp[0] = This.numerator[time * 2];
                temp[1] = This.numerator[time * 2 - 1];
            }
            else
            {
                temp[0] = This.numerator[0];
                temp[1] = 0;
            }
            Number t(temp, 2, true);
            Number now = remainder + t;
            if (now == int_zero)
                temp_num.push_back(0);
            else
            {
                int *ptr = new int[temp_num.size()];
                for (int i = 0; i < temp_num.size(); i++)
                {
                    ptr[i] = temp_num[temp_num.size() - i - 1];
                }
                remainder = now;
                while (now > compare)
                {
                    compare = int_zero;
                    if (temp_num.size() > 0)
                    {
                        Number product(ptr, temp_num.size(), true);
                        compare = product * int_twenty;
                    }
                    compare = compare + test;
                    compare = compare * test;
                    Number r = now - compare;
                    if (r.getSign())
                        remainder = r;
                    test = test + int_one;
                }
                if (now == int_one)
                {
                    remainder = int_zero;
                    temp_num.push_back(test[0]);
                }
                else if (compare == now)
                {
                    remainder = int_zero;
                    test = test - int_one;
                    temp_num.push_back(test[0]);
                }
                else
                {
                    test = test - int_one;
                    test = test - int_one;
                    temp_num.push_back(test[0]);
                }
            }
            remainder = remainder * int_100;
            time++;
        }
        int a = time;
        time = 0;
        int count = 0;
        vector<int> return_dec;

        while (time < 100)
        {
            Number test(x + 1, 1, true);
            Number compare(x + 1, 1, true);
            int temp[2];
            Number now = remainder;
            if ((a - 1) * 2 + 2 + time * 2 < numSize)
                temp[0] = This.numerator[(a - 1) * 2 + 2 + time * 2];
            else
                temp[0] = 0;
            if ((a - 1) * 2 + 1 + time * 2 < numSize)
                temp[1] = This.numerator[(a - 1) * 2 + 1 + time * 2];
            if ((a - 1) * 2 + 1 + time * 2 < numSize || (a - 1) * 2 + 2 + time * 2 < numSize)
            {
                Number t(temp, 2, true);
                now = now + t;
            }

            if (now == int_zero)
                temp_num.push_back(0);
            else
            {
                int *ptr = new int[temp_num.size()];
                for (int i = 0; i < temp_num.size(); i++)
                {
                    ptr[i] = temp_num[temp_num.size() - i - 1];
                }
                remainder = now;
                while (now > compare)
                {
                    compare = int_zero;
                    if (temp_num.size() > 0)
                    {
                        Number product(ptr, temp_num.size(), true);
                        compare = product * int_twenty;
                    }
                    compare = compare + test;
                    compare = compare * test;
                    Number r = now - compare;
                    if (r.getSign())
                        remainder = r;
                    test = test + int_one;
                }
                if (now == int_one)
                {
                    remainder = int_zero;
                    temp_num.push_back(test[0]);
                }
                else if (compare == now)
                {
                    remainder = int_zero;
                    test = test - int_one;
                    temp_num.push_back(test[0]);
                }
                else
                {
                    test = test - int_one;
                    test = test - int_one;
                    temp_num.push_back(test[0]);
                }
            }
            remainder = remainder * int_100;
            time++;
        }

        int *out_num = new int[temp_num.size()];
        for (int i = 0; i < temp_num.size(); i++)
        {
            out_num[i] = temp_num[temp_num.size() - i - 1];
        }
        Number new_num(out_num, temp_num.size(), true);
        Number dec(x + 1, 1, true);
        int Tsize = temp_num.size();
        if (Tsize - a > 0)
        {
            for (int i = 0; i < Tsize - a; i++)
            {
                dec = dec * int_ten;
            }
        }
        return Decimal(new_num, dec);
    }
    else
    {
        Number remainder(x, 1, true);
        int time = 0;

        while (time * 2 < Int)
        {
            Number test(x + 1, 1, true);
            Number compare(x + 1, 1, true);
            int temp[2];
            temp[0] = This.numerator[time * 2 + 1];
            temp[1] = This.numerator[time * 2];
            Number t(temp, 2, true);
            Number now = remainder + t;
            if (now == int_zero)
                temp_num.push_back(0);
            else
            {
                int *ptr = new int[temp_num.size()];
                for (int i = 0; i < temp_num.size(); i++)
                {
                    ptr[i] = temp_num[temp_num.size() - i - 1];
                }
                remainder = now;
                while (now > compare)
                {
                    compare = int_zero;
                    if (temp_num.size() > 0)
                    {
                        Number product(ptr, temp_num.size(), true);
                        compare = product * int_twenty;
                    }
                    compare = compare + test;
                    compare = compare * test;
                    Number r = now - compare;
                    if (r.getSign())
                        remainder = r;
                    test = test + int_one;
                }
                if (now == int_one)
                {
                    remainder = int_zero;
                    temp_num.push_back(test[0]);
                }
                else if (compare == now)
                {
                    remainder = int_zero;
                    test = test - int_one;
                    temp_num.push_back(test[0]);
                }
                else
                {
                    test = test - int_one;
                    test = test - int_one;
                    temp_num.push_back(test[0]);
                }
            }
            remainder = remainder * int_100;
            time++;
        }
        int diSize = numSize - Int;
        int a = time;
        time = 0;
        int count = 0;
        vector<int> return_dec;

        while (time < 100)
        {
            Number test(x + 1, 1, true);
            Number compare(x + 1, 1, true);
            int temp[2];
            Number now = remainder;
            if (a * 2 + time * 2 + 1 < numSize)
                temp[0] = This.numerator[a * 2 + time * 2 + 1];
            else
                temp[0] = 0;
            if (a * 2 + time * 2 < numSize)
                temp[1] = This.numerator[a * 2 + time * 2];
            if (a * 2 + time * 2 + 1 < numSize || a * 2 + time * 2 < numSize)
            {
                Number t(temp, 2, true);
                now = now + t;
            }

            if (now == int_zero)
                temp_num.push_back(0);
            else
            {
                int *ptr = new int[temp_num.size()];
                for (int i = 0; i < temp_num.size(); i++)
                {
                    ptr[i] = temp_num[temp_num.size() - i - 1];
                }
                remainder = now;
                while (now > compare)
                {
                    compare = int_zero;
                    if (temp_num.size() > 0)
                    {
                        Number product(ptr, temp_num.size(), true);
                        compare = product * int_twenty;
                    }
                    compare = compare + test;
                    compare = compare * test;
                    Number r = now - compare;
                    if (r.getSign())
                        remainder = now - compare;
                    test = test + int_one;
                }
                if (now == int_one)
                {
                    remainder = int_zero;
                    temp_num.push_back(test[0]);
                }
                else if (compare == now)
                {
                    remainder = int_zero;
                    test = test - int_one;
                    temp_num.push_back(test[0]);
                }
                else
                {
                    test = test - int_one;
                    test = test - int_one;
                    temp_num.push_back(test[0]);
                }
            }
            remainder = remainder * int_100;
            time++;
        }

        int *out_num = new int[temp_num.size()];
        for (int i = 0; i < temp_num.size(); i++)
        {
            out_num[i] = temp_num[temp_num.size() - i - 1];
        }
        Number new_num(out_num, temp_num.size(), true);
        Number dec(x + 1, 1, true);
        int Tsize = temp_num.size();
        if (Tsize - a > 0)
        {
            for (int i = 0; i < Tsize - a; i++)
            {
                dec = dec * int_ten;
            }
        }
        return Decimal(new_num, dec);
    }
}