#include <iostream>
#include "Number.h"

using namespace std;

int main()
{
    int a_num[6] = {9, 9, 9, 9, 9, 9};
    int b_num[6] = {9, 9, 9, 9, 9, 9};

    Number a(a_num, 6, true);
    Number b(b_num, 6, true);

    a.printNumber();
    b.printNumber();

    Number c = a * b;
    c.printNumber();
}