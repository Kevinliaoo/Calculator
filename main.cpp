#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include "Number.h"

using namespace std;

void printInstructions();
Decimal decimalDivision(const Number &num1, const Number num2);
void printVariables(map<string, Decimal> &vars);
Decimal makeDecCalculation(stringstream &ss);
Integer makeIntCalculation(stringstream &ss);
string processStringInput(string input);
bool checkElementInVector(vector<string> source, string target);
string solveOperation(string input, string op);

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
const string VARIABLES = "Variables";

int main()
{
    printInstructions();

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

    map<string, Decimal> variables;

    string inputMessage;
    stringstream ss;

    cout << "> ";

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
        else if (inputMessage.substr(0, VARIABLES.size()) == VARIABLES)
            printVariables(variables);
        else
        {
            cout << ss.str() << " = ";
            Decimal res = makeDecCalculation(ss);
            cout << "  " << res << endl;
        }

        ss.clear();
        cout << "> ";
    }
}

void printInstructions()
{
    cout << "-----------------------------------------------------------------\n";
    cout << "Instructions: \n";
    cout << "\t1. Make operations: Insert the operation directly.\n";
    cout << "\t2. Create a variable: Set + datatype + operation.\n";
    cout << "\t3. List all variables: Variables\n";
    cout << "\t4. Finish program: ctrl + d\n\n";
    cout << "Reference\n";
    cout << "datatypes: Integer or Decimal.\n";
    cout << "           variable names can only be one character.\n";
    cout << "operators: + - * / ! ^\n";
    cout << "-----------------------------------------------------------------\n\n";
}

Decimal makeDecCalculation(stringstream &ss)
{
    // Read the stringstream and delete all spaces
    string input = "", t;
    while (ss >> t)
        input += t;
    string result = processStringInput(input);
    Decimal temp;
    stringstream stemp(result);
    stemp >> temp;
    // cout << "[log]: Variable value is: " << temp;
    cout << endl;
    return temp;
}

Integer makeIntCalculation(stringstream &ss)
{
    // Read the stringstream and delete all spaces
    string input = "", t;
    while (ss >> t)
        input += t;
    string result = processStringInput(input);
    Integer temp;
    stringstream stemp(result);
    stemp >> temp;
    // cout << "[log]: Variable value is: " << temp;
    cout << endl;
    return temp;
}

void printVariables(map<string, Decimal> &vars)
{
    cout << "Variables list: \n";
    map<string, Decimal>::iterator itr;
    for (itr = vars.begin(); itr != vars.end(); itr++)
        cout << itr->first << ": " << itr->second;
    cout << endl;
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
            string subInputRes = processStringInput(subInput);

            input.erase(j, i - j + 1);
            input.insert(j, subInputRes);

            parenthesis_index.pop_back();
            parenthesis_stack.pop_back();
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

    // cout << "[log]: Finished factorial.\n";
    // cout << input << endl;

    // At this step, we assume that there are no invalid characters

    // Detect Powers
    input = solveOperation(input, POW_SIGN);

    // cout << "[log]: Finished power.\n";
    // cout << input << endl;

    // Detect Multiplication
    input = solveOperation(input, MULT_SIGN);

    // cout << "[log]: Finished multiplication.\n";
    // cout << input << endl;

    // Detect Division
    input = solveOperation(input, DIV_SIGN);

    // cout << "[log]: Finished division.\n";
    // cout << input << endl;

    // Addition and subtraction
    Decimal zero;
    string num_s;
    char op = PLUS_SIGN[0];
    stringstream ss;
    for (int i = 0; i < input.size(); i++)
    {
        char current = input[i];

        if ((current - '0' < 0 || current - '0' > 9) && current != DOT_SIGN[0])
        {
            ss.clear();
            ss.str(num_s);
            Decimal temp;
            ss >> temp;
            num_s = "";
            if (op == PLUS_SIGN[0])
                zero = zero + temp;
            else if (op == MIN_SIGN[0])
                zero = zero - temp;

            if (current == PLUS_SIGN[0])
                op = PLUS_SIGN[0];
            else if (current == MIN_SIGN[0])
                op = MIN_SIGN[0];
        }
        else
            num_s += current;
    }
    // Final operation
    ss.clear();
    ss.str(num_s);
    Decimal temp;
    ss >> temp;
    num_s = "";
    if (op == PLUS_SIGN[0])
        zero = zero + temp;
    else if (op == MIN_SIGN[0])
        zero = zero - temp;

    // cout << "[log]: Finished computation.\n";
    // cout << "[log]: Final result: " << zero;

    return zero.toString();
}

string solveOperation(string input, string op)
// Resolves power, multiplication and division
// Precondition: input is the string containing the operation
// op is the operation to be executed
{
    while (true)
    {
        // Separate the operands
        string temp1, temp2;
        stringstream ss(input);
        getline(ss, temp1, op[0]);

        // No operation sign was detected
        if (temp1.size() == input.size())
            break;

        getline(ss, temp2, op[0]);

        int cut_start = temp1.size();

        string fact1_s = "", fact2_s = "";
        // Get the numbers to be operated
        for (int i = temp1.size() - 1; i >= 0; i--)
        {
            string s = "";
            s += temp1[i];
            if (checkElementInVector(SPECIAL_SYMBOLS, s) && s != DOT_SIGN)
                break;
            else
            {
                fact1_s = s + fact1_s;
                cut_start--;
            }
        }

        // Get the second factor
        for (int i = 0; i < temp2.size(); i++)
        {
            string s = "";
            s += temp2[i];
            if (checkElementInVector(SPECIAL_SYMBOLS, s) && s != DOT_SIGN)
            {
                if (i == 0 && s == MIN_SIGN)
                    fact2_s += s;
                else
                    break;
            }
            else
                fact2_s += s;
        }

        int cut_size = fact1_s.size() + fact2_s.size() + 1;

        // Build the numbers
        Decimal fact1, fact2;
        ss.clear();
        ss.str(fact1_s);
        ss >> fact1;
        ss.clear();
        ss.str(fact2_s);
        ss >> fact2;
        Decimal res;

        // Compute the operations
        if (op == MULT_SIGN)
            res = fact1 * fact2;
        else if (op == POW_SIGN)
            res = fact1.power(fact2);
        else if (op == DIV_SIGN)
            res = fact1 / fact2;

        // Replace the operation with the result
        input.erase(cut_start, cut_size);
        input.insert(cut_start, res.toString());

        // Go over again
        ss.clear();
        ss.str(input);
    }

    return input;
}

bool checkElementInVector(vector<string> source, string target)
// This function checks if a string can be found in a string vector
{
    for (int i = 0; i < source.size(); i++)
        if (source[i] == target)
            return true;

    return false;
}