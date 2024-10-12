#include "network.h"
#include <stdlib.h>
#include <stdio.h>

#define ITERS 1000 //doesn't even get to half of it
#define LEARNING_RATE 0.11

int main()
{
    Network network = {0}; //initializes every struct member to 0 or NULL
    initialize_network(&network, 1); //1 input_neuron
    
    //training data
    double inputs[8] = {0,1,2,3,4,5,6,7};

    //outuput doesn't need to be explicitly stated here we can just do @
    double outputs[8] = {0,2,4,6,8,10,12,14}; 

    int i = 0;
    double total_error = 0.0;

    
    do {
        total_error = 0.0;

        for (int j = 0; j < 8; j++)
        {
            network.inputs[0] = inputs[j];  
            double prediction = feedforward(&network); 

            double target = 2*inputs[j];  
            double error = target - prediction;  
            total_error += error * error; 

            update_weights(&network, target, LEARNING_RATE);  
        }

        if (i % 100 == 0) {
            printf("Iteration %d, Total Error: %f\n", i, total_error);
        } //to mointor error

        i++;
    } while (i < ITERS && total_error > 0.00000000000000001); //if error is less than 1.0e^-17

    printf("took %i iterations \n", i);

    for (int j = 0; j < 8; j++)
    {
        network.inputs[0] = inputs[j];
        double prediction = feedforward(&network);
        printf("Input: %f, Predicted: %f, Expected: %f\n", inputs[j], prediction, outputs[j]);
    }

    //test data
    double input_check[5] = {100,200,300,400,1000};

    //put here as a sample we can do 2*input check when prediciting
    double output_check[3] = {200,400,600};


    for (int i = 0; i < 5; i++)
    {
        network.inputs[0] = input_check[i];
        double prediction = feedforward(&network);
        printf("Input: %f, Predicted: %f, Expected: %f\n", input_check[i], prediction, 2*input_check[i]);
    }
    

    free(network.weights);
    free(network.inputs);

    return 0;
}
