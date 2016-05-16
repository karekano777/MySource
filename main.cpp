<<<<<<< HEAD
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

	CLayer Layer1(3,3);
	CLayer Layer2(3,2);
	CLayer Layer3(2,4);
	CLayer Layer4(4,1);
	CLayer Layer5(1,3);
	CLayer Layer6(3,2);
	CLayer Layer7(2,4);
	CMultilayer CMLayer;

	CMLayer.pushLayer(&Layer1);
	CMLayer.pushLayer(&Layer2);
	CMLayer.pushLayer(&Layer3);
	CMLayer.pushLayer(&Layer4);
	CMLayer.pushLayer(&Layer5);
	CMLayer.pushLayer(&Layer6);
	CMLayer.pushLayer(&Layer7);

	CMLayer.setTrainingSets(mXData, mYData);
	
	CPerceptron Perceptron;
	Perceptron.setActiveFunc(SIGMOD);
	Perceptron.setSolver(SGD);
	Perceptron.setCondition(pow(10.,-10), 50000);
	Perceptron.setLearningRate(0.5);
	Perceptron.m_vMultilayer.push_back(CMLayer);
	Perceptron.Learning();

#if _DEBUG
	std::cout << "Enter to continue..." << std::endl;
	std::cin.get();
#endif
	return 0;
=======
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

	CLayer Layer1(3,3);
	CLayer Layer2(3,3);
	CLayer Layer3(3,3);
	CLayer Layer4(3,1);
	CLayer Layer5(1,3);
	CLayer Layer6(3,2);
	CLayer Layer7(2,4);
	CMultilayer CMLayer;

	CMLayer.pushLayer(&Layer1);
	CMLayer.pushLayer(&Layer2);
	CMLayer.pushLayer(&Layer3);
	CMLayer.pushLayer(&Layer4);
	CMLayer.pushLayer(&Layer5);
	CMLayer.pushLayer(&Layer6);
	CMLayer.pushLayer(&Layer7);

	CMLayer.setTrainingSets(mXData, mYData);
	
	CPerceptron Perceptron;
	Perceptron.setActiveFunc(SIGMOD);
	Perceptron.setSolver(SGD);
	Perceptron.setCondition(0.00001, 50000);
	Perceptron.setLearningRate(0.5);
	Perceptron.m_vMultilayer.push_back(CMLayer);
	Perceptron.Learning();

#if _DEBUG
	std::cout << "Enter to continue..." << std::endl;
	std::cin.get();
#endif
	return 0;
>>>>>>> origin/master
}