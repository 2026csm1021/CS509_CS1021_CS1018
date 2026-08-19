#ifndef GRADIENT_DESCENT_H
#define GRADIENT_DESCENT_H

#include <vector>

using namespace std;

struct GDResult
{
    double finalX;
    double finalFx;
    int iterations;
    bool converged;
};
double evaluateFunction(const vector<double>& coefficients, double x);
double evaluateDerivative(const vector<double>& coefficients, double x);

GDResult gradientDescent(const vector<double>& coefficients, double x,
                          double learningRate, double tolerance, int maxIterations);

#endif
