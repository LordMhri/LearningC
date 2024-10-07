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

/*sigmoid function used to introduce non-linearity
gives a value between 0 and 1
appraoches 0 for big negative values
appraoches 1 for big positive values
approaches 0 as we approach 0 */
double sigmoid(double x) {
    return 1.0/(1.0 + exp(-x));
}


double* Predict(Network *network,double *inputs){
    double hidden[2];//assuming two hidden neurons in the hidden layer

    //forward propagation through the hidden layer
    for (size_t i = 0; i < network->hiddenNeuronsCount; i++)
    {
        //initialize hidden neuron with it's bias
        // hiddenNeuronActivation = bias[i]
        hidden[i] = network->hiddenBias[i];
        for (size_t j = 0; j < network->inputNeuronsCount; j++)
        {
            //accumulate weighted input to hidden neuron
            //hiddenNeuronActivation = bias + summation of (each input neuron * its corresponding weight)
            hidden[i] += inputs[j]*network->hiddenWeight[j*network->hiddenNeuronsCount + i];
        }
        //applying the sigmoid function to approximate the value to between 0 and 1
        hidden[i] = sigmoid(hidden[i]);
    }

    //forward propagation through the output layer
    double output[1];//one output neuron yes or no
    for (size_t i = 0; i < network->ouptutNeuronsCount; i++)
    {
        output[i] = network->outputBias[i];
        for (size_t j = 0; j < network->hiddenNeuronsCount ; j++)
        {
        // Accumulate weighted input to output neuron
        // outputNeuronActivation = bias + summation of (each hidden neuron * its corresponding weight)

          output[i] += hidden[j] * network->outputWeight[j*network->ouptutNeuronsCount + i];
        }
        //sigmoid function to introduce non-linearity
        output[i] = sigmoid(output[i]);         
    }
    
    return output;
    
}