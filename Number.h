#include <iostream>
#include <vector>

using namespace std;

class Number
{
private:
    vector<int> digits; // Stores all the digits of the number
    bool isPositive;    // true if it is a positive number
    int size;           // The size of the number
    Number subtract(const Number &number);
    Number add(const Number &number) const;
    void changeSign();

public:
    Number(int *a, int size, bool isPositive);

    Number &operator=(const Number &number);
    Number operator*(const Number &number);
    Number operator-(const Number &number);
    Number operator+(const Number &number);
    bool operator>(const Number &number);

    void printNumber();
};