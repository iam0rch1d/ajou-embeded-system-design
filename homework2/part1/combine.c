#include <stdio.h>
#include <stdlib.h>

#define COMBINE_VERSION 1

enum boolean {
    false = 0,
    true
};

typedef struct Vector {
    int length;
    long int* data;
} Vector;


Vector* InitializeVector(int length);
int GetVectorLength(Vector* vector);
long int* GetVectorData(Vector* vector);
int GetVectorDataElement(Vector* vector, int index, long int* destination);
void Combine1(Vector* vector, long int* destination);
void Combine2(Vector* vector, long int* destination);
void Combine3(Vector* vector, long int* destination);
void Combine4(Vector* vector, long int* destination);


Vector* InitializeVector(int length) {
    Vector* result = malloc(sizeof(Vector));

    if (!result) {
        return NULL;
    }

    result->length = length;

    if (length > 0) {
        long int* data = calloc(length, sizeof(long int));

        if (!data) {
            free(result);

            return NULL;
        }

        result->data = data;
    } else {
        free(result);

        return NULL;
    }

    return result;
}

int GetVectorLength(Vector* vector) {
    return vector->length;
}

long int* GetVectorData(Vector* vector) {
    return vector->data;
}

int GetVectorDataElement(Vector* vector, int index, long int* destination) {
    if (index < 0 || index >= vector->length) {
        return false;
    }

    *destination = vector->data[index];

    return true;
}

void Combine1(Vector* vector, long int* destination) {
    int i;

    *destination = 0;

    for (i = 0; i < GetVectorLength(vector); i++) {
        int value;

        GetVectorDataElement(vector, i, (long*) &value);

        *destination += value;
    }
}

void Combine2(Vector* vector, long int* destination) {
    int i;
    int length = GetVectorLength(vector);

    *destination = 0;

    for (i = 0; i < length; i++) {
        int value;

        GetVectorDataElement(vector, i, (long*) &value);

        *destination += value;
    }
}

void Combine3(Vector* vector, long int* destination) {
    int i;
    int length = GetVectorLength(vector);
    long int* data = GetVectorData(vector);

    *destination = 0;

    for (i = 0; i < length; i++) {
        *destination += data[i];
    }
}

void Combine4(Vector* vector, long int* destination) {
    int i;
    int length = GetVectorLength(vector);
    long int* data = GetVectorData(vector);
    long int sum = 0;

    for (i = 0; i < length; i++) {
        sum += data[i];
    }

    *destination = sum;
}


int main() {
    Vector* vector = InitializeVector(5);
    long int sum;

    vector->data[0] = 1;
    vector->data[1] = 2;
    vector->data[2] = 4;
    vector->data[3] = 8;
    vector->data[4] = 16;

#if COMBINE_VERSION == 1
    Combine1(vector, &sum);
#elif COMBINE_VERSION == 2
    Combine2(vector, &sum);
#elif COMBINE_VERSION == 3
    Combine3(vector, &sum);
#elif COMBINE_VERSION == 4
    Combine4(vector, &sum);
#endif

    printf("Sum of vector: %ld\n", sum);

    return 0;
}
