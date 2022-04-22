#include <iostream>
#include <vector>

using namespace std;

class Number
{
private:
    vector<int> digits; // Stores all the digits of the number
    bool isPositive;    // true if it is a positive number
    int size;           // The size of the number

    Number subtract(const Number &number);  // Helper function for operator-
    Number add(const Number &number) const; // Helper function for operator+
    void changeSign();

public:
    Number(int *a, int size, bool isPositive);

    Number &operator=(const Number &number);
    Number operator*(const Number &number);
    Number operator-(const Number &number);
    Number operator+(const Number &number);
    Number operator%(const Number &number);
    Number operator/(const Number &number);
    bool operator>(const Number &number);
    bool operator==(const Number &number) const;
    int operator[](int index) const;

    Number factorial();
    void printNumber();

    friend Number getGCD(const Number &num1, const Number &num2);
    friend Number getLCM(const Number &num1, const Number &num2);
};