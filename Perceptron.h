// Perceptron.h
#pragma once

#ifndef PERCEPTRON_H
#define PERCEPTRON_H 0

#include "Matrix.h"
#include "Multilayer.h"
#include "Layer.h"
#include "OptiSolver.h"
#include "ActiveFunction.h"

#include <vector>

enum ACTIVE_LIST_{
	SIGMOD = 1,
	TANH
};

enum SOLVER_LIST_{
	SGD = 1, //		// Stochastic Gradient Descent Method
	NG,				// Newton-Gaussian Method
	LM1,			// Levenberg-Marquardt Type1 Method (diagonal entry 1 Ver.)
	LM2,			// Levenberg-Marquardt Type2 Method (diagonal entry i==j Ver.)
	CG				// Conjugate Gradient Method
};

typedef double (*pFunc)(double);
typedef void (*pSolver)(pFunc, CLayer*, double);
typedef void (*ppSolver) (CLayer*, double);

typedef struct ActiveFunc_
{
	pFunc pFunction;
	pFunc pDerivative;

} ActiveFunc;

class CPerceptron
{
public:
	CPerceptron(void);
	~CPerceptron(void);

public:
	void ForwardPropagation(CMultilayer* layers);
	void BackwardPropagation(CMultilayer* layers);
	void Learning();

	bool setActiveFunc(ACTIVE_LIST_ ACTIVE);
	bool setSolver(SOLVER_LIST_ SOLVER);
	void setCondition(double talerance, int itermax)
	{
		m_tolerance = talerance;
		m_itermax = itermax;
	}

	void setLearningRate(double rate) { m_rate = rate; }

public:
	ActiveFunc m_active;
	pSolver m_solver;
	
	int m_itermax;

	double m_tolerance;
	double m_rate;

	std::vector<CMultilayer> m_vMultilayer;
};

#endif //PERCEPTRON_H

