// * Task 2 *
// Read binary file and get sum and product as result of "part2/part2.c". Calculate and print area of rhombus of which
// two diagonal length is sum and product respectively.

#include "homework1.h"

int main() {
    int arrSumProduct[NUM_BUFFER];
    double areaRhombus;

    inputSumProduct(arrSumProduct);

    areaRhombus = (double)(arrSumProduct[INDEX_SUM] * arrSumProduct[INDEX_PRODUCT]) / 2.0f;

    printf("Area of rhombus:%.1f\n", areaRhombus);

    return 0;
}
