#pragma once

#ifndef MLP_H
#define MLP_H 0

#include "Matrix.h"

enum ACTIVE_LIST_{
	SIGMOD = 1,
	TANH,
	LINEAR
};

typedef double (*Func)(double);

typedef struct Active_
{
	Func Function;
	Func Derivative;
} Active;


class CMLP
{
public:
	CMLP(void);
	~CMLP(void);

public:
	void initWeights();
	void initData();
	void calcNet();
	void WeightChangesHO();
	void WeightChangesIH();
	void genHiddenValVector();
	void genWightsMatrix();
	void genDataMatrix();
	double getRand();

	void calcOverallError();
	void displayResults();
	
	void setActiveFunction(ACTIVE_LIST_ Act);
	void learing();

public:
	double RMSerror;
	double LR_IH;
	double LR_HO;

	int m_nEpochs;
	int m_nInputs;
	int m_nPatterns;
	int m_nHidden;
	int m_nPatNum;

	double m_dErrThisPat;
	double m_dOutPred;

	double* m_pHiddenVal;
	double** m_ppWeightsIH;
	double* m_pWeightsHO;

	double **m_pTrainInputs;
	double *m_pTrainOutput;

	
	Active m_pActive; 
};

#endif
