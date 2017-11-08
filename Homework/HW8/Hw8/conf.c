/*
 * This program is for one of the problems in Homework 8, EE 367
 * To compile gcc conf.c -lm
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define N 100 

main()
{
int i, j, k;
double mean;
double randnum[N];  /* Size of the array of random values */
double variance;
double stddev;

/* Initialize array with random values */
srand48(1);
for (i=0; i<N; i++) {
   randnum[i] = exp(drand48());
}

/* Print the array of values */
for (i=0; i<N; i++) {
   printf("random number %d = %f\n",i,randnum[i]);
}

/* Compute sample mean */
mean = 0.0;
for (i=0; i<N; i++) {
   mean += randnum[i];
}
mean = mean/((double) N);
printf("\nEstimated mean = %f\n",mean);

/* Compute unbiased estimate of variance */
variance = 0.0;
for (i=0; i<N; i++) {
   variance += (randnum[i]-mean)*(randnum[i]-mean);
}
variance = variance /((double) (N-1));
variance = variance /((double) (N));
stddev = sqrt(variance);

printf("\nEstimated variance= %f\n",variance);
printf("\nEstimated std dev= %f\n",stddev);

printf("\n90 Conf interval = [%f, %f]\n", mean-stddev*1.645,mean+stddev*1.645);
printf("\n95 Conf interval = [%f, %f]\n", mean-stddev*1.96, mean+stddev*1.96);
printf("\n99 Conf interval = [%f, %f]\n", mean-stddev*2.575, mean+stddev*2.575);
}




