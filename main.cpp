//main.cpp

#include "ECMINERMLP.h"

#include <iostream>

int main(int arg, char* argv)
{
	FILE *fp = NULL;

	// File Read - XData
	int nXVar = 0;
	int nXSize = 0;

	fp = fopen("XDataSet.txt", "r");
	if (!fp)
		return 1;

	fscanf(fp, "%d %d", &nXSize, &nXVar);

	Matrix mXData;
	mXData.ReSize(nXSize,nXVar);

	double fvalX = 0.;
	for (int iRowCnt = 1; iRowCnt<=nXSize; iRowCnt++)
	{
		for (int iColCnt = 1; iColCnt<=nXVar; iColCnt++)
		{
			fscanf(fp, "%lf", &fvalX);
			mXData(iRowCnt, iColCnt) = fvalX;
		}
	}
	fclose(fp);

	// File Read - XData
	int nYVar = 0;
	int nYSize = 0;

	fp = fopen("YDataSet.txt", "r");
	if (!fp)
		return 1;

	fscanf(fp, "%d %d", &nYSize, &nYVar);

	Matrix mYData;
	mYData.ReSize(nYSize,nYVar);

	double fvalY = 0.;
	for (int iRowCnt = 1; iRowCnt<=nYSize; iRowCnt++)
	{
		for (int iColCnt = 1; iColCnt<=nYVar; iColCnt++)
		{
			fscanf(fp, "%lf", &fvalY);
			mYData(iRowCnt, iColCnt) = fvalY;
		}
	}
	fclose(fp);

	CLayer Layer1;
	CMultilayer CMLayer;

	CMLayer.pushLayer(&Layer1);
	CMLayer.setTrainingSets(mXData, mYData);
	
	CPerceptron Perceptron;
	Perceptron.setActiveFunc(SIGMOD);
	Perceptron.setSolver(SGD);
	Perceptron.setCondition(0.0001, 10000000);
	Perceptron.setLearningRate(0.1);
	Perceptron.m_vMultilayer.push_back(CMLayer);
	Perceptron.Learning();

#if _DEBUG
	std::cout << "Enter to continue..." << std::endl;
	std::cin.get();
#endif
	return 0;
}