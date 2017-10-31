/**
 *  @file ZC_DataProperty.h
 *  @author Sheng Di
 *  @date July, 2016
 *  @brief Header file for the ZC_CompareData.c.
 *  (C) 2016 by Mathematics and Computer Science (MCS), Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

#ifndef _ZC_DataProperty_H
#define _ZC_DataProperty_H

#ifdef __cplusplus
extern "C" {
#endif

struct HashEntry_s{
	int flag;
    unsigned long key;
	int num;
};

typedef struct HashEntry_s HashEntry;

typedef double real;
typedef struct{real Re; real Im; real Amp;} complex;

typedef struct ZC_DataProperty
{
	char* varName;
	int dataType; /*ZC_DOUBLE or ZC_FLOAT*/
	size_t r5;
	size_t r4;
	size_t r3;
	size_t r2;
	size_t r1;
	
	void *data;
	
	long numOfElem;
	double minValue;
	double maxValue;
	double valueRange;
	double avgValue;
	double entropy;
	double zeromean_variance;
	double* autocorr; /*array of autocorrelation coefficients*/
	complex* fftCoeff; /*array of fft coefficients*/
	double* lap;
} ZC_DataProperty;

void hash_init(HashEntry *table, size_t table_size);
size_t hash_get(HashEntry *table, unsigned long key, size_t table_size);
void hash_put(HashEntry *table, unsigned long key, size_t table_size);

void fft(complex *v, size_t n, complex *tmp);
void ifft(complex *v, size_t n, complex *tmp);

void computeLap(double *data, double *lap, size_t r5, size_t r4, size_t r3, size_t r2, size_t r1);

void freeDataProperty(ZC_DataProperty* dataProperty);
ZC_DataProperty* ZC_constructDataProperty(char* varName, int dataType, size_t r5, size_t r4, size_t r3, size_t r2, size_t r1, 
size_t numOfElem, double minValue, double maxValue, double valueRange, double avgValue, 
double entropy, double* autocorr, complex* fftCoeff);

complex* ZC_computeFFT(void* data, size_t n, int dataType);
ZC_DataProperty* ZC_genProperties_float(char* varName, float *data, size_t numOfElem, size_t r5, size_t r4, size_t r3, size_t r2, size_t r1);
ZC_DataProperty* ZC_genProperties_double(char* varName, double *data, size_t numOfElem, size_t r5, size_t r4, size_t r3, size_t r2, size_t r1);
ZC_DataProperty* ZC_genProperties(char* varName, int dataType, void *oriData, size_t r5, size_t r4, size_t r3, size_t r2, size_t r1);
void ZC_printDataProperty(ZC_DataProperty* property);
char** constructDataPropertyString(ZC_DataProperty* property);

void ZC_writeFFTResults(char* varName, complex* fftCoeff, char* tgtWorkspaceDir);
void ZC_writeDataProperty(ZC_DataProperty* property, char* tgtWorkspaceDir);
ZC_DataProperty* ZC_loadDataProperty(char* propResultFile);

#ifdef HAVE_MPI
ZC_DataProperty* ZC_genProperties_float_online(char* varName, float *data, size_t numOfElem, size_t r5, size_t r4, size_t r3, size_t r2, size_t r1);
ZC_DataProperty* ZC_genProperties_double_online(char* varName, double *data, size_t numOfElem, size_t r5, size_t r4, size_t r3, size_t r2, size_t r1);
#endif

#ifdef __cplusplus
}
#endif

#endif /* ----- #ifndef _ZC_DataProperty_H  ----- */
