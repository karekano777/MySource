// main.cpp

#include <iostream>

#include "Matrix.h"
#include "MLP.h"

int main(int arg, char* argv)
{
	CMLP MLP;

	// setting
	MLP.m_nInputs = 3;
	MLP.m_nPatterns = 4;
	MLP.m_nHidden = 4;
	MLP.m_nEpochs = 500;
	MLP.LR_IH = 0.7;
	MLP.LR_HO = 0.07;

	// set hidden layer active_function
	MLP.setActiveFunction(TANH);

	//  generate matrix
	MLP.genDataMatrix();
	MLP.genHiddenValVector();
	MLP.genWightsMatrix();

	// read in the data
	// TrainSet1
	MLP.m_pTrainInputs[0][0]  = 1.;
	MLP.m_pTrainInputs[0][1]  = -1.;
	MLP.m_pTrainInputs[0][2]  = 1.; //bias
	MLP.m_pTrainOutput[0] = 1.;

	// TrainSet2
	MLP.m_pTrainInputs[1][0]  = -1.;
	MLP.m_pTrainInputs[1][1]  = 1.;
	MLP.m_pTrainInputs[1][2]  = 1.; //bias
	MLP.m_pTrainOutput[1] = 1.;
	
	// TrainSet3
	MLP.m_pTrainInputs[2][0]  = 1.;
	MLP.m_pTrainInputs[2][1]  = 1.;
	MLP.m_pTrainInputs[2][2]  = 1.; //bias
	MLP.m_pTrainOutput[2] = -1.;

	// TrainSet4
	MLP.m_pTrainInputs[3][0]  = -1.;
	MLP.m_pTrainInputs[3][1]  = -1.;
	MLP.m_pTrainInputs[3][2]  = 1.; //bias
	MLP.m_pTrainOutput[3] = -1.;

	// training
	MLP.learing();

	//training has finished display the results
	MLP.displayResults();

#if _DEBUG
	std::cout << "Enter to continue..." << std::endl;
	std::cin.get();
#endif
	return 0;
}