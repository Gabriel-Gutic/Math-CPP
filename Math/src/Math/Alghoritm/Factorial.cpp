#include "Factorial.h"

UInt Factorial::Run(UInt n)
{
    UInt result = 1;
    for (UInt i = 1; i <= n; i++)
        result *= i;
    return result;
}
