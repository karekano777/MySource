#pragma once

#ifndef OPtiSOLVER_H
#define OPtiSOLVER_H 0

#include "Layer.h"
#include "Matrix.h"
#include "OptiSolver.h"

typedef double (*pFunc)(double);

void StochasticGradientDescent(pFunc Derivative, CLayer* Layer, double rate);
void NewtonGaussian(pFunc Derivative, CLayer* Layer, double rate);
void LevenbergMarquardt1(pFunc Derivative, CLayer* Layer, double rate);
void LevenbergMarquardt2(pFunc Derivative, CLayer* Layer, double rate);
void ConjugateGradient(pFunc Derivative, CLayer* Layer, double rate);

#endif // OPtiSOLVER_H
