#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "recognition.h"

int timespec_subtract(struct timespec *, struct timespec *, struct timespec *);

int main(int argc, char **argv) {
    FILE *io_file;

    // Check arguments of file input/output
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <network file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Load data from '.network' file
    io_file = fopen(argv[1], "r");

    if (!io_file) {
        fprintf(stderr, "Invalid network file %s!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    int depth;
    int size;

    fread(&depth, sizeof(int), 1, io_file); // Load data of depth
    fread(&size, sizeof(int), 1, io_file); // Load data size
    printf("size=%d, depth=%d\n", size, depth);

    int total_network_size = (IMG_SIZE * size + size)
            + (depth - 1) * (size * size + size)
            + size * DIGIT_COUNT
            + DIGIT_COUNT;
    float *network = (float *) malloc(sizeof(float) * (total_network_size));

    fread(network, sizeof(float), total_network_size, io_file);
    fclose(io_file);

    // Load data from 'MNIST_image.bin'
    float *images = (float *) malloc(sizeof(float) * IMG_COUNT * IMG_SIZE);
    int *labels_actual = (int *) malloc(sizeof(int) * IMG_COUNT);

    io_file = fopen("MNIST_image.bin", "r");

    fread(images, sizeof(float), IMG_COUNT * IMG_SIZE, io_file); // Load data of images
    fclose(io_file);

    // Load data from 'MNIST_label.bin'
    io_file = fopen("MNIST_label.bin", "r");

    fread(labels_actual, sizeof(int), IMG_COUNT, io_file); // Load data of actual labels
    fclose(io_file);

    // Measure elapsed time
    struct timespec start, end, spent;
    int *labels_expected = (int *) malloc(sizeof(int) * IMG_COUNT);
    float *confidences = (float *) malloc(sizeof(float) * IMG_COUNT);

    clock_gettime(CLOCK_MONOTONIC, &start); // Start timer
    recognition(images, network, depth, size, labels_expected, confidences);
    clock_gettime(CLOCK_MONOTONIC, &end); // End timer
    timespec_subtract(&spent, &end, &start);

    // Calculate accuracy
    int i = 0;
    int correct = 0;

    for (i = 0; i < IMG_COUNT; i++) {
        if (labels_actual[i] == labels_expected[i]) correct++;
    }

    float accuracy = (float) correct / (float) IMG_COUNT;

    // Print elapsed time, accuracy
    printf("Elapsed time: %d.%03d sec\n", (int) spent.tv_sec, (int) spent.tv_nsec / 1000000);
    printf("Accuracy: %.3f\n", accuracy);

    // Write result data
    io_file = fopen(argv[2], "wb");

    fprintf(io_file, "%.3f\n", accuracy);

    for (i = 0; i < IMG_COUNT; i++) {
        fprintf(io_file, "%d, %d, %.3f\n", labels_actual[i], labels_expected[i], confidences[i]);
    }

    fclose(io_file);

    return 0;
}

int timespec_subtract(struct timespec *result, struct timespec *x, struct timespec *y) {
    // Perform the carry for the later subtraction by updating y
    if (x->tv_nsec < y->tv_nsec) {
        int nsec = (y->tv_nsec - x->tv_nsec) / 1000000000 + 1;
        y->tv_nsec -= 1000000000 * nsec;
        y->tv_sec += nsec;
    }

    if (x->tv_nsec - y->tv_nsec > 1000000000) {
        int nsec = (x->tv_nsec - y->tv_nsec) / 1000000000;
        y->tv_nsec += 1000000000 * nsec;
        y->tv_sec -= nsec;
    }

    // Compute the time remaining to wait
    // tv_nsec is certainly positive.
    result->tv_sec = x->tv_sec - y->tv_sec;
    result->tv_nsec = x->tv_nsec - y->tv_nsec;

    // Return 1 if result is negative
    return x->tv_sec < y->tv_sec;
}
