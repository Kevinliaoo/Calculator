#include <iostream>
#include <sstream>
#include <string>
#include "Number.h"

using namespace std;

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include "Number.h"

using namespace std;

void printInstructions();
Decimal decimalDivision(const Number &num1, const Number num2);
void printVariables(map<string, string> &vars);
Decimal makeDecCalculation(stringstream &ss);
Integer makeIntCalculation(stringstream &ss);
string getVarValue(map<string, string> &vars, string varName);
string processStringInput(string input);
bool checkElementInVector(vector<string> source, string target);
string solveOperation(string input, string op);
void setDecVariable(map<string, string> &variables, string varName, const Decimal &num);
void setIntVariable(map<string, string> &variables, string varName, const Integer &num);
bool inputHasDecimal(string input);
string makeBasicOperation(string input, string number1_s, string number2_s, char op, int i);

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

// map where all variables are stored
map<string, string> variables;

int main()
{
    Integer x;
    Decimal y;

    cin >> x; // 輸入 123456789
    cin >> y; // 輸入 3.1415926

    cout << x + y << endl;
    cout << x - y << endl;
    cout << x * y << endl;
    cout << x / y << endl;

    stringstream ssx("123 * 8 + 456");
    ssx >> x;

    stringstream ssy("-1.0 / 3 - 45 / 13.0");
    ssy >> y;

    vector<Decimal> nums;
    nums.push_back(x);
    nums.push_back(y);
    for (const auto &num : nums)
        cout << num << endl;
}

void printInstructions()
// Prints the instructions menu for the user
{
    cout << "-----------------------------------------------------------------\n";
    cout << "* Instructions: \n";
    cout << "\t1. Make operations: Insert the operation directly.\n";
    cout << "\t2. Create a variable: Set datatype varName = operation.\n";
    cout << "\t3. List all variables: Variables\n";
    cout << "\t4. Finish program: ctrl + d\n\n";
    cout << "* References:\n";
    cout << "\tdatatypes: Integer or Decimal.\n";
    cout << "\toperators: + - * / ! ^\n";
    cout << "\n* Notes:\n";
    cout << "\t1. All numbers are treated as Decimal.\n";
    cout << "\t2. Variable names can only contain letters.\n";
    cout << "\t3. Everything is case sensitive.\n";
    cout << "-----------------------------------------------------------------\n\n";
}

Decimal makeDecCalculation(stringstream &ss)
// Computes the an operation and returns the result in a Decimal
// Precondition: ss is the stringstream from where to get the calculation
// Postcondition: The result is returned as a Decimal
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
// Computes the an operation and returns the result in a Integer
// Precondition: ss is the stringstream from where to get the calculation
// Postcondition: The result is returned as a Integer
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

string getVarValue(map<string, string> &vars, string varName)
// Get the value of the variable stored in a map
// Precondition: vars is the map where all variabels are stored as name: value
// varName is the variable name to be searched
{
    map<string, string>::iterator itr;
    for (itr = vars.begin(); itr != vars.end(); itr++)
        if (itr->first == varName)
            return itr->second;

    cout << "[Error]: Variable " << varName << " does not exist.\n";
    return "0";
}

void printVariables(map<string, string> &vars)
// Prints all the variables list
// Precondition: vars is the map where all variables are stored as name: value
{
    cout << "Variables list: \n";
    map<string, string>::iterator itr;
    for (itr = vars.begin(); itr != vars.end(); itr++)
        cout << itr->first << ": " << itr->second << endl;
    cout << endl
         << endl;
}

