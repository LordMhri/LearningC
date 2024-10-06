#include "neural.h"
#include <stdlib.h>
#include <math.h>


double randf(){
    return (double)rand()/ RAND_MAX; //generates a random number between 0 and 1
    //rand generates a number between 0 and 2^(31)-1
    //RAND_MAX is 2^(31) - 1
}


Network createNetwork(size_t inputCount,size_t hiddenCount,size_t outputCount){
    Network network;
    network.inputNeuronsCount = inputCount;
    network.ouptutNeuronsCount = outputCount;
    network.hiddenNeuronsCount = hiddenCount;

    //allocate memory for weights and biases
    network.hiddenWeight = malloc(inputCount * hiddenCount * sizeof(double));
    network.hiddenBias = malloc(hiddenCount * sizeof(double));
    network.outputWeight = malloc(hiddenCount * outputCount * sizeof(double));
    network.outputBias = malloc(outputCount * sizeof(double));

    //initialize weights and biases randomly
    for (size_t i = 0; i < inputCount*hiddenCount; i++)
    {
        network.hiddenWeight[i] = randf();
    }
    for (size_t i = 0; i < hiddenCount; i++)
    {
        network.hiddenBias[i] = randf();
    }
    for (size_t i = 0; i < outputCount*hiddenCount; i++)
    {
        network.outputWeight[i] = randf();
    }
    for (size_t i = 0; i < outputCount; i++)
    {
        network.outputBias[i] = randf();
    }

}

void freeNetwork(Network *network) {
    free(network->hiddenWeight);
    free(network->hiddenBias);
    free(network->outputWeight);
    free(network->outputBias);
}
