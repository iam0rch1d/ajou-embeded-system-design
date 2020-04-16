// * Task 1 - part1 *
// Get 9-digits number from user. Remove 0 from each digit. Print resulting number

#include "part1.h"

int main() {
    char strDigit[NUM_DIGIT + 1]; // Number character array of 9-digits number and null character('\0')

    printf("Input (9-digits number):");
    scanf("%s", strDigit);

    if (isDigitStringValid(strDigit) == 0) {
        printf("Invalid input.\n");
    }
    else {
        removeZero(strDigit);
        printf("Output:%s\n", strDigit);
    }

    return 0;
}
