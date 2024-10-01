#include <math.h>
#include <stdio.h>


typedef float(*FunctionPointer) (float);

float sampleFunc(float x) {
    return  3*x - 2 + cos(x);
}

//the derivative of the given function is calculated here
float derivative(FunctionPointer func,float x) {
//uses the finite difference method 
    float h = 1e-5;
    return (func(x+h) -func(x-h)) / (2*h);
}


float newton_raphson(FunctionPointer func,float x0) { // x0 should be resonably close to the root 
    //uses the tangent property to approximate the zeroes of a root
    float x1;
    int max_iterations = 1000;
    float tolerance = 1e-5;
    int iteration = 0;
    while (iteration < max_iterations)
    {
       float f_x0 = func(x0);
       float df_dx0 = derivative(func,x0);

       if (fabs(f_x0) < tolerance)
       {
        break;// convergence is enough here
       }

        if (df_dx0 == 0)
        {
            printf("Derivative is zero,no solution found\n");
            return x0;
        }

        x1 = x0 - f_x0 /df_dx0; //update x 

        if (fabs(x1 - x0) < tolerance) {
            break; // convergence is enough here
        }

        x0 = x1; //update x0
        iteration++;
          
    }

    return x1;
     
}

int main(int argc, char const *argv[])
{
    float root = newton_raphson(sampleFunc,2.0f);
    printf("root is %f\n",root);
    return 0;
}
