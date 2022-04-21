#include <iostream>
#include "Number.h"

using namespace std;

int main()
{
    int a_num[1] = {5};
    int b_num[1] = {5};

    Number a(a_num, 1, true);
    Number b(b_num, 1, true);

    Number t = a.factorial();

    t.printNumber();
}