/*	some standard header files	*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RANDSEED (11)	/* seed for the random number generator */

/*	declarations of procedures defined in this file	*/
static int *generateRandomArray( int n ) ;
static void printArray( int *array, int n ) ;
static int isSorted( int *array, int n ) ;
static void heapSort (int *array, int n);
static void heapify (int *array, int n);
static void percolate (int *array, int tmpIndex, int n);
static void swap (int *array, int i, int j);

int main( int argc, char **argv )
{
int i;
int *array;
for (i = 10e5; i <= 10e6; i+= 10e5){
	array = NULL;//, n=10e5 ;
	clock_t t0, tf;
	
	array = generateRandomArray( i ) ;
	
	//printArray( array, n ) ;
	
	t0 = clock();
	heapSort (array, i);
	tf = clock();

	//printArray( array, n ) ;

	//if ( isSorted( array, i ) ) { printf("Array sorted\n") ; }
	//else { printf( "Array NOT sorted\n") ; }
	
	printf ( "%d\t%ld\n", i, (tf - t0));
	
	//


}
free(array) ;
	return ( 0 ) ;
}


int *generateRandomArray( int n )
{
	int i, *array = NULL ;

	array = (int *) malloc( sizeof(int) * n ) ;

	/* seed the random number generator */
	srand(RANDSEED) ;
	for ( i=0; i<n; i++ ) 
	{
		array[i] = (int) rand();
	}

	return ( array ) ;
}

int isSorted( int *array, int n )
{
	int i ;
	
	for ( i=0; i<n-1; i++ )
	{
		if ( array[i] > array[i+1] ) return( 0 ) ;
	}

	return( 1 ) ;
}

void printArray( int *array, int n )
{ 
	int i ;

	printf("\n") ;
	for ( i=0; i<n; i++ )
	{
		printf("%d, ", array[i]) ;
	}
	printf("\n") ;
}

void swap (int *array, int i, int j)
{
	int tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
}

void heapSort (int *array, int n)
{
	int i;
	
	heapify (array, n);
		
	for (i = (n-1); i > 0; i--)
	{
		swap (array, 0, i);
		percolate (array, 0, i);
	}
}

void heapify (int *array, int n)
{
	int i;
	for (i = floor(n/2); i >= 0; i--)
	{
		percolate (array, i, n);
	}
}

void percolate (int *array, int tmpIndex, int n)
{
	int childIndex;
	childIndex = (2*tmpIndex) + 1;
	if ((childIndex + 1) < n)
	{
		if (array[childIndex] < array[childIndex + 1])
			childIndex++;
		while (array[tmpIndex] < array[childIndex])
		{
			swap (array, tmpIndex, childIndex);
			
			tmpIndex = childIndex;
			childIndex = 2*tmpIndex + 1;
			
			if (childIndex >= n)
				break;
			
			if ((childIndex + 1) < n)
				if (array[childIndex] < array[childIndex + 1])
					childIndex++;
			}
		}
}

