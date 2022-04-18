#include <iostream>
#include <vector>

using namespace std;

class Number
{
private:
    vector<int> digits;
    bool isPositive;
    int size;

public:
    Number(int *a, int size, bool isPositive);

    Number &operator=(const Number &number);
    Number operator*(const Number &number);

    void printNumber();
};