Decimal decimalDivision(const Number &num1, const Number num2)
// Decimal division. Converts denominator in a number power of 10
// Divides two Integers and returns a Decimal
// Precondition: num1 and num2 are Numbers to be divided
// Postcondition: Decimal is the resulting number in Decimal mode
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
                cout << "[Error]: Invalid input (parenthesis does not match).\n";
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
            // Rewind to where the parenthesis was opened
            i = j;

            // cout << "[log]: Parenthesis solved.\n";
            // cout << input << endl;
        }
    }

    if (parenthesis_stack.size() != 0)
    {
        cout << "[Error]: Invalid input (parenthesis does not match).\n";
        return "";
    }

    // cout << "[log]: Starting arithmetic operations.\n";
    // cout << input << endl;

    // Replace variables names with their values
    {
        string varName;
        bool buildingName = false;
        int i;
        for (i = 0; i < input.size(); i++)
        {
            char letter = input[i];
            int c = input[i];
            if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
            {
                buildingName = true;
                varName += letter;
            }
            else
            {
                if (buildingName)
                {
                    string res = getVarValue(variables, varName);
                    input.erase(i - varName.size(), varName.size());
                    input.insert(i - varName.size(), res);
                    buildingName = false;
                    varName = "";
                }
            }
        }
        if (buildingName)
        {
            string res = getVarValue(variables, varName);
            input.erase(i - varName.size(), varName.size());
            input.insert(i - varName.size(), res);
            buildingName = false;
        }
    }

    // cout << "[log]: Variables replaced.\n";
    // cout << input << endl;

    bool hasDeicmal = inputHasDecimal(input);

    // At this step, all parenthesis are removed
    // Detect factorials
    {
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
                string del = "";
                del += Decimal::fraction_delimiter;
                if (!checkElementInVector(SPECIAL_SYMBOLS, s) && s != del)
                {
                    cout << "[Error]: Invalid input (invalid characters detected).\n";
                    cout << "Invalid character: " << s << endl;
                    return "";
                }
                else if (checkElementInVector(SPECIAL_SYMBOLS, s) && s != DOT_SIGN && s != del)
                {
                    if (s == FACT_SIGN)
                    {
                        string subInput = input.substr(lastOpI + 1, i - lastOpI - 1);
                        bool hasDecimal = inputHasDecimal(subInput);
                        stringstream ss(subInput);
                        string fact_res;
                        if (!hasDecimal)
                        {
                            Integer temp;
                            ss >> temp;
                            temp = temp.factorial();
                            fact_res = temp.toString();
                        }
                        else
                        {
                            Decimal temp;
                            ss >> temp;
                            temp = temp.factorial();
                            fact_res = temp.toString();
                        }
                        subInput += '!';
                        input.erase(lastOpI + 1, subInput.size());
                        input.insert(lastOpI + 1, fact_res);
                        factCalculated = true;
                        i--;
                    }
                    if (!factCalculated)
                        lastOpI = i;

                    factCalculated = false;
                }
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

    // Multiplication and division
    {
        string number1_s, number2_s;
        const char noOperator = '\0';
        char op = noOperator;
        int op_index = -10;
        for (int i = 0; i < input.size(); i++)
        {
            if ((input[i] == MULT_SIGN[0] || input[i] == DIV_SIGN[0]) && op == noOperator)
            {
                op_index = i;
                op = input[i];
            }
            else
            {
                if (input[i] - '0' >= 0 && input[i] - '0' <= 9 || (input[i] == Decimal::decimal_point || input[i] == Decimal::fraction_delimiter))
                {
                    if (op != noOperator)
                        number2_s += input[i];
                    else
                        number1_s += input[i];
                }
                else if (input[i] == Number::minus_sign && op_index == i - 1)
                    // Negative number detected (second operand)
                    number2_s += input[i];
                else if ((input[i] == MULT_SIGN[0] || input[i] == DIV_SIGN[0]) && op != noOperator)
                // Detected another operator, compute the previous one
                {
                    // This piece of code computes the operation
                    input = makeBasicOperation(input, number1_s, number2_s, op, i);
                    // RESET VALUES
                    int op_size = number1_s.size() + number2_s.size() + 1;
                    i -= (op_size + 1);
                    number1_s = "";
                    number2_s = "";
                    op = noOperator;
                }
                else if (input[i] == PLUS_SIGN[0] || input[i] == MIN_SIGN[0])
                // Plus or minus detected
                {
                    if (op == noOperator)
                    {
                        number1_s = "";
                        number2_s = "";
                    }
                    else
                    // Compute the last operator
                    {
                        // This piece of code computes the operation
                        input = makeBasicOperation(input, number1_s, number2_s, op, i);
                        // RESET VALUES
                        int op_size = number1_s.size() + number2_s.size() + 1;
                        i -= (op_size + 1);
                        number1_s = "";
                        number2_s = "";
                        op = noOperator;
                    }
                }
            }
        }
        if (op != noOperator)
        {
            if (op == MULT_SIGN[0])
            {
                stringstream ssr(input);
                input = makeBasicOperation(input, number1_s, number2_s, op, input.size() - 1);
            }
            else
            {
                stringstream ssr(input);
                input = makeBasicOperation(input, number1_s, number2_s, op, input.size() - 1);
            }
        }
    }

    // cout << "[log]: Finished multiplication and division.\n";
    // cout << input << endl;

    // Addition and subtraction
    if (hasDeicmal)
    {
        Decimal zero;
        string num_s;
        char op = PLUS_SIGN[0];
        stringstream ss;
        for (int i = 0; i < input.size(); i++)
        {
            char current = input[i];
            bool isDigit = current - '0' >= 0 && current - '0' <= 9;
            bool temp = current == Decimal::fraction_delimiter;

            if (isDigit || current == DOT_SIGN[0] || current == Decimal::fraction_delimiter)
                num_s += current;
            else
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

                char next = input[i + 1];
                if (next == PLUS_SIGN[0] && i + 1 < input.size())
                    i++;
                else if (next == MIN_SIGN[0] && i + 1 < input.size())
                {
                    op = op == PLUS_SIGN[0] ? MIN_SIGN[0] : PLUS_SIGN[0];
                    i++;
                }
            }
        }
        // Final operation
        ss.clear();
        ss.str(num_s);
        Decimal temp;
        ss >> temp;
        if (op == PLUS_SIGN[0])
            zero = zero + temp;
        else if (op == MIN_SIGN[0])
            zero = zero - temp;

        // cout << "[log]: Finished computation.\n";
        // cout << "[log]: Final result: " << zero;

        return zero.toFractString();
    }
    else
    {
        Integer zero;
        string num_s;
        char op = PLUS_SIGN[0];
        stringstream ss;
        for (int i = 0; i < input.size(); i++)
        {
            char current = input[i];
            bool isDigit = current - '0' >= 0 && current - '0' <= 9;
            bool temp = current == Decimal::fraction_delimiter;

            if (isDigit || current == DOT_SIGN[0] || current == Decimal::fraction_delimiter)
                num_s += current;
            else
            {
                ss.clear();
                ss.str(num_s);
                Integer temp;
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

                char next = input[i + 1];
                if (next == PLUS_SIGN[0] && i + 1 < input.size())
                    i++;
                else if (next == MIN_SIGN[0] && i + 1 < input.size())
                {
                    op = op == PLUS_SIGN[0] ? MIN_SIGN[0] : PLUS_SIGN[0];
                    i++;
                }
            }
        }
        // Final operation
        ss.clear();
        ss.str(num_s);
        Integer temp;
        ss >> temp;
        if (op == PLUS_SIGN[0])
            zero = zero + temp;
        else if (op == MIN_SIGN[0])
            zero = zero - temp;

        // cout << "[log]: Finished computation.\n";
        // cout << "[log]: Final result: " << zero;

        return zero.toString();
    }
}

