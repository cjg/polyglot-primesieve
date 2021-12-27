#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int countPrimes(int n) {
	char *primeNumbers = malloc(n);
	int i, j, c;
	for (i = 0; i < n; i++) {
		primeNumbers[i] = 1;
	}
	primeNumbers[0] = 0;
	primeNumbers[1] = 0;
	int last = (int) sqrt((double) n);
	for (i = 2; i < last; i++) {
		if (!primeNumbers[i]) {
			continue;
		}
		for (j = i * 2; j < n; j += i) {
			primeNumbers[j] = 0;
		}
	}
	c = 0;
	for (i = 0; i < n; i++) {
		if (primeNumbers[i]) {
			c++;
		}
	}
	free(primeNumbers);
	return c;
}

int main() {
	int i, n;
	clock_t start, end;
	double min, max, total, avg;
	double *durations = malloc(sizeof(double) * 100);
	
	for (i = 0; i < 100; i++) {	
		start = clock();
		n = countPrimes(1000000);
		end = clock();
		if (n != 78498) {
			fprintf(stderr, "found %d instead of 78498 prime numbers\n", n);
			return -1;
		}
		durations[i] = ((double) (end - start)) / (CLOCKS_PER_SEC / 1000.0);
		printf("Iteration %3d completed in %0.2lfms\n", i, durations[i]);
	}

	max = durations[0];
	min = durations[0];
	total = durations[0];
	for (i = 1; i < 100; i++) {
		if (durations[i] < min) {
			min = durations[i];
		}

		if (durations[i] > max) {
			max = durations[i];
		}

		total += durations[i];
	}
	avg = total / 100.0;
	free(durations);
	printf("%d iterations completed in %0.2lfs, min: %0.2lfms max: %0.2lfms average: %0.2lfms\n",
			100, total / 1000, min, max, avg);
}
