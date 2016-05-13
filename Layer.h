// Layer.h
#pragma once

#ifndef LAYER_H
#define LAYER_H 0

#include "Matrix.h"

#include <cstdlib>
#include <ctime>

class CLayer
{
public:
	CLayer(void);
	~CLayer(void);

public:
	void setInputVector(ColumnVector InputVector) { m_vecInput = InputVector; }
	ColumnVector getInputVector() { return m_vecInput; }
	void setNetVector(ColumnVector NetVector) { m_vecNet =  NetVector; }
	ColumnVector getNetVector() { return m_vecNet; }
	void setOutputVector(ColumnVector OutputVector) { m_vecOutput = OutputVector; }
	ColumnVector getOutputVector() { return m_vecOutput; }
	void setTargetVector(ColumnVector TargetVector) { m_vecTarget = TargetVector; }
	ColumnVector getTargetVector() { return m_vecTarget; }
	
	void setWeightMatrix(Matrix WeightMatrix) { m_matWeight = WeightMatrix; }
	Matrix getWeightMatrix() { return m_matWeight; }

	void setWeightColVector(int i, ColumnVector WeightColVector) 
	{
		if (m_matWeight.Nrows() == WeightColVector.Nrows())
		{
			for (int j = 1; j<=WeightColVector.Nrows(); j++)
				m_matWeight(j,i) = WeightColVector(j);
		}
	}

	void InitialWeight()
	{
		srand((unsigned int)time(NULL));

		m_matWeight.ReSize(getSizeOfInput(), getSizeOfOutput());
		for (int i=1; i<=m_matWeight.Nrows(); i++)
		{
			for (int j=1; j<=m_matWeight.Ncols(); j++)
			{
				m_matWeight(i,j) = (double)rand() / (double)RAND_MAX;
				//m_matWeight(i,j) = 1.0;
			}
		}
	}

	ColumnVector getWeightColVector(int i) { return m_matWeight.Column(i); }
	void setWeightEntry(int i, int j, double value) { m_matWeight(i, j) = value; }
	double getWeightEntry(int i, int j) { return m_matWeight(i, j); }

	int getSizeOfInput() { return m_vecInput.Nrows(); }
	//int getSizeOfOutput() { return m_vecOutput.Nrows(); }
	int getSizeOfOutput() { return m_vecInput.Nrows(); }

private:
	ColumnVector m_vecInput;
	ColumnVector m_vecNet;
	ColumnVector m_vecOutput;
	ColumnVector m_vecTarget;

	Matrix m_matWeight;
};

#endif // LAYER_H