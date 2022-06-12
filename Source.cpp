#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "functions.h"

using namespace std;

int main()
{

    Function f;

    // 宣告變數
    f.setVariable("ABC", 30);
    f.setVariable("K", 90);
    // 重寫會把他蓋過去
    f.setVariable("K", 45);
    // X 當作變數，要宣告
    f.setVariable("X", 10);

    // 輸入
    string expression = "X+3*ABC+sin(K)*(12+K)";

    try
    {
        // 把變數帶進去（包括X）
        string input = f.replaceVariables(expression);
        cout << "Input: " << input << endl;
        string res = f.calculate(input);
        cout << "Result: " << res << endl;
    }
    catch (const char *e)
    {
        // 如果有輸入格式錯誤會噴 error
        cout << "[Error]: " << e << endl;
    }
}