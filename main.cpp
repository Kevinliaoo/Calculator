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
string processStringInput(string input);
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
    // Read the stringstream and delete all spaces
    string input = "", t;
    while (ss >> t)
        input += t;
    processStringInput(input);
    Decimal temp;
    return temp;
}

Integer makeIntCalculation(stringstream &ss)
{
    // Read the stringstream and delete all spaces
    string input = "", t;
    while (ss >> t)
        input += t;
    processStringInput(input);
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

string processStringInput(string input)
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
                cout << "Error: Invalid input (parenthesis does not match).\n";
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
    // Detect factorials
    int lastOpI = -1; // last operator index
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] - '0' >= 0 && input[i] - '0' <= 9)
        {
        }
        else
        {
            bool factCalculated = false;
            string s = "";
            s += input[i];
            if (!checkElementInVector(SPECIAL_SYMBOLS, s))
            {
                cout << "Error: Invalid input (invalid characters detected).\n";
                return "";
            }
            else if (checkElementInVector(SPECIAL_SYMBOLS, s) && s != DOT_SIGN)
            {
                if (s == FACT_SIGN)
                {
                    string subInput = input.substr(lastOpI + 1, i - lastOpI - 1);
                    Integer temp;
                    stringstream ss(subInput);
                    ss >> temp;
                    temp = temp.factorial();
                    subInput += '!';
                    input.erase(lastOpI + 1, subInput.size());
                    input.insert(lastOpI + 1, temp.toString());
                    factCalculated = true;
                    i--;
                }
                if (!factCalculated)
                    lastOpI = i;

                factCalculated = false;
            }
        }
    }

    cout << input << endl;
    cout << "[log]: Finished factorial.\n";

    // Detect Powers
    while (true)
    {
        // At this step, we assume that there are no invalid characters
        string temp1, temp2;
        stringstream ss(input);
        getline(ss, temp1, POW_SIGN[0]);

        // No ^ sign was detected
        if (temp1.size() == input.size())
            break;

        getline(ss, temp2, POW_SIGN[0]);

        int cut_start = temp1.size();

        string base_s = "", exponent_s = "";
        // Get the base
        for (int i = temp1.size() - 1; i >= 0; i--)
        {
            string s = "";
            s += temp1[i];
            if (checkElementInVector(SPECIAL_SYMBOLS, s) && s != DOT_SIGN)
                break;
            else
            {
                base_s = s + base_s;
                cut_start--;
            }
        }

        // Get the exponent
        for (int i = 0; i < temp2.size(); i++)
        {
            string s = "";
            s += temp2[i];
            if (checkElementInVector(SPECIAL_SYMBOLS, s) && s != DOT_SIGN)
            {
                if (i == 0 && s == MIN_SIGN)
                    exponent_s += s;
                else
                    break;
            }
            else
                exponent_s += s;
        }

        int cut_size = base_s.size() + exponent_s.size() + 1;

        Decimal base, exp;
        ss.clear();
        ss.str(base_s);
        ss >> base;
        ss.clear();
        ss.str(exponent_s);
        ss >> exp;
        Decimal res = base.power(exp);

        input.erase(cut_start, cut_size);
        input.insert(cut_start, res.toString());

        ss.clear();
        ss.str(input);
    }

    cout << "[log]: Finished power.\n";
    cout << input << endl;

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