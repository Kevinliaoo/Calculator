#include <iostream>
#include <vector>
#include "Number.h"

using namespace std;

int main()
{
    int a_num[1] = {1};
    int b_num[1] = {5};
    int c_num[1] = {3};
    int z_num[1] = {0};

    Number a(a_num, 1, true);
    Number b(b_num, 1, false);
    Number c(c_num, 1, true);
    Number d(a_num, 1, false);

    Decimal deca(a, b);
    Decimal decb(a, c);

    Number zero;
    Number t(z_num, 1, false);

    t = t / t;

    t.printNumber();
}
