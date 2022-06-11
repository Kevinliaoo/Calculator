#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "functions.h"

using namespace std;

map<string, double> variables;

int main()
{

    // cout << calculate("90/(90/10)-2*sin(100-10)+1") << endl;
    cout << calculate("5*tan(100+60--20)+1") << endl;

    setVariable(variables, "ABC", 30);
    setVariable(variables, "K", 0.9);

    string expression = "3*ABC+sin(K)*(12+K)";
    if (checkParenthesis(expression))
    {
        string input = replaceVariables(expression, variables);
        cout << input << endl;
    }
}