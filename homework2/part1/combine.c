#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define COMBINE_VERSION 1
#define VECTOR_DATA_LENGTH 100000
#define NUM_COMBINE_LOOP 100000
#define CPU_FREQUENCY 442000000

enum boolean {
    false = 0,
    true
};

typedef struct Vector {
    int length;
    int* data;
} Vector;


Vector* InitializeVector(int length);
int GetVectorLength(Vector* vector);
int* GetVectorData(Vector* vector);
int GetVectorDataElement(Vector* vector, int index, int* destination);
void Combine1(Vector* vector, long long int* destination);
void Combine2(Vector* vector, long long int* destination);
void Combine3(Vector* vector, long long int* destination);
void Combine4(Vector* vector, long long int* destination);


Vector* InitializeVector(int length) {
    Vector* result = malloc(sizeof(Vector));

    if (!result) {
        return NULL;
    }

    result->length = length;

    if (length > 0) {
        int* data = calloc(length, sizeof(int));

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

int* GetVectorData(Vector* vector) {
    return vector->data;
}

int GetVectorDataElement(Vector* vector, int index, int* destination) {
    if (index < 0 || index >= vector->length) {
        return false;
    }

    *destination = vector->data[index];

    return true;
}

void Combine1(Vector* vector, long long int* destination) {
    int i;

    *destination = 0;

    for (i = 0; i < GetVectorLength(vector); i++) {
        int value;

        GetVectorDataElement(vector, i, (int*)&value);

        *destination += value;
    }
}

void Combine2(Vector* vector, long long int* destination) {
    int i;
    int length = GetVectorLength(vector);

    *destination = 0;

    for (i = 0; i < length; i++) {
        int value;

        GetVectorDataElement(vector, i, (int*)&value);

        *destination += value;
    }
}

void Combine3(Vector* vector, long long int* destination) {
    int i;
    int length = GetVectorLength(vector);
    int* data = GetVectorData(vector);

    *destination = 0;

    for (i = 0; i < length; i++) {
        *destination += data[i];
    }
}

void Combine4(Vector* vector, long long int* destination) {
    int i;
    int length = GetVectorLength(vector);
    int* data = GetVectorData(vector);
    long long int sum = 0;

    for (i = 0; i < length; i++) {
        sum += data[i];
    }

    *destination = sum;
}


int main() {
    FILE* file = fopen("vector_data.txt", "r");
    struct timeval timeStart;
    struct timeval timeFinish;
    double timeSeconds;
    Vector* vector = InitializeVector(VECTOR_DATA_LENGTH);
    long long int sum;
    int i;

    if (file == NULL) {
        printf("Can't open file with \'r\' option.\n");
    } else {
        for (i = 0; i < VECTOR_DATA_LENGTH; i++) {
            fscanf(file, "%d", vector->data + i);
        }
    }

    gettimeofday(&timeStart, NULL);

    for (i = 0; i < NUM_COMBINE_LOOP; i++) {
#if COMBINE_VERSION == 1
        Combine1(vector, &sum);
#elif COMBINE_VERSION == 2
        Combine2(vector, &sum);
#elif COMBINE_VERSION == 3
        Combine3(vector, &sum);
#elif COMBINE_VERSION == 4
        Combine4(vector, &sum);
#endif
    }

    gettimeofday(&timeFinish, NULL);

    timeSeconds = (timeFinish.tv_sec - timeStart.tv_sec) + 1e-6 * (timeFinish.tv_usec - timeStart.tv_usec);

    printf("Sum of vector: %lld,%03lld,%03lld,%03lld\n",
	    sum / 1000000000 % 1000,
	    sum / 1000000 % 1000,
	    sum / 1000 % 1000,
	    sum % 1000);
    printf("Elapsed time: %f [sec]\n", timeSeconds);
    printf("CPE: %f\n", timeSeconds * CPU_FREQUENCY / VECTOR_DATA_LENGTH / NUM_COMBINE_LOOP);

    free(vector);
    fclose(file);

    return 0;
}
