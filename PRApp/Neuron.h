#if !defined(AFX_NEURON_H__2B0AD0ED_F894_4E37_BD3C_CB83CF992AAB__INCLUDED_)
#define AFX_NEURON_H__2B0AD0ED_F894_4E37_BD3C_CB83CF992AAB__INCLUDED_

#ifndef __GNUC__
#pragma warning(disable : 4786)
#endif

#include <vector>
#include <cmath>

class CSynapse;

class CNeuron  
{
public:
	CNeuron()
	{

		m_dblOutput = 0.0f;
		m_dblDelta = 0.0f;
		m_dblSum = 0.0f;
		m_InLinks.clear();
		m_OutLinks.clear();

	}
	virtual ~CNeuron();

	void SetOutput(double dblOutput) { m_dblOutput = dblOutput; }
	double GetOutput(void) { return m_dblOutput; }
	double GetDelta(void) { return m_dblDelta; }

	void ComputeOutput();
	void ComputeBackpropDelta(double d);	// for an output neuron
	void ComputeBackpropDelta();			// for a hidden neuron
	void ComputeWeight();
	void SetWeights(double* pWeights);
	

	std::vector<CSynapse*> m_InLinks;
	std::vector<CSynapse*> m_OutLinks;

protected:

	static double m_dblMomentum;			// = 0.9;
	static double m_dblLearningRate;		// = 0.05;

	double m_dblOutput;						// range from 0.0 to 1.0
	double m_dblSum;
	double m_dblDelta;

	double SigmoidFunction (double d);

};

#endif 
