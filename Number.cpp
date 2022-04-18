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
    }
    return Number(product, newSize, isPos);
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