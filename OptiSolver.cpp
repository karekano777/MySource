#include "OptiSolver.h"

void StochasticGradientDescent(pFunc Derivative, CLayer* Layer, double rate, Matrix Weight)
{
	ColumnVector vXata = Layer->getInputVector();
	ColumnVector vTarget = Layer->getTargetVector();
	ColumnVector vNet = Layer->getNetVector();
	ColumnVector vYhat = Layer->getOutputVector();

	for (int i = 1; i<=Layer->getSizeOfOutput(); i++)
	{
		ColumnVector vWeight = Layer->getWeightColVector(i);

		for (int j = 1; j<=Layer->getSizeOfInput(); j++)
		{
			vWeight(j) = vWeight(j) + (Derivative(vNet(i)) * (vTarget(i) - vYhat(i))) * vXata(j);
		}

		for (int j = 1; j<=vWeight.Nrows(); j++)
		{
			Weight(j,i) = vWeight(j);
		}
	}

	Layer->setWeightMatrix(Weight);
}

void NewtonGaussian(pFunc Derivative, CLayer* Layer, double rate, Matrix Weight)
{

}

void LevenbergMarquardt1(pFunc Derivative, CLayer* Layer, double rate, Matrix Weight)
{

}

void LevenbergMarquardt2(pFunc Derivative, CLayer* Layer, double rate, Matrix Weight)
{

}

void ConjugateGradient(pFunc Derivative, CLayer* Layer, double rate, Matrix Weight)
{

}
