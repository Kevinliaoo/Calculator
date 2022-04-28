#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include "Number.h"

using namespace std;

Decimal decimalDivision(const Number &num1, const Number num2);
void printVariables(map<string, Decimal> &vars);
Decimal makeDecCalculation(stringstream &ss);
Integer makeIntCalculation(stringstream &ss);
string processStringInput(string input, bool isDecimal);
bool checkElementInVector(vector<string> source, string target);

const string SET_STR = "Set";
const string INTEGER_STR = "Integer";
const string DECIMAL_STR = "Decimal";
vector<string> SPECIAL_SYMBOLS;
const string PLUS_SIGN = "+";
const string MIN_SIGN = "-";
const string MULT_SIGN = "*";
const string DIV_SIGN = "/";
const string FACT_SIGN = "!";
const string POW_SIGN = "^";
const string OPAR_SIGN = "(";
const string CPAR_SIGN = ")";
const string DOT_SIGN = ".";
const string COMMA_SIGN = ",";
const string POWER_KWORD = "Power";
const string FACT_KWORD = "Factorial";

int main()
{
    // Setting up special symbols (I can not use the vector constructor)
    SPECIAL_SYMBOLS.push_back(PLUS_SIGN);
    SPECIAL_SYMBOLS.push_back(MIN_SIGN);
    SPECIAL_SYMBOLS.push_back(MULT_SIGN);
    SPECIAL_SYMBOLS.push_back(DIV_SIGN);
    SPECIAL_SYMBOLS.push_back(FACT_SIGN);
    SPECIAL_SYMBOLS.push_back(POW_SIGN);
    SPECIAL_SYMBOLS.push_back(OPAR_SIGN);
    SPECIAL_SYMBOLS.push_back(CPAR_SIGN);
    SPECIAL_SYMBOLS.push_back(DOT_SIGN);
    SPECIAL_SYMBOLS.push_back(COMMA_SIGN);
    SPECIAL_SYMBOLS.push_back(POWER_KWORD);
    SPECIAL_SYMBOLS.push_back(FACT_KWORD);

    /*
    map<string, Decimal> variables;
    stringstream ss;

    Integer i1;
    Decimal d1;

    ss.clear();
    string aa = "-1234";
    ss.str(aa);
    ss >> i1;

    ss.clear();
    string bb = "123.4567900";
    ss.str(bb);
    ss >> d1;

    variables.insert(pair<string, Decimal>("i1", i1));
    variables.insert(pair<string, Decimal>("d1", d1));

    map<string, Decimal>::iterator itr;
    for (itr = variables.begin(); itr != variables.end(); itr++)
        cout << itr->first << ": " << itr->second;
        */

    map<string, Decimal> variables;

    string inputMessage;
    stringstream ss;

    while (getline(cin, inputMessage))
    {
        ss.str(inputMessage);

        if (inputMessage.substr(0, 3) == SET_STR)
        // Set a variable
        {
            string datatype, varName, eqSign, value;
            ss >> eqSign >> datatype >> varName >> eqSign;

            if (datatype == INTEGER_STR)
                variables.insert(pair<string, Decimal>(varName, makeIntCalculation(ss)));
            else if (datatype == DECIMAL_STR)
                variables.insert(pair<string, Decimal>(varName, makeDecCalculation(ss)));
            else
            {
                cout << "Error: Invalid datatype";
                continue;
            }
        }

        ss.clear();
    }

    printVariables(variables);
}
Decimal makeDecCalculation(stringstream &ss)
{
    Decimal temp;
    ss >> temp;
    return temp;
}

Integer makeIntCalculation(stringstream &ss)
{
    // Read the stringstream and delete all spaces
    string input = "", t;
    while (ss >> t)
        input += t;
    processStringInput(input, false);
    Integer temp;
    return temp;
}

void printVariables(map<string, Decimal> &vars)
{
    map<string, Decimal>::iterator itr;
    for (itr = vars.begin(); itr != vars.end(); itr++)
        cout << itr->first << ": " << itr->second;
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

string processStringInput(string input, bool isDecimal)
{
    vector<char> parenthesis_stack;
    vector<int> parenthesis_index;

    for (int i = 0; i < input.size(); i++)
    {
        char current = input[i];

        // An open parenthesis ( detected
        if (current == OPAR_SIGN[0])
        {
            parenthesis_stack.push_back(current);
            parenthesis_index.push_back(i);
        }

        if (current == CPAR_SIGN[0])
        {
            if (parenthesis_stack.size() == 0)
            // A close parenthesis detected without previously opening
            {
                cout << "Error: Invalid input.\n";
                return "";
            }
            // Take what is inside the parenthesis
            int j = parenthesis_index.back();
            string subInput = input.substr(j + 1, i - j - 1);
            cout << "The subinput is: " << subInput << endl;

            parenthesis_index.pop_back();
            parenthesis_stack.pop_back();

            // Power() or Factorial()

            // Arithmetic operations
        }
    }
    // At this step, all parenthesis are removed

    string res;
    return res;
}

bool checkElementInVector(vector<string> source, string target)
// This function checks if a string can be found in a string vector
{
    for (int i = 0; i < source.size(); i++)
        if (source[i] == target)
            return true;

    return false;
}