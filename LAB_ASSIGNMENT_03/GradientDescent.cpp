#include "GradientDescent.h"
#include <cmath>

using namespace std;

double evaluateFunction(const vector<double>& coefficients, double x)
{
    double result = 0.0;

    for (size_t i = 0; i < coefficients.size(); i++)
    {
        result += coefficients[i] * pow(x, (double)i);
    }

    return result;
}

double evaluateDerivative(const vector<double>& coefficients, double x)
{
    double result = 0.0;

    for (size_t i = 1; i < coefficients.size(); i++)
    {
        result += (double)i * coefficients[i] * pow(x, (double)(i - 1));
    }

    return result;
}

GDResult gradientDescent(const vector<double>& coefficients, double x,
                          double learningRate, double tolerance, int maxIterations)
{
    bool converged = false;
    int iterations = 0;

    for (int i = 0; i < maxIterations; i++)
    {
        double gradient = evaluateDerivative(coefficients, x);

        // Convergence check
        if (abs(gradient) <= tolerance)
        {
            converged = true;
            break;
        }

        // Gradient Descent update
        x = x - learningRate * gradient;

        iterations++;
    }

    double finalFx = evaluateFunction(coefficients, x);

    return {x, finalFx, iterations, converged};
}
