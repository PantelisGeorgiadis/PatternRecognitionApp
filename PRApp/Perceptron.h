#if !defined(AFX_PERCEPTRON_H__76D39C8A_525A_45B6_98B1_3B5DCCCE36E2__INCLUDED_)
#define AFX_PERCEPTRON_H__76D39C8A_525A_45B6_98B1_3B5DCCCE36E2__INCLUDED_

#ifndef __GNUC__
#pragma warning(disable : 4786)
#endif

#include "Layer.h"
#include "Synapse.h"
#include "Neuron.h"
#include <vector>

class CPerceptron  
{
public:
	CPerceptron(int i, int o)
	{
		
		m_Layers.clear();
		m_InputSamples.clear(); // !!!!
		m_OutputSamples.clear(); // !!!!
		m_InputLayer = new CLayer(i + 1); // plus the bias
		m_OutputLayer = new CLayer(o);
		m_Layers.push_back(m_InputLayer);
		m_Layers.push_back(m_OutputLayer);
		m_dblError = 0.0;

	}

	virtual ~CPerceptron();

	void AddLayer(int n);
	CLayer* GetLayer(int iLayerIndex);
	int GetNumberOfLayers (void) { return m_Layers.size(); }
	void Connect(int iSourceLayer, int iSourceNeuron, int iDestLayer, int iDestNeuron, double dblWeight);
	void BiasConnect(int iDestLayer, int iDestNeuron, double dblWeight);
	void Propagate(void);

	void removeSamples()
	{
		m_InputSamples.clear();
		m_InputSamples.clear();
	}
	void addSample(Samples inputs,Samples outputs)
	{
//		ASSERT( (inputs.nLenght > 0) && (outputs.nLenght > 0) );
//		ASSERT( (inputs.samples) && (outputs.samples) );
		m_InputSamples.push_back(inputs);
		m_OutputSamples.push_back(outputs);
	}

	void InitInputs(Samples iS)
	{
		/*POSITION pos = inputLayer->neurons.GetHeadPosition();
		Neuron* neuron = (Neuron*)inputLayer->neurons.GetAt(pos);
		for (int i = 0; i < iS.nLenght; i++) 
		{
			neuron = (Neuron*)inputLayer->neurons.GetNext(pos);
			neuron->output = iS.samples[i];
		}
		neuron = (Neuron*)inputLayer->neurons.GetNext(pos);// bias;
		neuron->output = 1.0;*/

		CNeuron *Neuron = NULL;
		int iCount = 0;
		for (int i=0;i<iS.nLenght;i++){
			Neuron = m_InputLayer->m_Neurons[i];
			Neuron->SetOutput(iS.samples[i]);
			iCount++;
		}

        iCount++;

		Neuron = m_InputLayer->m_Neurons[iCount]; // Bias
		Neuron->SetOutput(1.0f);
	}

	Samples GetOutput()
	{
		
		CNeuron *Neuron = NULL;
		Samples oS = {0, m_OutputLayer->m_Neurons.size()};

		for (int i=0;i<m_OutputLayer->m_Neurons.size();i++){
			Neuron = m_OutputLayer->m_Neurons[i];
			oS.samples[i] = Neuron->GetOutput();
		}

		return oS;

	}

	double ComputeError(Samples oS)
	{
		
		double dblSum = 0.0f;
		double dblTmp;
		CNeuron *Neuron = NULL;

		for (int i=0;i<m_OutputLayer->m_Neurons.size();i++){
			Neuron = m_OutputLayer->m_Neurons[i];
			dblTmp = oS.samples[i] - Neuron->GetOutput();
			dblSum += dblTmp * dblTmp;
		}

		return dblSum;

	}
	
	double GetCurrentError(){
		
		return m_dblError;

	}

	void bpAdjustWeights(Samples oS)
	{
		
		/*m_OutputLayer->computeBackpropDeltas(oS);
		
		POSITION pos = layers.GetHeadPosition();
		
		for(int i=m_Layers.size() - 2;i>=1;i--)
		{
			layers.GetNext(pos);
			((Layer*)layers.GetAt(pos))->computeBackpropDeltas();
		}
		outputLayer->computeWeights();
		pos = layers.GetHeadPosition();
		for(int i=layers.GetCount()-2; i>=1; i--)
		{
			layers.GetNext(pos);
			((Layer*)layers.GetAt(pos))->computeWeights();
		}*/
	}

	Samples Recognize(Samples iS)
	{
		InitInputs(iS);
		Propagate();
		Samples oS = GetOutput();
		return oS;
	}

	void Learn(int iIterations)
	{
		
		int i = 0, j = 0;
		Samples Pattern;
		Samples Target;
		
		for(i=0;i<iIterations;i++){
			// accumulate total error over each epoch
			m_dblError = 0.0;
			for (j=0;j<m_InputSamples.size();j++){			
				Pattern = m_InputSamples[j];
				Target = m_OutputSamples[j];
				LearnPattern(Pattern, Target);
				m_dblError += ComputeError(Target);
			}
			m_dblError /= (m_InputSamples.size() * m_OutputLayer->m_Neurons.size());
			m_dblError = sqrt(m_dblError);
		}
	}
	
	void LearnPattern(Samples iS, Samples oS)
	{
		InitInputs(iS);
		Propagate();
		bpAdjustWeights(oS);
	}





protected:

	std::vector<CLayer*> m_Layers;
	CLayer *m_InputLayer;
	CLayer *m_OutputLayer;

	std::vector<Samples>	m_InputSamples;	//Samples are array of double
	std::vector<Samples>	m_OutputSamples;

	double	m_dblError;


};

#endif 
