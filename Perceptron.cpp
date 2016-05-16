<<<<<<< HEAD
#include "Perceptron.h"

#include <iostream>
#include <windows.h>

CPerceptron::CPerceptron(void)
{
}


CPerceptron::~CPerceptron(void)
{
}

//void CPerceptron::ForwardPropagation(CMultilayer* Layers)
//{
//	Layers->gotoFirstLayer();
//
//	CLayer* Layer = Layers->getLayer();
//	for (int iLayer=1; iLayer<=Layers->getLayerNumber(); iLayer++)
//	{
//		ColumnVector vXData = Layer->getInputVector();
//		int nYSize = Layer->getSizeOfOutput();
//		ColumnVector vYhat;
//		vYhat.ReSize(nYSize, 1);
//		for (int iRowCnt = 1; iRowCnt<=nYSize; iRowCnt++)
//			vYhat(iRowCnt) = 0.0;
//
//		ColumnVector vNet;
//		vNet.ReSize(nYSize, 1);
//		for (int iRowCnt = 1; iRowCnt<=nYSize; iRowCnt++)
//			vNet(iRowCnt) = 0.0;
//
//		double fVal = 0.0;
//		for (int i = 1; i<=Layer->getSizeOfOutput(); i++)
//		{
//			fVal = 0.0;
//			ColumnVector vWeight = Layer->getWeightColVector(i);
//			for (int j = 1; j<=vWeight.Nrows(); j++)
//			{
//				if (j <= Layer->getSizeOfInput())
//					fVal += vWeight(j)*vXData(j);
//				else
//					fVal += vWeight(j);
//			}
//			vNet(i) = fVal;
//			vYhat(i) = m_active.pFunction(vNet(i));
//		}
//
//		Layer->setNetVector(vNet);
//		Layer->setOutputVector(vYhat);
//		//Layers->updateLayer(Layer, iLayer);
//
//		ColumnVector vTarget = Layer->getTargetVector();
//		Layers->nextLayer();
//		if (!Layers->isEndLayer())
//		{
//			Layer = Layers->getLayer();
//			Layer->setInputVector(vYhat);
//		}
//	}
//}

void CPerceptron::ForwardPropagation(CMultilayer* Layers)
{
	Layers->gotoFirstLayer();
	CLayer* Layer = Layers->getLayer();

	for (int iLayer=1; iLayer<=Layers->getLayerNumber(); iLayer++)
	{
		ColumnVector vXData = Layer->getInputVector();
		int nYSize = Layer->getSizeOfOutput();

		ColumnVector vYhat;
		vYhat.ReSize(nYSize, 1);

		ColumnVector vNet;
		vNet.ReSize(nYSize, 1);

		double fVal = 0.0;
		for (int i = 1; i<=Layer->getSizeOfOutput(); i++)
		{
			fVal = 0.0;
			ColumnVector vWeight = Layer->getWeightColVector(i);
			for (int j = 1; j<=vWeight.Nrows(); j++)
				fVal += vWeight(j)*vXData(j);
			vNet(i) = fVal;
			vYhat(i) = m_active.pFunction(vNet(i));
		}
		Layer->setNetVector(vNet);
		Layer->setOutputVector(vYhat);

		Layers->nextLayer();
		if (!Layers->isEndLayer())
		{
			Layer = Layers->getLayer();
			Layer->setInputVector(vYhat);
		}
	}
}

