#include "part2.h"

// isDigitStringValid() - Check if digit string is composed of maximum-9 numbers
int isDigitStringValid(const char* digit) {
    if (strlen(digit) > MAX_NUM_DIGIT) {
        return 0;
    }
    else {
        int i;

        for (i = 0; i < strlen(digit); i++) {
            if (digit[i] < '0' || digit[i] > '9') {
                return 0;
            }
        }

        return 1;
    }
}

// getDigitsSum() - Calculate sum of each digit
int getDigitsSum(const char* digit) {
    int sum = 0;

    while (*digit != '\0') {
        sum += *digit - '0';
        digit++;
    }

    return sum;
}

// getDigitsProduct() - Calculate product of each digit
int getDigitsProduct(const char* digit) {
    int product = 1;

    while (*digit != '\0') {
        product *= *digit - '0';
        digit++;
    }

    return product;
}

// outputSumProduct() - Output binary file of sum and product as "fileSumProduct.dat".
void outputSumProduct(const int *sum, const int *product) {
    int buffer[] = {*sum, *product};
    FILE* file = fopen("fileSumProduct.dat", "wb");

    if (file == NULL) {
        printf("Can't open file with \'wb\' option.\n");
    }
    else {
        fwrite(buffer, sizeof(int), NUM_BUFFER, file);
    }

    fclose(file);
}