string makeBasicOperation(string input, string number1_s, string number2_s, char op, int i)
// Solves multiplications or division
// Precondition: input is the calculation
//               number1_s and number2_s are the operands
//               op is the operation to be performed
//               i is the index where it is standed
// Postcondition: Returns the same input string with the operation computed
{
    stringstream ss1(number1_s);
    stringstream ss2(number2_s);

    bool hasDecimal = inputHasDecimal(number1_s) || inputHasDecimal(number2_s);
    string res_s;
    if (hasDecimal)
    {
        Decimal number1, number2, res;
        ss1 >> number1;
        ss2 >> number2;
        if (op == MULT_SIGN[0])
            res = number1 * number2;
        else if (op == DIV_SIGN[0])
            res = number1 / number2;
        else if (op == PLUS_SIGN[0])
            res = number1 + number2;
        else if (op == MIN_SIGN[0])
            res = number1 - number2;
        res_s = res.toFractString();
    }
    else
    {
        Integer number1, number2, res;
        ss1 >> number1;
        ss2 >> number2;
        if (op == MULT_SIGN[0])
            res = number1 * number2;
        else if (op == DIV_SIGN[0])
            res = number1 / number2;
        else if (op == PLUS_SIGN[0])
            res = number1 + number2;
        else if (op == MIN_SIGN[0])
            res = number1 - number2;
        res_s = res.toString();
    }

    int op_size = number1_s.size() + number2_s.size() + 1;
    if (op_size == input.size())
        input = res_s;
    else
    {
        input.erase(i - op_size, op_size);
        input.insert(i - op_size, res_s);
    }

    return input;
}

