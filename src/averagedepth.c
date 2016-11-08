#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "../inc/averagedepth.h"


double* proba = NULL;
double* proba_sums = NULL;
double** depth_array = NULL;
uint32_t call_count = 0;

double proba_sum(uint32_t low_index,uint32_t high_index){
	double sum = 0;
	for(uint32_t i=low_index;i<high_index;i++)
		sum += proba[i];
	return sum;
}

double avgdepth(uint32_t low_index,uint32_t high_index){
	if(high_index-low_index <= 1)
		return high_index-low_index;

	/* We have to check if value is very close to 0, can't compare floats to 0.0 */
	if(fabs(depth_array[low_index][high_index-1]) > 10e-7)
		return depth_array[low_index][high_index-1];

	call_count += 1;
	double lower, higher, total;
	double min_result, new_result;
	total = proba_sum(low_index,high_index);
	lower = 0.0;
	higher = avgdepth(low_index+1,high_index) * proba_sum(low_index+1,high_index) / total;

	min_result = 1 + lower + higher;
	for(uint32_t i=low_index+1;i<high_index;i++){
		lower = avgdepth(low_index,i) * proba_sum(low_index,i) / total;
		higher = avgdepth(i+1,high_index) * proba_sum(i+1,high_index) / total;
		new_result = 1 + lower + higher;
		if(min_result > new_result)
			min_result = new_result;
	}
	depth_array[low_index][high_index-1] = min_result;
	return min_result;
}

double getavg(double* proba_array,double* proba_sum_array,uint32_t length){
	double min_depth;
	proba = proba_array;
	proba_sums = proba_sum_array;
	depth_array = malloc(length*sizeof(double*));
	for(uint32_t i=0;i<length;i++)
		depth_array[i] = calloc(length,sizeof(double));

	min_depth = avgdepth(0,length);
	for(uint32_t i=1;i<length;i++)
		free(depth_array[i]);
	free(depth_array);
	printf("Unique call count: %u\n",call_count);
	return min_depth;
}
