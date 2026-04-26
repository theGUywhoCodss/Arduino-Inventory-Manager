#include "circuit.h"

int countDigit(int n)
{
    // Base case: if 'n' is a single digit
    if (n / 10 == 0)
        return 1;
    // Recursive case: strip one digit and count
    return 1 + countDigit(n / 10);
}