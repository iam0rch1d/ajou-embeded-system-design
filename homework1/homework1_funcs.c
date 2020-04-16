#include "homework1.h"

// inputSumProduct() - Read binary file and get sum and product from binary file "fileSumProduct.dat". Store in array.
void inputSumProduct(int* arrSumProduct) {
    FILE* file = fopen("fileSumProduct.dat", "rb");

    if (file == NULL) {
        printf("Can't open file with \'rb\' option.\n");
    }
    else {
        fread(arrSumProduct, sizeof(int), NUM_BUFFER, file);
    }

    fclose(file);
}
