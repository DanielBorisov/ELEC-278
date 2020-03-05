#include "scatterTable.h"


int main(int argc, char **argv)
{
	int M, N, nCollisions ;
	scatterTableType *scatterTable ;

	sscanf( argv[1], "%d", &M ) ;
	scatterTable = initScatterTable( M ) ;
	
	N = loadScatterTable( argv[2], scatterTable, &nCollisions ) ;
	printf("inserted %d elements into scatter table of size %d with %d collisions\n", N, M, nCollisions) ;
	printScatterTable( scatterTable ) ;
	
	printf("\n");
	N = 0;
	nCollisions = 0 ;
	N = findInScatterTable( argv[2], scatterTable, &nCollisions ) ;
	printf("found %d elements in scatter table with %d collisions\n\n", N, nCollisions) ;
	
	N = 0;
	nCollisions = 0;
	N = withdrawScatterTable( argv[2], scatterTable, &nCollisions );
	printf("deleted %d elements from scatter table with %d collisions\n", N, nCollisions) ;
	printScatterTable(scatterTable);

	
	freeScatterTable( scatterTable ) ;
	return(0) ;
}
	
