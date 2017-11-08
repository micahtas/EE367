/*
 * EE 367 University of Hawaii - G. Sasaki
 *
 * This program will measure the time it takes insert sort to
 * sort a collection of random integers in an array.
 * The random values are from a random number generator.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>  /* This has clock(), clock_gettime(); compile with -lrt */
#include <math.h>  /* If you use functions from this, compile with "-lm" */

/* Set CLOCK 1 to use clock() and set to 0 to use clockgettime */
#define CLOCK 0 

#define MAXARRAY 100000  /* Maximum array size */
#define NUMITER 11       /* Number of iterations */

struct perfdata { /* Performance data per run */
   double delay;  /* Measured delay of the run */
   int    asize;  /* Size of the array during the run */
};

int randnum(int n); /* Returns a random number ranging from 0 to n-1 */
int randarray(int a[], int asize, int n); /* Inserts random numbers in array a[] */
void insertsort(int a[], int asize); /* Insertion sort */
   /* Next function returns difference in time in seconds */
double diff(struct timespec * start, struct timespec * end); 
int checksorted(int a[], int asize); /* Checks if array is sorted. Unused right now */

main()
{

struct perfdata data[NUMITER]; /* Performance data per array size */

int a[MAXARRAY];  /* Array with the numbers to sort */
int asize;        /* Size of the array.  It can be at most MAXARRAY. */
int i, k, j;
double ratio;

#if CLOCK == 1
   clock_t start_clock, end_clock;
   double delay_clock;
#else
   struct timespec start_get, end_get;
   double delay_get;
#endif


srand48(1);       /* This will seed the random number generator with */
                  /* the value 1.  This value is chosen arbitrarily */
for (j=0; j<2; j++) {
   asize = 64;
   for (i=0; i<NUMITER; i++) {
      randarray(a, asize, asize); /* Initialize array with random numbers */ 

      #if CLOCK == 1
         start_clock = clock();
         insertsort(a, asize);
         end_clock = clock();
      #else
         clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_get);
         insertsort(a, asize);
         clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_get);
      #endif

      #if CLOCK == 1
         /*  Record data on 2nd pass through the for-loop, i.e., when j > 0 */
         delay_clock = (end_clock - start_clock)/((double) CLOCKS_PER_SEC);
         if (j > 0) {
            data[i].delay = delay_clock;
            data[i].asize = asize;
         }
      #else
         delay_get = diff(&start_get, &end_get);
         if (j > 0) {
            data[i].delay = delay_get;
            data[i].asize = asize;
         }
      #endif
   asize *= 2;
   }
}

/* Display measured results */
for (i=0; i<NUMITER; i++) {
   #if CLOCK == 1
      printf("clock(): ");
   #else
      printf("clock_gettime(): ");
   #endif
   printf("asize=%d Delay=%f(sec)\n",data[i].asize, data[i].delay);
}

for (i=0; i<NUMITER-1; i++) {
  ratio = data[i+1].delay/data[i].delay;
  printf("Ratio[%d/%d] = %f\n",data[i+1].asize,data[i].asize,log(ratio)/log(2.0));
}

}


int checksorted(int a[], int asize)
/*
 * This can be used to check if an array is sorted.
 */
{
int i;

if (asize <= 0) return 1; /* Array is small so it's sorted */

for (i=0; i<asize-1; i++) {
   if (a[i] > a[i+1]) {
      printf("checksorted:  array is unsorted i = %d\n", i);
      return 0;
   }
}
return 1;
}

double diff(struct timespec * start, struct timespec * end) 
/*
 *  Returns the difference times (end - start) in seconds.
 */
{
struct timespec temp;
double ns;

if ((end->tv_nsec - start->tv_nsec) < 0) {
   temp.tv_sec = end->tv_sec - start->tv_sec - 1;
   temp.tv_nsec = 1000000000 + end->tv_nsec - start->tv_nsec;
} 
else {
   temp.tv_sec = end->tv_sec - start->tv_sec;
   temp.tv_nsec = end->tv_nsec - start->tv_nsec;
}

ns = temp.tv_sec; 
ns *= 1000000000.0;
ns += temp.tv_nsec;

return ns/1000000000.0;
}

void insertsort(int a[], int asize) 
/*
 * This is insertion sort.  It follows the lecture notes with
 * some modifications
 */
{
int key;
int i, k;

if (asize <= 1) return; /* Array is too small to sort */
for (k = 1; k < asize; k++) {
   key = a[k];   /* k is the border between the sorted subarray (on the left)
                    and the unsorted subarray (on the right).  We want to
                    shift values in the left subarray so we can insert the
                    key value into sorted position */
   i=k;
   while (i>0) { /* Keep shifting until i points to insertion point */
      if (a[i-1] > key) {
         a[i] = a[i-1];
         i--;
      }
      else break;
   }
   a[i] = key;
}
}

int randnum(int n)
/* 
 * This function will generate a random fraction U and multiply it with
 * the n.  This will create a random number that ranges in the interval
 * [0, n).  The function rounds this number down to an integer, and returns
 * the integer. 
 */
{     
return (int) (drand48()* ((double) n));
}


int randarray(int a[], int asize, int n) /* Inserts random numbers in a[] */
/* 
 * This function inserts random numbers into the array a[] of size asize.
 * The random numbers range from 0 to n-1.
 */
{
int i;

for (i=0; i<asize; i++) a[i]=randnum(n);
}


