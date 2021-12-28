#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define mask(x) (((uint32_t)1) << (x % 32))
#define is_set(b, x) (!(b[x / 32] & mask(x)))
#define unset(b, x) b[x / 32] |= mask(x)

uint32_t *bitmap = NULL;

int countPrimes(int n)
{
	int bitmap_size = n / 32;
	if (bitmap_size * 32 < n) {
		bitmap_size += 1;
	}
	if (bitmap == NULL) {
		bitmap = calloc(bitmap_size, sizeof(uint32_t));
	} else {
		memset(bitmap, 0, bitmap_size * sizeof(uint32_t));
	}
	int i, j, c;
	unset(bitmap, 0);
	unset(bitmap, 1);
	
	int last = (int)sqrt((double)n);
	for (i = 2; i < last; i++) {
		if (!is_set(bitmap, i)) {
			continue;
		}
		for (j = i * 2; j < n; j += i) {
			unset(bitmap, j);
		}
	}
	c = 0;
	for (i = 0; i < n; i++) {
		if (is_set(bitmap, i)) {
			c++;
		}
	}
	//free(bitmap);
	return c;
}

int main()
{
	int i, n;
	clock_t start, end;
	double min, max, total, avg;
	double *durations = malloc(sizeof(double) * 100);

	for (i = 0; i < 100; i++) {
		start = clock();
		n = countPrimes(10000000);
		end = clock();
		if (n != 664579) {
			fprintf(stderr,
				"found %d instead of 78498 prime numbers\n", n);
			return -1;
		}
		durations[i] =
		    ((double)(end - start)) / (CLOCKS_PER_SEC / 1000.0);
		printf("Iteration %3d completed in %0.2lfms\n", i,
		       durations[i]);
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
	printf
	    ("%d iterations completed in %0.2lfs, min: %0.2lfms max: %0.2lfms average: %0.2lfms\n",
	     100, total / 1000, min, max, avg);
}
