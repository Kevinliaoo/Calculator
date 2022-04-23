#include <iostream>
#include <vector>

using namespace std;

class Integer
{
private:
    vector<int> digits; // Stores all the digits of the number
    bool isPositive;    // true if it is a positive number
    int size;           // The size of the number

    Integer subtract(const Integer &number);  // Helper function for operator-
    Integer add(const Integer &number) const; // Helper function for operator+

public:
    Integer();
    Integer(int *a, int size, bool isPositive);

    Integer &operator=(const Integer &number);
    Integer operator*(const Integer &number);
    Integer operator-(const Integer &number);
    Integer operator+(const Integer &number);
    Integer operator%(const Integer &number);
    Integer operator/(const Integer &number);
    bool operator>(const Integer &number) const;
    bool operator==(const Integer &number) const;
    int operator[](int index) const;

    Integer factorial();
    Integer power(const Integer &times);
    void changeSign();
    bool getSign();
    bool isEqualZero();
    void insertFront(int d);
    int getSize();

    friend Integer getGCD(const Integer &num1, const Integer &num2);
    friend Integer getLCM(const Integer &num1, const Integer &num2);
    friend ostream &operator<<(ostream &strm, const Integer &num);
    friend istream &operator>>(istream &strm, Integer &num);
};

class Decimal
{
private:
    // Both numerator and denominator are stored as positive numbers
    Integer numerator;
    Integer denominator;
    bool isPositive; // The numerator's sign determines the Decimal's sign

public:
    Decimal(const Integer &num, const Integer &den);

    Decimal operator+(const Decimal &num);
    Decimal operator-(const Decimal &num);

    void printFraction();
    bool isInteger();

    friend ostream &operator<<(ostream &strm, const Decimal &num);
    friend istream &operator>>(istream &strm, Decimal &num);
};