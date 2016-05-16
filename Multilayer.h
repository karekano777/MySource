// Multilayer.h
#pragma once

#ifndef MILTILAYER_H
#define MILTILAYER_H 0 

#include "Matrix.h"
#include "Layer.h"

#include <vector>

class CMultilayer
{
public:
	CMultilayer(void);
	~CMultilayer(void);

public:
	void pushLayer(CLayer* Layer)
	{ 
		m_vLayer.push_back(Layer);
		iter++;
	}

	CLayer* getLayer()
	{
		if ((iter>=0) && (iter<(int)m_vLayer.size()))
		{
			return m_vLayer[iter];
		}
		return NULL;
	}

	void updateLayer(CLayer* Layer, int i) { 
		m_vLayer[i-1] = Layer;
	}

	void setTrainingSets(Matrix X, Matrix Y)
	{
		m_matSetX = X;
		m_matSetY = Y;
	}

	void updateTrainingData(int i)
	{
		for (int iLayer=0; iLayer<(int)m_vLayer.size(); iLayer++)
		{
			CLayer* layer = m_vLayer[iLayer];

			if (iLayer == 0)
				layer->setInputVector(m_matSetX.Column(i));

			layer->setTargetVector(m_matSetY.Column(i));
			m_vLayer[iLayer] = layer;
		}
	}

	bool gotoFirstLayer()
	{
		if (iter>-1)
		{
			iter = 0;
			return true;
		}
		else
			return false;
	}

	bool gotoEndLayer()
	{
		if (iter>-1)
		{
			iter = m_vLayer.size()-1;
			return true;
		}
		else 
		{
			return false;
		}
	}

	bool preLayer()
	{
		if ((iter>-1) && (iter != 0))
		{
			iter--;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool nextLayer()
	{
		if ((iter>-1) && (iter < (int)m_vLayer.size()))
		{
			iter++;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool isFirstLayer() { return (iter==-1)? true : false; }
	bool isEndLayer() { return (iter==m_vLayer.size())? true : false; }

	int getTrainingNumber() { return min(m_matSetX.Ncols(), m_matSetY.Ncols()); }
	int getLayerNumber() { return m_vLayer.size(); }

	int getiLayer() { return iter; }
	std::vector<CLayer*> m_vLayer;

private:

	Matrix m_matSetX;
	Matrix m_matSetY;

	int iter;
};

#endif //MILTILAYER_H