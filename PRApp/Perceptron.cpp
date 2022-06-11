#include "stdafx.h"
#include "Perceptron.h"

CPerceptron::~CPerceptron()
{

	if (!m_Layers.empty()){
		m_Layers.clear();
	}

}

void CPerceptron::AddLayer(int n){

	std::vector<CLayer*>::iterator it = m_Layers.end() - 1;	
	CLayer* Layer = new CLayer(n);
	m_Layers.insert(it, Layer);

}

CLayer* CPerceptron::GetLayer(int iLayerIndex){

	if (iLayerIndex > GetNumberOfLayers()){
		return NULL;
	}

	return (CLayer *)m_Layers[iLayerIndex];

}

void CPerceptron::Connect(int iSourceLayer, int iSourceNeuron, int iDestLayer, int iDestNeuron, double dblWeight){
		
	new CSynapse(GetLayer(iSourceLayer)->GetNeuron(iSourceNeuron), GetLayer(iDestLayer)->GetNeuron(iDestNeuron), dblWeight);

}

void CPerceptron::BiasConnect(int iDestLayer, int iDestNeuron, double dblWeight){

	new CSynapse(m_InputLayer->GetNeuron(m_InputLayer->GetSize() - 1), GetLayer(iDestLayer)->GetNeuron(iDestNeuron), dblWeight);

}

void CPerceptron::Propagate(void){
	
	CLayer *Layer = NULL;
	for (int i=1;i<m_Layers.size();i++){ // skip the input layer
		Layer = m_Layers[i];
		Layer->ComputeOutputs();
	}

}
