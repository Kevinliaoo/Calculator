#include <iostream>
#include "Number.h"

using namespace std;

Number::Number(int *a, int size, bool isPositive)
// Precondition: a must be clean and reverted
{
    this->isPositive = isPositive;
    this->size = size;

    for (int i = 0; i < size; i++)
        this->digits.push_back(a[i]);
}

Number &Number::operator=(const Number &number)
{
    this->digits.clear();
    this->size = number.size;
    for (int i = 0; i < size; i++)
        this->digits.push_back(number.digits[i]);

    return *this;
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

void Number::changeSign()
{
    this->isPositive = !this->isPositive;
}

bool Number::operator>(const Number &number)
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

void Number::printNumber()
// Display the number
{
    if (!this->isPositive)
        cout << "-";
    for (int i = 0; i < this->size; i++)
        cout << this->digits[this->size - 1 - i];
    cout << endl;
}