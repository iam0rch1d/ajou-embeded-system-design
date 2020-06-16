#include <stdlib.h>
#include <math.h>

#include "recognition.h"

#define sigmoid(x) (1 / (1 + exp(-x)))

void recognition(float *images, float *network, int depth, int size, int *labels, float *confidences) {
    int i, j, x, y;
    float *hidden_layers = (float *) malloc(sizeof(float) * size * depth);
    float **weights = (float **) malloc(sizeof(float *) * (depth + 1));
    float **biases = (float **) malloc(sizeof(float *) * (depth + 1));

    // Set pointers for weights and biases
    // Part 1 - Input layer
    weights[0] = network;
    biases[0] = weights[0] + size * IMG_SIZE;

    // Part 2 - Hidden layers
    int size_square = size * size;
    for (i = 1; i < depth; i++) {
        weights[i] = network + (size * IMG_SIZE + size) + (size_square + size) * (i - 1);
        biases[i] = weights[i] + size_square;
    }

    // Part 3 - Output layer
    weights[depth] = weights[depth - 1] + size_square + size;
    biases[depth] = weights[depth] + DIGIT_COUNT * size;

    // Recognize numbers
    for (i = 0; i < IMG_COUNT; i++) {
        float *input = images + IMG_SIZE * i;
        float output[DIGIT_COUNT];

        // From the input layer to the first hidden layer
        for (x = 0; x < size; x++) {
            float sum = 0;
            int img_size_by_x = IMG_SIZE * x;

            for (y = 0; y < IMG_SIZE; y++) {
                sum += input[y] * weights[0][img_size_by_x + y];
            }

            sum += biases[0][x];
            hidden_layers[x] = sigmoid(sum);
        }

        // Between hidden layers
        for (j = 1; j < depth; j++) {
            for (x = 0; x < size; x++) {
                float sum = 0;
                int size_by_j = size * j;
                int size_by_x = size * x;

                for (y = 0; y < size; y++) {
                    sum += hidden_layers[size_by_j - size + y] * weights[j][size_by_x + y];
                }

                sum += biases[j][x];
                hidden_layers[size_by_j + x] = sigmoid(sum);
            }
        }

        // From the last hidden layer to the output layer
        for (x = 0; x < DIGIT_COUNT; x++) {
            float sum = 0;
            int size_by_depthminus1 = size * (depth - 1);
            int size_by_x = size * x;

            for (y = 0; y < size; y++) {
                sum += hidden_layers[size_by_depthminus1 + y] * weights[depth][size_by_x + y];
            }

            sum += biases[depth][x];
            output[x] = sigmoid(sum);
        }

        // Find the answer
        float max = 0;
        int label = 0;

        for (x = 0; x < DIGIT_COUNT; x++) {
            if (output[x] > max) {
                label = x;
                max = output[x];
            }
        }

        // Store the result
        confidences[i] = max;
        labels[i] = label;
    }
}
