#include <stdio.h>
#include "neural.h"

#define ITERS  10000
#define LEARNING_RATE 1.5

// Function to calculate the parity (even/odd) of a binary number
size_t parity(size_t i) {
    return __builtin_popcount(i) % 2 == 0;
}

int main() {
    // Initialize the network
    Network network = createNetwork(3, 2, 1);  // 3 inputs (3-bit numbers), 2 hidden neurons, 1 output


    // Generate training data (all 3-bit numbers)
    double inputs[8][3] = {
        {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
        {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}
    };
    double outputs[8] = {1, 1, 0, 1, 0, 1, 1, 0};  // Even parity: 1, Odd parity: 0

    // Train the network
    for (size_t i = 0; i < ITERS; i++) {
        for (size_t j = 0; j < 8; j++) {
            Train(&network, inputs[j], &outputs[j], LEARNING_RATE);
        }
    }

    // test network
    printf("Input  | Predicted | Expected\n");
    printf("-----------------------------\n");
    for(size_t i = 0; i < 8; i++) {
        double* prediction = Predict(&network, inputs[i]);
        printf("%d%d%d    | %.3f      | %.0f\n", (int)inputs[i][0], (int)inputs[i][1], (int)inputs[i][2], prediction[0], outputs[i]);
    }

    // free network
    freeNetwork(&network);

    return 0;
}
