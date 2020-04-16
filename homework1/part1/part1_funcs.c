#include "part1.h"

// isDigitStringValid() - Check if digit string is composed of 9 numbers
int isDigitStringValid(const char* digit) {
    if (strlen(digit) != NUM_DIGIT) {
        return 0;
    }
    else {
        int i;

        for (i = 0; i < NUM_DIGIT; i++) {
            if (digit[i] < '0' || digit[i] > '9') {
                return 0;
            }
        }

        return 1;
    }
}

// removeZero() - Remove all '0' from digit string
void removeZero(char* digit) {
    while (*digit != '\0') {
        if ((int) *digit == '0') {    // If digit is '0', overwrite remaining digit string to pointer of current digit
            strcpy(digit, digit + 1); // and pointer moves to next digit spontaneously
        }
        else { // If digit is not '0', just move pointer to next digit
            digit++;
        }
    }
}
