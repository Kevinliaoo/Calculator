#include <iostream>
#include "Number.h"

using namespace std;

int main()
{
    int a_num[2] = {5, 1};
    int b_num[2] = {0, 2};

    Number a(a_num, 2, true);
    Number b(b_num, 2, true);

    a.printNumber();
    b.printNumber();

    Number c = getLCM(a, b);
    c.printNumber();
}