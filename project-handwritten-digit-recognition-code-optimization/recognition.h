#define IMG_SIZE 784
#define IMG_COUNT 50000
#define DIGIT_COUNT 10
#define NUM_UNROLLING_ELEMENT 8

void recognition(float *images, float *network, int depth, int size, int *labels, float *confidences);
