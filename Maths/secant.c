#include <stdio.h>
#include <math.h>

typedef float(*FunctionPointer)(float);

float sampleFunc(float x){
    return 5*x - 4 + (float)sin(x);
}


//given the function and two numbers reasonably close to the root
//draw a straight line that intersects func(x0) and func(x1) (hence the name secant)
//and where the straight line intersects the x-axis will be closer to the root
//than both x0 and x1, so iteratively find a closer one until we reach the precision level needed
float secantMethod(FunctionPointer func,float x0,float x1){
    float x2;//x2 is the variable to hold the closest number to the root we find
    
    //this is the formula for it,find the graph of the function
    //choose two points x0 and x1 draw a straight line between func(x0) and func(x1)
    //there will be two similar triangles formed , that's how we get this function
    x2 = x1 - (func(x1) * (x1 - x0)) / (func(x1) - func(x0));

    while (fabs(func(x2)) >= 0.00001) //0.00001 is the precision level
    {
        x2 = x1 - (func(x1) * (x1 - x0)) / (func(x1) - func(x0)); // move x2 closer to the root on every iteration

        x0 = x1;//update x0 with x1, moving it closer to the root
        
        x1 = x2;//updtae x1 with x2, moves it closer to the root
    }
    

    return x2;
    
}

int main(int argc, char const *argv[])
{
    float root = secantMethod(sampleFunc,5,9);
    printf("root is %f\n ", root);

    return 0;
}

//doesn't work for some cases where the function is far from linear near the root
//graph should be plotted before using this