//void CPerceptron::BackwardPropagation(CMultilayer* Layers)
//{
//	Layers->gotoEndLayer();
//
//	ColumnVector vnewDelta;
//	ColumnVector vpreDelta;
//	Matrix matpreWeight;
//
//	CLayer* Layer = Layers->getLayer();
//	for (int iLayer=1; iLayer<=Layers->getLayerNumber(); iLayer++)
//	{
//		//Matrix Weight;
//		//Weight.ReSize(Layer->getSizeOfInput(), Layer->getSizeOfOutput());
//		//Weight = Layer->getWeightMatrix();
//
//		// Make dleta
//
//		ColumnVector vXata = Layer->getInputVector();
//		ColumnVector vTarget = Layer->getTargetVector();
//		ColumnVector vNet = Layer->getNetVector();
//		ColumnVector vYhat = Layer->getOutputVector();
//		Matrix matWeight = Layer->getWeightMatrix();
//
//		vnewDelta.ReSize(Layer->getSizeOfOutput(), 1);
//
//		if (iLayer == 1)
//		{
//			for (int i = 1; i<=Layer->getSizeOfOutput(); i++)
//			{
//				vnewDelta(i) = m_active.pDerivative(vNet(i)) * (vTarget(i) - vYhat(i));
//			}
//		}
//		else
//		{
//			ColumnVector vecSumDOW;
//			vecSumDOW.ReSize(Layer->getSizeOfOutput(),1);
//			for (int i=1; i<=vecSumDOW.Nrows(); i++)
//			{
//				vecSumDOW(i) = 0;
//				for (int j=1; j<vpreDelta.Nrows(); j++)
//				{
//					vecSumDOW(i) += matpreWeight(j,i)*vpreDelta(j);
//				}
//				vnewDelta(i) = m_active.pDerivative(vNet(i)) * vecSumDOW(i);
//			}
//		}
//
//		m_solver(m_active.pDerivative, Layer, m_rate);
//		//Layers->updateLayer(Layer, iLayer);
//
//		Layers->preLayer();
//		if (!Layers->isFirstLayer())
//		{
//			Layer = Layers->getLayer();
//		}
//
//		vpreDelta = vnewDelta;
//		matpreWeight = Layer->getWeightMatrix();
//	}
//}

void CPerceptron::BackwardPropagation(CMultilayer* Layers)
{
	Layers->gotoEndLayer();

	CLayer* Layer = Layers->getLayer();
	for (int iLayer=Layers->getLayerNumber(); iLayer>=1; iLayer--)
	{
		ColumnVector vecDelta;
		ColumnVector vecPreDelta;

		Matrix matWeight = Layer->getWeightMatrix();
		Matrix matPreWeight;

		ColumnVector vecTarget = Layer->getTargetVector();
		ColumnVector vecOutput = Layer->getOutputVector();
		ColumnVector vecNet = Layer->getNetVector();
		ColumnVector vecInput = Layer->getInputVector();

		if (iLayer == Layers->getLayerNumber())
		{
			vecDelta.ReSize(vecOutput.Nrows(), 1);
			for (int k=1; k<=vecDelta.Nrows(); k++)
			{
				vecDelta(k) = (vecTarget(k) - vecOutput(k))*m_active.pDerivative(vecNet(k));
			}
		}
		else
		{
			vecDelta.ReSize(vecOutput.Nrows(), 1);
			ColumnVector vecSumD;
			vecSumD.ReSize(vecOutput.Nrows(), 1);
			for (int k=1; k<=vecDelta.Nrows(); k++)
			{
				vecSumD(k) = 0.0;
				for (int j=1;j<=vecPreDelta.Nrows(); j++)
				{
					vecSumD(k) += matPreWeight(k,j)*vecPreDelta(j);
				}
				vecDelta(k) = vecSumD(k)*m_active.pDerivative(vecNet(k));
			}
		}


		for (int i=1; i<=matWeight.Ncols(); i++)
		{
			for (int j=1; j<=matWeight.Nrows(); j++)
			{
				matWeight(j,i) = matWeight(j,i) + m_rate*vecDelta(i)*vecInput(j);
			}
		}

		Layer->setWeightMatrix(matWeight);
		vecPreDelta = vecDelta;
		matPreWeight = matWeight;

		Layers->preLayer();
		if (!Layers->isFirstLayer())
		{
			Layer = Layers->getLayer();
		}

	}
}

