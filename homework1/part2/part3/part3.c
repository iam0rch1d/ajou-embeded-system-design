// * Task 1 - part3 *
// Get two numbers in [1-50000] from user. Print GCD(greatest common divisor) and LCM(least common multiple) of two
// numbers

#include "part3.h"

int main() {
    int arrNum[NUM_NUMBER];

    printf("Input first number ([%d-%d]):", MIN_NUMBER, MAX_NUMBER);
    scanf("%d", arrNum);
    printf("Input second number ([%d-%d]):", MIN_NUMBER, MAX_NUMBER);
    scanf("%d", arrNum + 1);

    if (isNumberValid(arrNum) == 0) {
        printf("Invalid input.\n");
    }
    else {
        int gcd = euclid(arrNum[0], arrNum[1]); // Perform Euclid algorithm to get GCD
        int lcm = arrNum[0] * arrNum[1] / gcd; // LCM is quotient of product of two number divided by GCD

        printf("GCD(greatest common divisor):%d\n", gcd);
        printf("LCM(least common multiple):%d\n", lcm);
    }

    return 0;
}
