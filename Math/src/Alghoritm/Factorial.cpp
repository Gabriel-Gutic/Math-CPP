#include "Factorial.h"

UInt Factorial::Run(UInt n)
{
    if (n == 0)
        return 1;
    return n * Run(n - 1);
}
