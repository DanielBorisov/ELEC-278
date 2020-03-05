#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct scatterTableType
{
	int M, N ;
	char **array ;
	int *next ;
} scatterTableType ; 


scatterTableType *initScatterTable( int M ) ;
void freeScatterTable( scatterTableType *scatterTable ) ;
int loadScatterTable( 
	char *filename, scatterTableType *scatterTable, int *nCollisions ) ;
int findInScatterTable( 
	char *filename, scatterTableType *scatterTable, int *nCollisions ) ;
int insert( char *val, scatterTableType *scatterTable, int* nCollisions ) ;
int find( char *val, scatterTableType *scatterTable, int *prevIndex, int *index, int *nCollisions ) ; 
int hash( char *val, int M  ) ;
int f( char *val  ) ;
void printScatterTable( scatterTableType *scatterTable ) ;

int withdraw( char *val, scatterTableType *scatterTable, int *nCollisions );
int withdrawScatterTable(
	char *filename, scatterTableType *scatterTable, int *nCollisions) ;