string solveOperation(string input, string op)
// Resolves a calculation within a parenthesis (power, division and multiplication)
// Precondition: input is the string containing the operation
// op is the operation to be executed
// Postcondition: The result of the computation in a string (fraction mode)
{
    bool hasDeicmal = inputHasDecimal(input);

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
        if (hasDeicmal)
        {
            Decimal fact1, fact2;
            ss.clear();
            ss.str(fact1_s);
            ss >> fact1;
            ss.clear();
            ss.str(fact2_s);
            ss >> fact2;
            Decimal res;

            // cout << "[log] solveOperation() fact1: " << fact1;
            // cout << "[log] solveOperation() fact2: " << fact2;

            // Compute the operations
            if (op == MULT_SIGN)
                res = fact1 * fact2;
            else if (op == POW_SIGN)
                res = fact1.power(fact2);
            else if (op == DIV_SIGN)
                res = fact1 / fact2;

            // cout << "[log] solveOperation() res: " << res;
            // cout << "[log] solveOperation() res#: " << res.toFractString() << endl;

            // Replace the operation with the result
            input.erase(cut_start, cut_size);
            input.insert(cut_start, res.toFractString());
        }
        else
        {
            Integer fact1, fact2;
            ss.clear();
            ss.str(fact1_s);
            ss >> fact1;
            ss.clear();
            ss.str(fact2_s);
            ss >> fact2;
            Integer res;

            // cout << "[log] solveOperation() fact1: " << fact1;
            // cout << "[log] solveOperation() fact2: " << fact2;

            // Compute the operations
            if (op == MULT_SIGN)
                res = fact1 * fact2;
            else if (op == POW_SIGN)
                res = fact1.power(fact2);
            else if (op == DIV_SIGN)
                res = fact1 / fact2;

            // cout << "[log] solveOperation() res: " << res;
            // cout << "[log] solveOperation() res#: " << res.toFractString() << endl;

            // Replace the operation with the result
            input.erase(cut_start, cut_size);
            input.insert(cut_start, res.toString());
        }

        // Go over again
        ss.clear();
        ss.str(input);
    }

    return input;
}

bool checkElementInVector(vector<string> source, string target)
// Checks if a string can be found in a string vector
{
    for (int i = 0; i < source.size(); i++)
        if (source[i] == target)
            return true;

    return false;
}

void setDecVariable(map<string, string> &variables, string varName, const Decimal &num)
// Inserts a new Decimal variable to variables list (map) or overrides if already exists
// Precondition: variables is the map containing all variables
// varName is the name of the variable, num is the Decimal to be stored
{
    map<string, string>::iterator itr;
    for (itr = variables.begin(); itr != variables.end(); itr++)
    {
        if (itr->first == varName)
        {
            variables[varName] = num.toFractString();
            return;
        }
    }

    variables.insert(pair<string, string>(varName, num.toFractString()));
}
void setIntVariable(map<string, string> &variables, string varName, const Integer &num)
// Inserts a new Integer variable to variables list (map) or overrides if already exists
// Precondition: variables is the map containing all variables
// varName is the name of the variable, num is the Integer to be stored
{
    map<string, string>::iterator itr;
    for (itr = variables.begin(); itr != variables.end(); itr++)
    {
        if (itr->first == varName)
        {
            variables[varName] = num.toString();
            return;
        }
    }

    variables.insert(pair<string, string>(varName, num.toString()));
}

bool inputHasDecimal(string input)
// This function returns true if the given input (operation) contains decimal numbers or fractions
// Precondition: input is the string containing the operation to compute
{
    for (int i = 0; i < input.size(); i++)
        if (input[i] == Decimal::decimal_point || input[i] == Decimal::fraction_delimiter)
            return true;
    return false;
}