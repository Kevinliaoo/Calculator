#include <iostream>
#include <vector>

using namespace std;

#ifndef _NUMBER_
#define _NUMBER_
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
    bool operator>(const Number &number) const;
    bool operator==(const Number &number) const;
    int operator[](int index) const;

    Number factorial();
    Number power(const Number &times);
    void changeSign();
    bool getSign() const;
    bool isEqualZero() const;
    void insertFront(int d);
    int getSize();
    virtual string toString();

    friend Number getGCD(const Number &num1, const Number &num2);
    friend Number getLCM(const Number &num1, const Number &num2);
    friend ostream &operator<<(ostream &strm, const Number &num);
    friend istream &operator>>(istream &strm, Number &num);
};
#endif

#ifndef _DECIMAL_
#define _DECIMAL_
class Decimal
{
private:
    void divideSelf(); // Copy function of decimalDivision
    void printFraction();
    bool isInteger();

protected:
    // Both numerator and denominator are stored as positive numbers
    Number numerator;
    Number denominator;
    bool isPositive; // The numerator's sign determines the Decimal's sign

public:
    Decimal();
    Decimal(const Number &num);
    Decimal(const Number &num, const Number &den);

    Decimal operator+(const Decimal &num);
    Decimal operator-(const Decimal &num);
    Decimal operator-();
    Decimal operator*(const Decimal &num);
    Decimal operator/(const Decimal &num);
    Decimal &operator=(const Decimal &num);
    bool operator==(const Decimal &num) const;

    friend ostream &operator<<(ostream &strm, const Decimal &num);
    friend istream &operator>>(istream &strm, Decimal &num);

    Decimal power(const Decimal &times);
    string toString();
    Decimal simplify(const Decimal &num);
};
#endif

#ifndef _INTEGER_
#define _INTEGER_
class Integer : public Decimal
{
private:
public:
    // The Integer's sign is NOT determined by bool isPositive,
    // otherwise, it is determined by this->numerator's sign
    Integer() : Decimal(){};
    Integer(const Number &num);

    Integer operator+(const Integer &integer);
    Integer operator-(const Integer &integer);
    Integer operator-();
    Integer operator*(const Integer &integer);
    Integer operator/(const Integer &integer);
    Integer &operator=(const Integer &integer);
    bool operator==(const Integer &integer) const;

    friend istream &operator>>(istream &strm, Integer &integer);
    friend ostream &operator<<(ostream &strm, Integer &integer);

    Integer factorial();
    string toString();
};
#endif