#if !defined(AFX_SYNAPSE_H__B1A9813F_25CD_421A_86A6_498CD7FD79A3__INCLUDED_)
#define AFX_SYNAPSE_H__B1A9813F_25CD_421A_86A6_498CD7FD79A3__INCLUDED_

#include "Neuron.h"
class CSynapse;

class CSynapse  
{
public:
	CSynapse();
	virtual ~CSynapse();

	CSynapse (CNeuron* pNeuronFrom, CNeuron* pNeuronTo, double dblWeight)
	{

		m_pNeuronFrom = pNeuronFrom;
		m_pNeuronTo = pNeuronTo;
		m_dblWeight = dblWeight;
		m_dblData = 0.0f;
		pNeuronFrom->m_OutLinks.push_back(this);
		pNeuronTo->m_InLinks.push_back(this);

	}

	double GetWeight(void){ return m_dblWeight; }
	void SetWeight(double dblWeight){ m_dblWeight = dblWeight; }
	double GetData(void){ return m_dblData; }
	void SetData(double dblData){ m_dblData = dblData; }
	CNeuron* GetNeuronFrom (void) { return m_pNeuronFrom; }
	CNeuron* GetNeuronTo (void) { return m_pNeuronTo; }

protected:

	double m_dblWeight;				//weight between "to" and "from" neurons
	double m_dblData;
	CNeuron* m_pNeuronFrom;
	CNeuron* m_pNeuronTo;

};

#endif 
