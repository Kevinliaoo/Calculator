#include <iostream>
#include "Number.h"

using namespace std;

/* ********** NUMBER ********** */

// Constructors
Number::Number()
// Default constructor: build zero
{
    this->digits.push_back(0);
    this->isPositive = true;
    this->size = 1;
}

Number::Number(int *a, int size, bool isPositive)
// Precondition: a must be clean and reverted
{
    this->isPositive = isPositive;
    this->size = size;

    for (int i = 0; i < size; i++)
        this->digits.push_back(a[i]);
}

// Operator overloading
Number &Number::operator=(const Number &number)
{
    this->digits.clear();
    this->size = number.size;
    this->isPositive = number.isPositive;
    for (int i = 0; i < size; i++)
        this->digits.push_back(number.digits[i]);

    return *this;
}

int Number::operator[](int index) const
// This function returns the digit at a position
// Precondition: index is the number of the digit, it must be
// greater or equal than 0 and smaller than the number's size
{
    return this->digits[this->size - 1 - index];
}

bool Number::operator>(const Number &number) const
// This comparison does not consider sign
{
    if (this->size > number.size)
        return true;
    else if (this->size < number.size)
        return false;
    else
    {
        for (int i = this->size - 1; i >= 0; i--)
        {
            if (this->digits[i] > number.digits[i])
                return true;
            else if (this->digits[i] < number.digits[i])
                return false;
        }
    }

    return false;
}

bool Number::operator==(const Number &number) const
{
    // 0 is equal to -0
    if (this->size == number.size && this->size == 1)
        if (this->digits[0] == number.digits[0] && this->digits[0] == 0)
            return true;

    if (this->size != number.size)
        return false;

    if (this->isPositive != number.isPositive)
        return false;

    for (int i = 0; i < this->size; i++)
        if (this->digits[i] != number.digits[i])
            return false;

    return true;
}

Number Number::operator*(const Number &number)
{
    bool isPos = true;
    if (!this->isPositive)
    {
        if (number.isPositive)
            isPos = false;
    }
    else
    {
        if (!number.isPositive)
            isPos = false;
    }

    int next = 0, current = 0;
    int newSize;
    int *product = new int[size + number.size];
    for (int i = 0; i < size + number.size; i++)
    {
        product[i] = 0;
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < number.size; j++)
        {
            if (this->digits[i] * number.digits[j] >= 10)
            {
                next = this->digits[i] * number.digits[j] / 10;
            }
            if (current + (this->digits[i] * number.digits[j]) % 10 >= 10)
            {
                next += (current + (this->digits[i] * number.digits[j]) % 10) / 10;
            }
            product[i + j] += (current + (this->digits[i] * number.digits[j]) % 10) % 10;
            if (product[i + j] >= 10)
            {
                next += product[i + j] / 10;
                product[i + j] = product[i + j] % 10;
            }
            if (j == number.size - 1)
            {
                if (next != 0)
                {
                    product[i + j + 1] = next;
                    newSize = i + j + 2;
                }
                else
                    newSize = i + j + 1;
            }
            current = next;
            next = 0;
        }
        current = 0;
        next = 0;
    }
    return Number(product, newSize, isPos);
}

Number Number::operator-(const Number &number)
{
    if (this->isPositive)
    {
        if (this->operator>(number))
        {
            if (number.isPositive)
                return this->subtract(number);
            else
            {
                Number temp = number;
                temp.changeSign();
                return this->add(temp);
            }
        }
        else
        {
            if (number.isPositive)
            {
                Number temp1 = *this;
                Number temp2 = number;
                temp1 = temp2.subtract(temp1);
                temp1.changeSign();
                return temp1;
            }
            else
            {
                Number temp = number;
                temp.changeSign();
                return temp.add(*this);
            }
        }
    }
    else
    {
        if (this->operator>(number))
        {
            if (number.isPositive)
            {
                Number temp1 = *this;
                temp1.changeSign();
                temp1 = temp1.add(number);
                temp1.changeSign();
                return temp1;
            }
            else
            {
                Number temp1 = *this;
                Number temp2 = number;
                temp1.changeSign();
                temp2.changeSign();
                temp1 = temp1.subtract(temp2);
                temp1.changeSign();
                return temp1;
            }
        }
        else
        {
            if (number.isPositive)
            {
                Number temp1 = *this;
                Number temp2 = number;
                temp1.changeSign();
                temp1 = temp2.add(temp1);
                temp1.changeSign();
                return temp1;
            }
            else
            {
                Number temp1 = *this;
                Number temp2 = number;
                temp1.changeSign();
                temp2.changeSign();
                temp1 = temp2.subtract(temp1);
                return temp1;
            }
        }
    }
}

