#ifndef NETWORK_H
#define NETWORK_H


typedef struct Network
{
    int input_neurons;     
    int output_neurons;    

    double *weights;       
    double bias;           

    double *inputs;        
    double output;         
} Network;


void initialize_network( Network *network, int input_neurons);
double feedforward( Network *network);
void update_weights( Network *network, double target, double learning_rate);

#endif
