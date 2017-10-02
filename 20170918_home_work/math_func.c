/* Home Work */

# include <stdlib.h>

# include "math_func.h"

unsigned long fact(unsigned long n) {
    unsigned long fact = 1;

    for (unsigned long i = 1; i <= n; i++) {
        fact *= i;
    }

    return fact;
}

unsigned long fibo(unsigned long n) {
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return fibo(n - 1) + fibo(n - 2);
}

unsigned long int_sqrt(unsigned long n) {
  // FIX ME
}

unsigned long digit_number(unsigned long n) {
  // FIX ME
}

unsigned long binary_digit_number(unsigned long n) {
  // FIX ME
}

unsigned long power_of_2(unsigned long n) {
    unsigned long pow2 = 1;

    for (int i = 0; i < n; i++) {
        pow2 *= 2;
    }

    return pow2;
}

unsigned long divisor_sum(unsigned long n) {
  // FIX ME
}
