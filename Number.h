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

    friend Number getGCD(const Number &num1, const Number &num2);
    friend Number getLCM(const Number &num1, const Number &num2);
    friend ostream &operator<<(ostream &strm, const Number &num);
    friend istream &operator>>(istream &strm, Number &num);
};

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
    Decimal(const Number &num, const Number &den);

    Decimal operator+(const Decimal &num);
    Decimal operator-(const Decimal &num);
    Decimal &operator=(const Decimal &num);
    bool operator==(const Decimal &num) const;

    friend ostream &operator<<(ostream &strm, const Decimal &num);
    friend istream &operator>>(istream &strm, Decimal &num);

    Decimal power(const Decimal &times);
};

class Integer : public Decimal
{
private:
public:
    Integer();
    Integer(const Number &num);

    Integer operator+(const Integer &integer);
    Integer operator-(const Integer &integer);
    Integer operator*(const Integer &integer);
    Integer operator/(const Integer &integer);
    Integer &operator=(const Integer &integer);
    bool operator==(const Integer &integer) const;

    friend istream &operator>>(istream &strm, Integer &integer);
    friend ostream &operator<<(ostream &strm, Integer &integer);
};