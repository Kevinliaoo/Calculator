#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include "Number.h"

using namespace std;

Decimal decimalDivision(const Number &num1, const Number num2);
void printVariables(map<string, Decimal> &vars);
Decimal makeCalculation(stringstream &ss);

int main()
{
    /*
    map<string, Number> variables;
    stringstream ss;

    Integer i1;
    string aa = "-1234";
    ss.str(aa);

    cout << i1;
    ss >> i1;
    cout << i1;*/

    Number i1, i2;
    cin >> i1 >> i2;
    cout << i1;
    cout << i2;

    /*
        map<string, Decimal> variables;

        string inputMessage;
        stringstream ss;

        while (getline(cin, inputMessage))
        {
            ss.str(inputMessage);

            if (inputMessage.substr(0, 3) == "SET")
            // Set a variable
            {
                string datatype, varName, eqSign, value;
                ss >> eqSign >> datatype >> varName >> eqSign;

                if (datatype != "Integer" && datatype != "Decimal")
                {
                    cout << "Error: Invalid datatype";
                    continue;
                }
                variables.insert(pair<string, Decimal>(varName, makeCalculation(ss)));
            }

            ss.clear();
        }

        printVariables(variables);
        */
}

Decimal makeCalculation(stringstream &ss)
{
    Decimal temp;
    ss >> temp;
    return temp;
}

void printVariables(map<string, Decimal> &vars)
{
    map<string, Decimal>::iterator itr;
    for (itr = vars.begin(); itr != vars.end(); itr++)
        cout << itr->first << ": " << itr->second << endl;
}

Decimal decimalDivision(const Number &num1, const Number num2)
// Decimal division. Converts denominator in a number power of 10
// Divides two Integers and returns a Decimal
{
    Number temp1 = num1;
    Number temp2 = num2;

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

    return Decimal(quotient, one_temp);
}