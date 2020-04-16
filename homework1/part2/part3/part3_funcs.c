#include "part3.h"

// isNumberValid() - Check if numbers are in range
int isNumberValid(const int* arrNum) {
    int i;

    for (i = 0; i < NUM_NUMBER; i++) {
        if (arrNum[i] < MIN_NUMBER || arrNum[i] > MAX_NUMBER) {
            return 0;
        }
    }

    return 1;
}

// euclid() - Perform Euclid algorithm
int euclid(int a, int b) {
    return (b == 0) ? a : euclid(b, a % b); // Recursion steps. Divide smaller number into remainder of larger number
                                            // divided by smaller number until they are divisible
}
