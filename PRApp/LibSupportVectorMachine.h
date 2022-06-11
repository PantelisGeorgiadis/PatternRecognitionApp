#ifndef _LIBSUPPORTVECTORMACHINE_H
#define _LIBSUPPORTVECTORMACHINE_H

#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif
	
struct SVMNODE
{
	
	int iIndex;
	double dblValue;
	
};

struct SVMPROBLEM
{
	
	int l;
	double *y;
	struct SVMNODE **x;
	
};

enum { C_SVC, NU_SVC, ONE_CLASS, EPSILON_SVR, NU_SVR };	// SVM Type
enum { LINEAR, POLY, RBF, SIGMOID, PRECOMPUTED };		// Kernel Type

struct SVMPARAMETER
{
	
	int iSVMType;
	int iKernelType;
	int iDegree;			// for poly 
	double dblGamma;		// for poly/rbf/sigmoid 
	double dblCoef0;		// for poly/sigmoid 
	
	// Training
	double dblCacheSize;	// in MB 
	double dblEps;			// stopping criteria 
	double dblC;			// for C_SVC, EPSILON_SVR and NU_SVR 
	int iNRWeight;			// for C_SVC 
	int *iWeightLabel;		// for C_SVC 
	double* dblWeight;		// for C_SVC 
	double dblNU;			// for NU_SVC, ONE_CLASS, and NU_SVR 
	double dblp;			// for EPSILON_SVR 
	int iShrinking;			// use the shrinking heuristics 
	int iProbability;		// do probability estimates 
};

struct SVMMODEL *svm_train(const struct SVMPROBLEM *prob, const struct SVMPARAMETER *param);
void svm_cross_validation(const struct SVMPROBLEM *prob, const struct SVMPARAMETER *param, int nr_fold, double *target);

int svm_save_model(const char *model_file_name, const struct SVMMODEL *model);
struct SVMMODEL *svm_load_model(const char *model_file_name);

int svm_get_svm_type(const struct SVMMODEL *model);
int svm_get_nr_class(const struct SVMMODEL *model);
void svm_get_labels(const struct SVMMODEL *model, int *label);
double svm_get_svr_probability(const struct SVMMODEL *model);

void svm_predict_values(const struct SVMMODEL *model, const struct SVMNODE *x, double* dec_values);
double svm_predict(const struct SVMMODEL *model, const struct SVMNODE *x);
double svm_predict_probability(const struct SVMMODEL *model, const struct SVMNODE *x, double* prob_estimates);

void svm_destroy_model(struct SVMMODEL *model);
void svm_destroy_param(struct SVMPARAMETER *param);

const char *svm_check_parameter(const struct SVMPROBLEM *prob, const struct SVMPARAMETER *param);
int svm_check_probability_model(const struct SVMMODEL *model);
	
#ifdef __cplusplus
}
#endif

#endif 
