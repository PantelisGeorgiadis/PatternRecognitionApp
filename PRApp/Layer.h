#if !defined(AFX_LAYER_H__6E2BB533_A8AB_4B99_BF61_8F7737A15300__INCLUDED_)
#define AFX_LAYER_H__6E2BB533_A8AB_4B99_BF61_8F7737A15300__INCLUDED_

#ifndef __GNUC__
#pragma warning(disable : 4786)
#endif

#include "Neuron.h"
#include <vector>

static const int LEN = 100;
struct Samples
{
	double samples[LEN];
	int nLenght;
};

class CLayer  
{
public:
	CLayer(int iSize);
	virtual ~CLayer();

	std::vector<CNeuron*> m_Neurons;

	CNeuron* GetNeuron(int iNeuronIndex);
	void ComputeOutputs(void);
	void ComputeBackpropDeltas(Samples s);		// for output neurons
	void ComputeBackpropDeltas(void);			// for hidden neurons
	void ComputeWeights(void);
	int GetNumberOfNeurons (void) { return m_Neurons.size(); }
	int GetSize(void) { return m_iSize; }

protected:

	int m_iSize;

};

#endif 
