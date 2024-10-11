#include <stdio.h>
#include "neural.h"

#define ITERS 400000
#define LEARNING_RATE 0.1

// Function to calculate the parity (even/odd) of a binary number
size_t parity(size_t i) {
    return __builtin_popcount(i) % 2 == 0;
}

int main() {
    Network network = {0};
    initializeNetwork(&network,3,2,1);


    // Generate training data (all 3-bit numbers)
    double inputs[8][3] = {
        {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
        {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}
    };
    double outputs[8] = {1, 1, 0, 1, 0, 1, 1, 0};  // Even parity: 1, Odd parity: 0

     for (int i = 0; i < ITERS; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            train(&network,inputs[j],&outputs[j],LEARNING_RATE);
            if (i % 10000 == 0) {
    double* prediction = predict(&network, inputs[0]);
    printf("Iteration %d: Prediction for [0, 0, 0] = %.3f\n", i, prediction[0]);
}
        }
        
    }

    // test network
    printf("Input  | Predicted | Expected\n");
    printf("-----------------------------\n");
    for(size_t i = 0; i < 8; i++) {
        double* prediction = predict(&network, inputs[i]);
        printf("%d%d%d    | %.3f      | %.0f\n", (int)inputs[i][0], (int)inputs[i][1], (int)inputs[i][2], prediction[0], outputs[i]);
    }

    return 0;
}
