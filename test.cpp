#include <iostream>
#include "Number.h"

using namespace std;

int main()
{
    int a_num[8] = {3, 2, 1, 5, 4, 3, 2, 1};
    int b_num[5] = {5, 4, 3, 2, 1};

    Number a(a_num, 8, true);
    Number b(b_num, 5, true);

    Number t = a * b;
    t.printNumber();
}