void CPerceptron::Learning()
{
	for (int iMlayer=0; iMlayer<(int)m_vMultilayer.size(); iMlayer++)
	{
		int iterStop = 0;
		double MSE = 0.0;
		CMultilayer* Layers = &(m_vMultilayer[iMlayer]);
		for (int iSet = 1; iSet<=Layers->getTrainingNumber(); iSet++)
		{
			Layers->updateTrainingData(iSet);
			for (int iter = 1; iter<=m_itermax; iter++)
			{
				if (iSet == 1 && iter == 1)
				{
					Layers->gotoFirstLayer();
					for (int iLayer=1; iLayer<=Layers->getLayerNumber(); iLayer++)
					{
						CLayer* Layer = Layers->getLayer();
						Layer->InitialWeight();
						Layers->nextLayer();
						//Layers->updateLayer(Layer, iLayer);
					}
				}

				ForwardPropagation(Layers);
				BackwardPropagation(Layers);

				//if (!(Layers->isEndLayer()))
				//	Layers->gotoEndLayer();

				Layers->gotoEndLayer();
				CLayer* Layer = Layers->getLayer();
				ColumnVector vTarget = Layer->getTargetVector();
				ColumnVector vYhat = Layer->getOutputVector();

				MSE = (((vTarget - vYhat).t() * (vTarget - vYhat) )).as_scalar() / (double)(vYhat.Nrows()-1);
				std::cout<<"iter= "<<iter<<" ";
				for (int i=1; i<=vYhat.Nrows(); i++)
					std::cout<<vYhat(i)<<", ";
				std::cout<<"MSE= "<<MSE<<endl;

				iterStop = iter;
				if (MSE < m_tolerance)
				{
					break;
				}
			}
			std::cout<<"Stage= "<<iMlayer<<", iSet= "<<iSet<<", iter= "<<iterStop<<", MSE = "<<MSE<<std::endl;
			Sleep(5000); // windows.h
		}
	}
}

bool CPerceptron::setActiveFunc(ACTIVE_LIST_ ACTIVE)
{
	pFunc pFunction  = NULL;
	pFunc pDerivative = NULL;

	switch(ACTIVE)
	{
	case SIGMOD:
		pFunction = sigmod;
		pDerivative = sigmod_Derivative;
		break;
	case TANH:
		pFunction = tanh;
		pDerivative = tanh_Derivative;
		break;
	default:
		break;
	}

	m_active.pFunction = pFunction;
	m_active.pDerivative = pDerivative;

	if (m_active.pFunction && m_active.pDerivative)
	{
		pFunction = NULL;
		pDerivative = NULL;
		return true;
	}
	
	return false;
}

bool CPerceptron::setSolver(SOLVER_LIST_ SOLVER)
{
	m_solver = NULL;

	switch(SOLVER)
	{
	case SGD:
		m_solver = StochasticGradientDescent;
		break;
	case NG:
		m_solver = NewtonGaussian;
		break;
	case LM1:
		m_solver = LevenbergMarquardt1;
		break;
	case LM2:
		m_solver = LevenbergMarquardt2;
		break;
	case CG:
		m_solver = ConjugateGradient;
		break;
	default:
		break;
	}

	if (m_solver)
		return true;

	return false;
}
=======
#include "Perceptron.h"

#include <iostream>
#include <windows.h>

CPerceptron::CPerceptron(void)
{
}


CPerceptron::~CPerceptron(void)
{
}

void CPerceptron::ForwardPropagation(CMultilayer* Layers)
{
	Layers->gotoFirstLayer();

	CLayer* Layer = Layers->getLayer();
	for (int iLayer=1; iLayer<=Layers->getLayerNumber(); iLayer++)
	{
		ColumnVector vXData = Layer->getInputVector();
		int nYSize = Layer->getSizeOfOutput();
		ColumnVector vYhat;
		vYhat.ReSize(nYSize, 1);
		for (int iRowCnt = 1; iRowCnt<=nYSize; iRowCnt++)
			vYhat(iRowCnt) = 0.0;

		ColumnVector vNet;
		vNet.ReSize(nYSize, 1);
		for (int iRowCnt = 1; iRowCnt<=nYSize; iRowCnt++)
			vNet(iRowCnt) = 0.0;

		double fVal = 0.0;
		for (int i = 1; i<=Layer->getSizeOfOutput(); i++)
		{
			fVal = 0.0;
			ColumnVector vWeight = Layer->getWeightColVector(i);
			for (int j = 1; j<=vWeight.Nrows(); j++)
			{
				if (j <= Layer->getSizeOfInput())
					fVal += vWeight(j)*vXData(j);
				else
					fVal += vWeight(j);
			}
			vNet(i) = fVal;
			vYhat(i) = m_active.pFunction(vNet(i));
		}

		Layer->setNetVector(vNet);
		Layer->setOutputVector(vYhat);
		//Layers->updateLayer(Layer, iLayer);

		ColumnVector vTarget = Layer->getTargetVector();
		Layers->nextLayer();
		if (!Layers->isEndLayer())
		{
			Layer = Layers->getLayer();
			Layer->setInputVector(vYhat);
		}
	}
}

