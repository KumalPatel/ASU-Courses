/*
 * Usage info:
 *    To compile: g++ -fopenmp -o prob5 prob5.cpp
 *    To run: ./prob5
 * To save the output in a file, redirect stdout to a file, i.e.,
 *    ./prob5 > outputFile.txt
 * where outputFile.txt is the desired name of the output file.
 */

#include <ctime>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <omp.h>

using namespace std;

int sumWithLoop(int * A, int n);
int sumWithLoop_OMP(int * A, int n);
int sumRec(int * A, int n, int start, int end);
int sumRec_OMP(int * A, int n, int start, int end);

int main()
{
   double wtime;
   int n;
   printf ( " How many random numbers do you want to generate?\n" );
   scanf ( "%d", &n );
   int * A;
   A = new int[n];

   //generate n of random numbers
   srand( (unsigned) time(NULL) );

   for(int i = 0; i < n; i++)
   {
      A[i] = rand() % 100;
   }

   int num_procs = omp_get_num_procs ( );
   int max_threads = omp_get_max_threads ( );
   printf ( " Number of processors available = %d\n", num_procs );
   printf ( " Number of threads = %d\n", max_threads );

   //executing sumWithLoop and also measuring its execution time
   wtime = omp_get_wtime( );
   int sum1 = sumWithLoop(A, n);
   wtime = omp_get_wtime( ) - wtime;
   printf( "\n sum loop is %d\n", sum1 );
   printf ( " time  %14f\n\n", wtime );

   //executing sumWithLoop_OMP and also measuring its execution time
   wtime = omp_get_wtime ( );
   int sum2 = sumWithLoop_OMP(A, n);
   wtime = omp_get_wtime ( ) - wtime;
   printf( " sum loop OMP is %d\n", sum2 );
   printf ( " time  %14f\n\n", wtime );

   //executing sumRec and also mesuring its execution time
   wtime = omp_get_wtime( );
   int sum3 = sumRec(A, n, 0, n-1);
   wtime = omp_get_wtime( ) - wtime;
   printf( " sum recursion is %d\n", sum3 );
   printf ( " time  %14f\n\n", wtime );

   //executing sumRec_OMP and also mesuring its execution time
   wtime = omp_get_wtime ( );
   int sum4 = sumRec_OMP(A, n, 0, n-1);
   wtime = omp_get_wtime ( ) - wtime;
   printf( " sum recursion OMP is %d\n", sum4 );
   printf ( " time  %14f\n\n", wtime );
}

int sumWithLoop(int * A, int n)
{
	int sum = 0;

	for(int i = 0; i < n; i++)
	{
		sum += *(A + i);
	}

	return sum;
}

int sumWithLoop_OMP(int * A, int n)
{
	int sum = 0;

	#pragma omp parallel for reduction(+:sum)
	for(int i = 0; i < n; i++)
	{
		sum += *(A + i);
	}

	return sum;
}

int sumRec(int * A, int n, int start, int end)
{
	int sum = 0;

	if(start <= end)
	{
		int middle = (start + end)/2;
		sum = *(A + middle) + sumRec(A, n, start, middle - 1) + sumRec(A, n, middle + 1, end); // start sum at middle add one one left and one on right until you reach end of array
	}

	return sum;
}

int sumRec_OMP(int * A, int n, int start, int end)
{
	int sum = 0, first_rec, second_rec;

	if(start <= end)
	{
		int middle = (start + end)/2;
		sum = *(A + middle);
	#pragma omp parallel
	{
		#pragma omp single
		{
			#pragma omp task shared(first_rec)
			first_rec = sumRec_OMP(A, n, start, middle - 1);

			#pragma omp task shared(second_rec)
			second_rec = sumRec_OMP(A, n, middle + 1, end);

			#pragma omp taskwait
			sum += first_rec + second_rec;
		}

	}
	}
			return sum;
}
