#include "stdafx.h"
#include "Layer.h"

CLayer::CLayer(int iSize)
{

	CNeuron *Neuron = NULL;
	
	m_iSize = iSize;
	m_Neurons.clear();
	for (int i=0;i<m_iSize;i++){
		Neuron = new CNeuron();
		m_Neurons.push_back(Neuron);
	}
	
}

CLayer::~CLayer()
{

	if (!m_Neurons.empty()){
		m_Neurons.clear();
	}

}

CNeuron* CLayer::GetNeuron(int iNeuronIndex){
	
	if (iNeuronIndex > GetNumberOfNeurons()){
		return NULL;
	}

	return (CNeuron *)m_Neurons[iNeuronIndex];

}

void CLayer::ComputeOutputs(void){
	
	CNeuron *Neuron = NULL;
	for (int i=0;i<m_Neurons.size();i++){
		Neuron = m_Neurons[i];
		Neuron->ComputeOutput();
	}

}

void CLayer::ComputeBackpropDeltas(Samples oS){
	
	CNeuron *Neuron = NULL;
	for (int i=0;i<m_Neurons.size();i++){
		Neuron = m_Neurons[i];
		Neuron->ComputeBackpropDelta(oS.samples[i]);
	}

}

void CLayer::ComputeBackpropDeltas(void){

	CNeuron *Neuron = NULL;
	for (int i=0;i<m_Neurons.size();i++){
		Neuron = m_Neurons[i];
		Neuron->ComputeBackpropDelta();
	}

}

void CLayer::ComputeWeights(void){

	CNeuron *Neuron = NULL;
	for (int i=0;i<m_Neurons.size();i++){
		Neuron = m_Neurons[i];
		Neuron->ComputeWeight();
	}

}

