#include <iostream>
#include "Number.h"

using namespace std;

int main()
{
    int a_num[1] = {1};
    int b_num[1] = {5};
    int c_num[1] = {3};

    Number a(a_num, 1, true);
    Number b(b_num, 1, true);
    Number c(c_num, 1, true);

    Decimal deca(a, b);
    Decimal decb(a, c);

    Decimal t = deca - decb;
    t.printFraction();
}