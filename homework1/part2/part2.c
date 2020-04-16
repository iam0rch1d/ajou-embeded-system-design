// * Task 1 - part2 *
// Get maximum-9-digits number from user. Print sum and product of each digit. Output binary file of sum and product.

#include "part2.h"

int main() {
    char strDigit[MAX_NUM_DIGIT + 1]; // Number character array of 9-digits number and null character('\0')

    printf("Input (maximum-9-digits number):");
    scanf("%s", strDigit);

    if (isDigitStringValid(strDigit) == 0) {
        printf("Invalid input.\n");
    }
    else {
        int sum = getDigitsSum(strDigit);
        int product = getDigitsProduct(strDigit);

        printf("Sum of each digit:%d\n", sum);
        printf("Product of each digit:%d\n", product);
        outputSumProduct(&sum, &product);
    }

    return 0;
}
