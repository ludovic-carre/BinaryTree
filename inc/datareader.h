#ifndef DATAREADER_H
#define DATAREADER_H

#include <stdlib.h>
#include <stdint.h>
#include "tree.h"

typedef struct {
	double* proba;
	double* proba_sums;
	uint32_t length;
} probabilities;

probabilities* getprobaarray(double* value_array,uint32_t length,double total_value);

probabilities* getproba(FILE*,uint32_t length);

void disparray(double* proba,uint32_t length);

void treetoarray(Tree* tree,uint32_t length);

void printtree(int32_t length);

void nodetoarray(Node* root);

void free_array(probabilities* array);

#endif
