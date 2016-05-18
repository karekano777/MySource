#include "MLP.h"

#include <cstdio>

double f_sigmod(double x) { return 1. / (1 + exp(-x)); }
double dev_sigmod(double x) {
	//return f_sigmod(x) * (1 - f_sigmod(x));
	return x*(1-x);
}
double f_tanh(double x) { return tanh(x); }
double dev_tanh(double x) {
	//return 1. - f_tanh(x) * f_tanh(x);
	return 1.-x*x;
}
double f_linear(double x) { return x; }
double dev_linear(double x) { return 1; }

CMLP::CMLP(void)
{
	LR_IH = 0.0;
	LR_HO = 0.0;
	RMSerror = 0.0;

	m_nInputs = 0;
	m_nPatterns = 0;
	m_nHidden = 0;

	m_nEpochs = 0;
	m_nPatNum = 0;
	m_dErrThisPat = 0.0;
	m_dOutPred = 0.0;

	m_pHiddenVal = NULL;
	m_ppWeightsIH = NULL;
	m_pWeightsHO = NULL;

	m_pTrainInputs = NULL;
	m_pTrainOutput = NULL;

}

CMLP::~CMLP(void)
{
	delete[] m_pHiddenVal;

	for (int i=1; i<m_nInputs; i++)
		delete[] m_ppWeightsIH[i];
	delete[] m_ppWeightsIH;
	delete[] m_pWeightsHO;

	for (int i=1; i<m_nPatterns; i++)
		delete[] m_pTrainInputs[i];
	delete[] m_pTrainInputs;
	delete[] m_pTrainOutput;
}

// calculates the network output
void CMLP::calcNet()
{
	int i = 0;
	for(i = 0;i<m_nHidden;i++)
	{
		m_pHiddenVal[i] = 0.0;

		for(int j = 0;j<m_nInputs;j++)
		{
			m_pHiddenVal[i] = m_pHiddenVal[i] + (m_pTrainInputs[m_nPatNum][j] * m_ppWeightsIH[j][i]);
		}

		m_pHiddenVal[i] = m_pActive.Function(m_pHiddenVal[i]);
	}

	m_dOutPred = 0.0;
	for(i = 0;i<m_nHidden;i++)
	{
		m_dOutPred = m_dOutPred + m_pHiddenVal[i] * m_pWeightsHO[i];
	}

	m_dErrThisPat = m_dOutPred - m_pTrainOutput[m_nPatNum];

}

//adjust the weights hidden-output
void CMLP::WeightChangesHO()
{
	for(int k = 0;k<m_nHidden;k++)
	{
		double weightChange = LR_HO * m_dErrThisPat * m_pHiddenVal[k];
		m_pWeightsHO[k] = m_pWeightsHO[k] - weightChange;

		//regularisation on the output weights
		if (m_pWeightsHO[k] < -5)
		{
			m_pWeightsHO[k] = -5;
		}
		else if (m_pWeightsHO[k] > 5)
		{
			m_pWeightsHO[k] = 5;
		}
	}

}

// adjust the weights input-hidden
void CMLP::WeightChangesIH()
{
	for(int i = 0;i<m_nHidden;i++)
	{
		for(int k = 0;k<m_nInputs;k++)
		{
			double x = m_pActive.Derivative(m_pHiddenVal[i]);
			x = x * m_pWeightsHO[i] * m_dErrThisPat * LR_IH;
			x = x * m_pTrainInputs[m_nPatNum][k];
			double weightChange = x;
			m_ppWeightsIH[k][i] = m_ppWeightsIH[k][i] - weightChange;
		}
	}
}

void CMLP::genHiddenValVector()
{
	// the outputs of the hidden neurons
	m_pHiddenVal = new double[m_nHidden];
}

void CMLP::genWightsMatrix()
{
	// the weights
	m_ppWeightsIH = new double*[m_nInputs];
	for (int i=0; i<m_nInputs; i++)
		m_ppWeightsIH[i] = new double[m_nHidden];

	m_pWeightsHO = new double[m_nHidden];
}

void CMLP::genDataMatrix()
{
	// the data
	m_pTrainInputs = new double*[m_nPatterns];
	for (int i=0; i<m_nPatterns; i++)
		m_pTrainInputs[i] = new double[m_nInputs];

	m_pTrainOutput = new double[m_nPatterns];
}

double CMLP::getRand()
{
	// generates a random number
	return ((double)rand())/(double)RAND_MAX;
}

void CMLP::initWeights(void)
{
	// set weights to random numbers 
	for(int j = 0;j<m_nHidden;j++)
	{
		m_pWeightsHO[j] = (getRand() - 0.5) / 2.; // Output + 1;
		for(int i = 0;i<m_nInputs;i++)
		{
			m_ppWeightsIH[i][j] = (getRand() - 0.5) / (double)(m_nPatterns + 1);
			printf("Weight = %f\n", m_ppWeightsIH[i][j]);
		}
	}
}

void CMLP::displayResults()
{
	// display results
	for(int i = 0;i<m_nPatterns;i++)
	{
		m_nPatNum = i;
		calcNet();
		printf("pat = %d actual = %f neural model = %f\n",m_nPatNum+1,m_pTrainOutput[m_nPatNum],m_dOutPred);
	}
}

void CMLP::calcOverallError()
{
	// calculate the overall error
	RMSerror = 0.0;
	for(int i = 0;i<m_nPatterns;i++)
	{
		m_nPatNum = i;
		calcNet();
		RMSerror = RMSerror + (m_dErrThisPat * m_dErrThisPat);
	}
	RMSerror = RMSerror/m_nPatterns;
	RMSerror = sqrt(RMSerror);
}

void CMLP::setActiveFunction(ACTIVE_LIST_ Act)
{
	// set active function
	switch(Act)
	{
	case SIGMOD:
		m_pActive.Function = f_sigmod;
		m_pActive.Derivative = dev_sigmod;
		break;
	case TANH:
		m_pActive.Function = f_tanh;
		m_pActive.Derivative = dev_tanh;
		break;
	case LINEAR:
		m_pActive.Function = f_linear;
		m_pActive.Derivative = dev_linear;
		break;
	default:
		break;
	}
}

void CMLP::learing()
{
	// seed random initialize
	srand (time(NULL));

	// initiate the weights
	initWeights();

	// train the network
	for(int j = 0;j <= m_nEpochs;j++)
	{
		for(int i = 0;i<m_nPatterns;i++)
		{
			//select a pattern at random
			m_nPatNum = rand()%m_nPatterns;

			//calculate the current network output and error for this pattern
			calcNet();

			//change network weights
			WeightChangesHO();
			WeightChangesIH();
		}

		//display the overall network error after each epoch
		calcOverallError();

		printf("epoch = %d RMS Error = %f\n",j, RMSerror);
	}
}