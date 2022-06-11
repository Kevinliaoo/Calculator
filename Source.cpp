#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "functions.h"

using namespace std;

map<string, double> variables;

int main()
{

    // 宣告變數
    setVariable(variables, "ABC", 30);
    setVariable(variables, "K", 90);
    // 重寫會把他蓋過去
    setVariable(variables, "K", 45);
    // X 當作變數，要宣告
    setVariable(variables, "X", 10);

    // 輸入
    string expression = "X+3*ABC+sin(K)*(12+K)";

    try
    {
        // 把變數帶進去（包括X）
        string input = replaceVariables(expression, variables);
        cout << "Input: " << input << endl;
        string res = calculate(input);
        cout << "Result: " << res << endl;
    }
    catch (const char *e)
    {
        // 如果有輸入格式錯誤會噴 error
        cout << "[Error]: " << e << endl;
    }
}