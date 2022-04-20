#include <iostream>
#include "Number.h"

using namespace std;

int main()
{
    int a_num[1] = {5};
    int b_num[1] = {3};

    Number a(a_num, 1, true);
    Number b(b_num, 1, false);

    Number t = b + a;

    t.printNumber();
}