#include "stdafx.h"
#include "Neuron.h"
#include "Synapse.h"

double CNeuron::m_dblMomentum = 0.9;
double CNeuron::m_dblLearningRate = 0.05;

CNeuron::~CNeuron()
{

	if (!m_InLinks.empty()){
		m_InLinks.clear();
	}
	if (!m_OutLinks.empty()){
		m_OutLinks.clear();
	}

}

void CNeuron::ComputeOutput(void){
	
	m_dblSum = 0.0;
	CSynapse *Synapse = NULL;
	for (int i=0;i<m_InLinks.size();i++){
		Synapse = m_InLinks[i];
		m_dblSum += Synapse->GetNeuronFrom()->GetOutput() * Synapse->GetWeight();
	}
	
	m_dblOutput = SigmoidFunction(m_dblSum);

}

void CNeuron::ComputeBackpropDelta (double d){ // for an output neuron
	
	m_dblDelta = (d - m_dblOutput) * m_dblOutput * (1.0f - m_dblOutput);

}

void CNeuron::ComputeBackpropDelta(void){
	
	double dblErrorSum = 0.0f;
	CSynapse *Synapse = NULL;
	for (int i=0;i<m_OutLinks.size();i++){
		Synapse = m_OutLinks[i];
		dblErrorSum += Synapse->GetNeuronTo()->GetDelta() * Synapse->GetWeight();
	}
	
	m_dblDelta = m_dblOutput * (1.0 - m_dblOutput) * dblErrorSum;

}

void CNeuron::ComputeWeight (void){

	CSynapse *Synapse = NULL;
	for (int i=0;i<m_InLinks.size();i++){
		Synapse = m_InLinks[i];
		Synapse->SetData(m_dblLearningRate * m_dblDelta * Synapse->GetNeuronFrom()->GetOutput() + m_dblMomentum * Synapse->GetData());
		Synapse->SetWeight(Synapse->GetWeight() + Synapse->GetData());
	}
}

void CNeuron::SetWeights (double* pdblWeights){

	CSynapse* Synapse = NULL;
	for (int i=0;i<m_OutLinks.size();i++){
		Synapse = m_OutLinks[i];
		Synapse->SetWeight(pdblWeights[i]);
	}

}

double CNeuron::SigmoidFunction (double d){

	return 1.0 / (1.0 + exp(-d));

}