Number Number::operator+(const Number &number)
{
    if (this->isPositive)
    {
        if (this->operator>(number))
        {
            if (number.isPositive)
                return this->add(number);
            else
            {
                Number temp = number;
                temp.changeSign();
                return this->subtract(temp);
            }
        }
        else
        {
            if (number.isPositive)
                return number.add(*this);
            else
            {
                Number temp1 = *this;
                Number temp2 = number;
                temp2.changeSign();
                temp1 = temp2.subtract(temp1);
                temp1.changeSign();
                return temp1;
            }
        }
    }
    else
    {
        if (this->operator>(number))
        {
            if (number.isPositive)
            {
                Number temp = *this;
                temp.changeSign();
                temp = temp.subtract(number);
                temp.changeSign();
                return temp;
            }
            else
            {
                Number temp1 = *this;
                Number temp2 = number;
                temp1.changeSign();
                temp2.changeSign();
                temp1 = temp1.add(temp2);
                temp1.changeSign();
                return temp1;
            }
        }
        else
        {
            if (number.isPositive)
            {
                Number temp1 = *this;
                Number temp2 = number;
                temp1.changeSign();
                temp1 = temp2.subtract(temp1);
                return temp1;
            }
            else
            {
                Number temp1 = *this;
                Number temp2 = number;
                temp1.changeSign();
                temp2.changeSign();
                temp1 = temp2.add(temp1);
                temp1.changeSign();
                return temp1;
            }
        }
    }
}

Number Number::operator/(const Number &number)
{

    int a[1] = {0};
    Number zero(a, 1, true);
    int b[1] = {1};
    Number one(b, 1, true);

    if (number == zero)
    {
        cout << "Error: Can not divide by zero!" << endl;
        return zero;
    }

    if (this->operator==(number))
        return one;

    Number temp = *this;
    Number temp2 = number;

    bool aa = true;
    if (temp.isPositive)
    {
        if (!temp2.isPositive)
        {
            temp2.changeSign();
            aa = false;
        }
    }
    else
    {
        temp.changeSign();
        if (number.isPositive)
            aa = false;
        else
            temp2.changeSign();
    }

    if (temp == temp2)
        return Number(b, 1, aa);
    // number is greater than this, so I return zero
    if (!(temp > temp2))
        return zero;

    while (temp > temp2)
    {
        zero = zero + one;
        temp = temp - temp2;
    }

    if (temp == temp2)
        zero = zero + one;

    if (!aa)
        zero.changeSign();

    return zero;
}

Number Number::operator%(const Number &number)
{
    int a[1] = {0};
    Number zero(a, 1, true);

    if (this->operator==(number))
        return zero;

    // number is greater than this, so I return zero
    if (!this->operator>(number))
        return *this;

    Number temp = *this;
    Number temp2 = number;

    bool aa = true;
    if (temp.isPositive)
    {
        if (!temp2.isPositive)
            temp2.changeSign();
    }
    else
    {
        aa = false;
        temp.changeSign();
        if (!temp2.isPositive)
            temp2.changeSign();
    }

    while (temp > temp2)
        temp = temp - temp2;

    if (temp == temp2)
        return zero;

    if (!aa)
        temp.changeSign();

    return temp;
}

// Helper functions
Number Number::add(const Number &number) const
// This function adds two numbers
// Precondition: both this and number are considered positive numbers
// and this is biger than number
// Postcondition: returns this + number (always positive)
{
    int i = 0, j = 0, k = 0;
    int digit_size = this->size + 1;
    int *digit_temp = new int[digit_size];
    for (int x = 0; x < digit_size; x++)
        digit_temp[x] = 0;

    bool carry = false;
    while (i < this->size && j < number.size)
    {
        int temp = this->digits[i] + number.digits[j];
        if (carry)
        {
            temp++;
            carry = false;
        }

        if (temp > 9)
        {
            carry = true;
            temp -= 10;
        }
        digit_temp[k] = temp;

        i++;
        j++;
        k++;
    }
    while (i < this->size)
    {
        int temp = carry ? this->digits[i] + 1 : this->digits[i];
        if (carry)
            carry = false;
        if (temp > 9)
        {
            carry = true;
            temp -= 10;
        }

        digit_temp[k] = temp;
        i++;
        k++;
    }
    if (carry)
        digit_temp[k] = 1;

    // Remove useless zeros in the front
    int countZeros = 0;
    for (int x = digit_size - 1; x >= 0; x--)
    {
        if (digit_temp[x] == 0)
            countZeros++;
        else
            break;
    }

    if (digit_size == countZeros)
        countZeros--;

    int *temp = new int[digit_size - countZeros];
    for (int x = 0; x < digit_size - countZeros; x++)
        temp[x] = digit_temp[x];

    return Number(temp, digit_size - countZeros, true);
}

