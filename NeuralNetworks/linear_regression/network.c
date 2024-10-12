#include "network.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void initialize_network(Network* network,int input_neurons) {
    network->input_neurons = input_neurons;
    network->output_neurons = 1;
    network->weights = calloc(input_neurons,sizeof(*network->weights));
    network->inputs = calloc(input_neurons,sizeof(*network->inputs));

    //initialize random values for weights and biases
    for (int i = 0; i < input_neurons; i++)
    {
        network->weights[i] =  ((double) rand() / (RAND_MAX));
    }
    network->bias = ( (double) rand() / (RAND_MAX));
    
}
//This calculates the prediction or output of the neural network based on the given inputes.
double feedforward(Network *network){
    double sum = 0.0;

    for (int i = 0; i < network->input_neurons; i++)
    {
        sum += network->weights[i] * network->inputs[i];
    }

    network->output = sum + network->bias;

    return network->output;

}
//updates weights and errors based on the errors
void update_weights( Network *network, double target, double learning_rate) {
    double error = target-network->output;


    for (int i = 0; i < network->input_neurons; i++)
    {   
        //increases weights if error is postive and decreases if not 
        network->weights[i] += learning_rate*error*network->inputs[i];
    }
    
    //increases bias if error is postive and decreases if not 
    network->bias += learning_rate * error;
}