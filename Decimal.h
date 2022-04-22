#include "Number.h"

class Decimal
{
private:
    Number numerator;
    Number denominator;

public:
    Decimal(const Number &num, const Number &den) : numerator(num), denominator(den){};
};