Number Number::subtract(const Number &number)
// This function substract a number to itself (positive result)
// Precondition: number is smaller than this, both numbers are considered positive
// Postcondition: return the this - number (always positive)
{
    int i = 0, j = 0, k = 0;
    int *dig_temp = new int[this->size];
    for (int x = 0; x < this->size; x++)
        dig_temp[x] = 0;

    while (i < this->size && j < number.size)
    {
        if (this->digits[i] >= number.digits[j])
            dig_temp[k] = this->digits[i] - number.digits[j];
        else
        {
            this->digits[i + 1] -= 1;
            dig_temp[k] = this->digits[i] + 10 - number.digits[j];
        }

        i++;
        j++;
        k++;
    }
    while (i < this->size)
    {
        if (this->digits[i] >= 0)
            dig_temp[k] = this->digits[i];
        else
        {
            this->digits[i + 1] -= 1;
            dig_temp[k] = this->digits[i] + 10;
        }

        i++;
        j++;
        k++;
    }

    // Remove useless zeros in the front
    int countZeros = 0;
    for (int x = this->size - 1; x >= 0; x--)
    {
        if (dig_temp[x] == 0)
            countZeros++;
        else
            break;
    }
    // If the number is 0, remain one position
    if (this->size == countZeros)
        countZeros--;

    // Make a copy without the useless zeros
    int *temp = new int[this->size - countZeros];
    for (int x = 0; x < this->size - countZeros; x++)
        temp[x] = dig_temp[x];

    return Number(temp, this->size - countZeros, true);
}

Number Number::factorial()
{
    int x[] = {1, 0};
    Number temp = *this;
    Number times = *this;
    Number one(x, 1, true);
    Number zero(x + 1, 1, true);
    times = times - one;
    while (times > zero)
    {
        temp = temp * times;
        times = times - one;
    }
    return temp;
}

void Number::changeSign()
// Changes the sign of the number
{
    this->isPositive = !this->isPositive;
}

bool Number::getSign()
// Getter function for isPositive
{
    return this->isPositive;
}

void Number::printNumber() const
// Display the number
{
    if (!this->isPositive)
        cout << "-";
    for (int i = 0; i < this->size; i++)
        cout << this->digits[this->size - 1 - i];
    cout << endl;
}

bool Number::isEqualZero()
// Returns true if the number is zero, ignoring sign
{
    if (this->size == 1)
    {
        if (this->digits[0] == 0)
            return true;
    }
    return false;
}

void Number::insertFront(int d)
// Inserts a digit at the end of the numer
// (at the front of the vector digits)
{
    vector<int> new_digits;
    new_digits.push_back(d);
    for (int i = 0; i < this->digits.size(); i++)
        new_digits.push_back(this->digits[i]);

    this->digits.clear();
    this->size = new_digits.size();
    this->digits = new_digits;
}

int Number::getSize()
{
    return this->digits.size();
}

// Friend functions

Number getGCD(const Number &num1, const Number &num2)
// Get the Greatest Common Divisor between two numbers
// Precondition: num1 and num2 are different positive numbers
{
    if (!num1.isPositive || !num2.isPositive)
        cout << "Error: Can not get GCD of negative values!" << endl;

    int a[1] = {0};
    Number zero(a, 1, true);

    if (num2 == zero)
        return num1;

    Number temp = num1;

    return getGCD(num2, temp % num2);
}

Number getLCM(const Number &num1, const Number &num2)
// Get the Least Common Multiple between two numbers
// Precondition: num1 and num2 are different positive numbers
{
    Number temp = num1;
    return (temp / getGCD(num1, num2)) * num2;
}

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