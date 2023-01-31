#pragma once
#include <stdlib.h>

int randInRange(int min, int max)
{
	return min + (int)(rand() / (double)(RAND_MAX + 1) * (max - min + 1));
}

double randZeroToOne() {
	return (rand() / (double) RAND_MAX);
}

double randInDoubleRange(double min, double max) {
	return min + (rand() / (double)RAND_MAX * (max - min));
}