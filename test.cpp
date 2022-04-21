#include <iostream>
#include "Number.h"

using namespace std;

int main()
{
    int a_num[4] = {4, 3, 2, 1};
    int b_num[4] = {4, 3, 2, 1};

    Number a(a_num, 4, true);
    Number b(b_num, 4, true);
}