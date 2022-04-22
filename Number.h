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

public:
    Number();
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
    void changeSign();
    bool getSign();

    friend Number getGCD(const Number &num1, const Number &num2);
    friend Number getLCM(const Number &num1, const Number &num2);
};

class Decimal
{
private:
    // Both numerator and denominator are stored as positive numbers
    Number numerator;
    Number denominator;
    bool isPositive; // The numerator's sign determines the Decimal's sign

public:
    Decimal(const Number &num, const Number &den);

    Decimal operator+(const Decimal &num);
    Decimal operator-(const Decimal &num);

    void printFraction();
    void printDecimal();
};