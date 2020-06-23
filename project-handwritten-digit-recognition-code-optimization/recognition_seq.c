#include <stdlib.h>
#include <math.h>

#include "recognition.h"

#define sigmoid(x) (1 / (1 + exp(-x)))

void recognition(float *images, float *network, int depth, int size, int *labels, float *confidences) {
    int i, j, x, y;
    float *hidden_layers = (float *) malloc(sizeof(float) * size * depth);
    float **weights = (float **) malloc(sizeof(float *) * (depth + 1));
    float **biases = (float **) malloc(sizeof(float *) * (depth + 1));
    float *weights_zero;
    float *biases_zero;

    // Set pointers for weights and biases
    // Part 1 - Input layer
    weights[0] = network;
    biases[0] = weights[0] + size * IMG_SIZE;
    weights_zero = weights[0];
    biases_zero = biases[0];

    // Part 2 - Hidden layers
    int size_square = size * size;
    int weight_constant = (int) (network + size * IMG_SIZE + size);

    for (i = 1; i < depth; i++) {
        weights[i] = (float *) (weight_constant + (size_square + size) * (i - 1));
        biases[i] = weights[i] + size_square;
    }

    // Part 3 - Output layer
    weights[depth] = weights[depth - 1] + size_square + size;
    biases[depth] = weights[depth] + DIGIT_COUNT * size;

    // Recognize numbers
    int img_size_by_i = 0;

    for (i = 0; i < IMG_COUNT; i++) {
        float *input = images + img_size_by_i;
        float output[DIGIT_COUNT];

        img_size_by_i += IMG_SIZE;

        // From the input layer to the first hidden layer
        int img_size_by_x = 0;

        for (x = 0; x < size; x++) {
            float sum = 0;

            for (y = 0; y < IMG_SIZE; y += 4) {
                sum += input[y] * weights_zero[img_size_by_x + y];
                sum += input[y + 1] * weights_zero[img_size_by_x + y + 1];
                sum += input[y + 2] * weights_zero[img_size_by_x + y + 2];
                sum += input[y + 3] * weights_zero[img_size_by_x + y + 3];
            }

            img_size_by_x += IMG_SIZE;
            sum += biases_zero[x];
            hidden_layers[x] = sigmoid(sum);
        }

        // Between hidden layers
        int size_by_j = size;
        int size_by_x = 0;

        for (j = 1; j < depth; j++) {
            for (x = 0; x < size; x++) {
                float sum = 0;

                for (y = 0; y < size; y += 4) {
                    sum += hidden_layers[size_by_j - size + y] * weights[j][size_by_x + y];
                    sum += hidden_layers[size_by_j - size + y + 1] * weights[j][size_by_x + y + 1];
                    sum += hidden_layers[size_by_j - size + y + 2] * weights[j][size_by_x + y + 2];
                    sum += hidden_layers[size_by_j - size + y + 3] * weights[j][size_by_x + y + 3];
                }

                size_by_x += size;

                sum += biases[j][x];
                hidden_layers[size_by_j + x] = sigmoid(sum);
            }

            size_by_j += size;
        }

        // From the last hidden layer to the output layer
        int size_by_depthminus1 = size * (depth - 1);
        size_by_x = 0;

        for (x = 0; x < DIGIT_COUNT; x++) {
            float sum = 0;

            for (y = 0; y < size; y += 4) {
                sum += hidden_layers[size_by_depthminus1 + y] * weights[depth][size_by_x + y];
                sum += hidden_layers[size_by_depthminus1 + y + 1] * weights[depth][size_by_x + y + 1];
                sum += hidden_layers[size_by_depthminus1 + y + 2] * weights[depth][size_by_x + y + 2];
                sum += hidden_layers[size_by_depthminus1 + y + 3] * weights[depth][size_by_x + y + 3];
            }

            size_by_x += size;

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
