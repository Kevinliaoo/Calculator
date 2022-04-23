#include <iostream>
#include <vector>
#include "Number.h"

using namespace std;

Decimal decimalDivision(const Integer &num1, const Integer num2);

int main()
{
    Decimal dec_1;
    cout << dec_1;
    cin >> dec_1;
    cout << dec_1;
}

Decimal decimalDivision(const Integer &num1, const Integer num2)
// Decimal division. Converts denominator in a number power of 10
{
    Integer temp1 = num1;
    Integer temp2 = num2;

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

    Integer quotient = temp1 / temp2;
    Integer reminder = temp1 % temp2;

    int ten_dig[2] = {0, 1};
    int one_dig[1] = {1};
    Integer ten(ten_dig, 2, true);
    Integer one(one_dig, 1, true);
    Integer zero;
    int ten_times = 0;

    while (!(reminder == zero))
    {
        ten_times++;
        reminder = reminder * ten;
        Integer quot_temp = reminder / temp2;
        // In this step, we assume that quotient is always one digit
        quotient.insertFront(quot_temp[0]);
        reminder = reminder % temp2;

        // 100 decimal digits of precision
        if (ten_times == 100)
            break;
    }

    Integer one_temp(one_dig, 1, true);
    for (int i = 0; i < ten_times; i++)
        one_temp = one_temp * ten;

    if (!aa)
        quotient.changeSign();

    return Decimal(quotient, one_temp);
}