void CPerceptron::BackwardPropagation(CMultilayer* Layers)
{
	Layers->gotoEndLayer();

	CLayer* Layer = Layers->getLayer();
	for (int iLayer=1; iLayer<=Layers->getLayerNumber(); iLayer++)
	{
		Matrix Weight;
		//Weight.ReSize(Layer->getSizeOfInput(), Layer->getSizeOfOutput());
		Weight = Layer->getWeightMatrix();

		m_solver(m_active.pDerivative, Layer, m_rate, Weight);
		//Layers->updateLayer(Layer, iLayer);

		Layers->preLayer();
		if (!Layers->isFirstLayer())
		{
			Layer = Layers->getLayer();
		}
	}
}

void CPerceptron::Learning()
{
	for (int iMlayer=0; iMlayer<(int)m_vMultilayer.size(); iMlayer++)
	{
		int iterStop = 0;
		double MSE = 0.0;
		CMultilayer* Layers = &(m_vMultilayer[iMlayer]);
		for (int iSet = 1; iSet<=Layers->getTrainingNumber(); iSet++)
		{
			Layers->updateTrainingData(iSet);
			for (int iter = 1; iter<=m_itermax; iter++)
			{
				if (iSet == 1&& iter == 1)
				{
					Layers->gotoFirstLayer();
					for (int iLayer=1; iLayer<=Layers->getLayerNumber(); iLayer++)
					{
						CLayer* Layer = Layers->getLayer();
						Layer->InitialWeight();
						Layers->nextLayer();
						//Layers->updateLayer(Layer, iLayer);
					}
				}

				ForwardPropagation(Layers);
				BackwardPropagation(Layers);

				//if (!(Layers->isEndLayer()))
				//	Layers->gotoEndLayer();

				Layers->gotoEndLayer();
				CLayer* Layer = Layers->getLayer();
				ColumnVector vTarget = Layer->getTargetVector();
				ColumnVector vYhat = Layer->getOutputVector();

				MSE = (((vTarget - vYhat).t() * (vTarget - vYhat) )).as_scalar() / (double)(vYhat.Nrows()-1);
				std::cout<<"iter= "<<iter<<" ";
				for (int i=1; i<=vYhat.Nrows(); i++)
					std::cout<<vYhat(i)<<", ";
				std::cout<<"MSE= "<<MSE<<endl;

				iterStop = iter;
				if (MSE < m_tolerance)
				{
					break;
				}
			}
			std::cout<<"Stage= "<<iMlayer<<", iSet= "<<iSet<<", iter= "<<iterStop<<", MSE = "<<MSE<<std::endl;
			Sleep(5000); // windows.h
		}
	}
}

bool CPerceptron::setActiveFunc(ACTIVE_LIST_ ACTIVE)
{
	pFunc pFunction  = NULL;
	pFunc pDerivative = NULL;

	switch(ACTIVE)
	{
	case SIGMOD:
		pFunction = sigmod;
		pDerivative = sigmod_Derivative;
		break;
	case TANH:
		pFunction = tanh;
		pDerivative = tanh_Derivative;
		break;
	default:
		break;
	}

	m_active.pFunction = pFunction;
	m_active.pDerivative = pDerivative;

	if (m_active.pFunction && m_active.pDerivative)
	{
		pFunction = NULL;
		pDerivative = NULL;
		return true;
	}
	
	return false;
}

bool CPerceptron::setSolver(SOLVER_LIST_ SOLVER)
{
	m_solver = NULL;

	switch(SOLVER)
	{
	case SGD:
		m_solver = StochasticGradientDescent;
		break;
	case NG:
		m_solver = NewtonGaussian;
		break;
	case LM1:
		m_solver = LevenbergMarquardt1;
		break;
	case LM2:
		m_solver = LevenbergMarquardt2;
		break;
	case CG:
		m_solver = ConjugateGradient;
		break;
	default:
		break;
	}

	if (m_solver)
		return true;

	return false;
}
>>>>>>> origin/master
