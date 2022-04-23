#include <iostream>
#include "Number.h"

using namespace std;

/* ********** DECIMAL ********** */
Decimal::Decimal(const Integer &num, const Integer &den)
{
    Integer temp_num = num;
    Integer temp_den = den;

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
    Integer lcm = this->denominator;

    if (!(this->denominator == num.denominator))
        lcm = getLCM(this->denominator, num.denominator);

    Integer temp1 = this->numerator;
    Integer temp2 = num.numerator;

    if (!this->isPositive)
        temp1.changeSign();
    if (!num.isPositive)
        temp2.changeSign();

    Integer temp_num = temp1 * (lcm / this->denominator) + temp2 * (lcm / num.denominator);

    return Decimal(temp_num, lcm);
}

Decimal Decimal::operator-(const Decimal &num)
{
    Integer lcm = this->denominator;

    if (!(this->denominator == num.denominator))
        lcm = getLCM(this->denominator, num.denominator);

    Integer temp1 = this->numerator;
    Integer temp2 = num.numerator;

    if (!this->isPositive)
        temp1.changeSign();
    if (!num.isPositive)
        temp2.changeSign();

    Integer temp_num = temp1 * (lcm / this->denominator) - temp2 * (lcm / num.denominator);

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
    int a[1] = {0};
    Integer zero(a, 1, true);
    Integer reminder = this->numerator % this->denominator;
    if (reminder == zero)
        return true;
    return false;
}

ostream &operator<<(ostream &strm, const Decimal &num)
{
    Decimal temp = num;

    if (!temp.isPositive)
        strm << "-";

    int noZeroPositions = temp.numerator.getSize() - temp.denominator.getSize() + 1;

    if (noZeroPositions == 0)
        cout << "0";

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
    Integer one(a, 1, true);
    Integer ten(b, 2, true);

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
    for (int i = 0; i < decimalPlaces; i++)
        one = one * ten;

    for (int i = numDigits.size() - 1; i >= 0; i--)
    {
        if (numDigits[i] != 0)
            break;
        numDigits.pop_back();
    }

    int *c = &numDigits[0];
    Integer numerator(c, numDigits.size(), isPositive);

    Decimal temp(numerator, one);
    num = temp;

    return strm;
}
