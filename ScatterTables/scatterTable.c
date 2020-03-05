#include "scatterTable.h"

scatterTableType *initScatterTable( int M )
{
	int i ;

	scatterTableType *scatterTable = NULL ;

	scatterTable = (scatterTableType *) malloc( sizeof
						(scatterTableType ) ) ;
	scatterTable->array = (char **) malloc( sizeof(char *) * M ) ;
	scatterTable->next = (int *) malloc( sizeof(int) * M ) ;
	scatterTable->M = M ;
	scatterTable->N = 0 ;

	for ( i=0; i<M; i++ )
	{
		scatterTable->array[i] = NULL ;
		scatterTable->next[i] = -1 ;
	}

	return( scatterTable ) ;
}

void freeScatterTable( scatterTableType *scatterTable )
{
	int i ;

	for ( i=0; i<scatterTable->M; i++ )
	{
		if ( scatterTable->array[i] != NULL )
		{
			free( scatterTable->array[i] ) ;
		}
	}
	free( scatterTable->array ) ;
	free( scatterTable->next ) ;
	free( scatterTable ) ;
}

int loadScatterTable( 
	char *filename, scatterTableType *scatterTable, int *nCollisions )
{
	int iResult, N = 0 ;
	char *val = NULL ;
	int insertCollisions;

	*nCollisions = 0 ;	
	val = malloc(255) ;
	/* "r" means open file for reading. "t" means file must already exist */
	FILE *stream = fopen( filename, "rt" ) ;
	
	if ( stream != NULL )
	{
		while ( fscanf(stream, "%s", val) != EOF ) // while end of file not reached
		{
			iResult = insert( val, scatterTable, &insertCollisions ) ;
			if (iResult == 1)
			{
				N++ ;
				*nCollisions += insertCollisions;
			}
		}
	}
			
	fclose( stream ) ;

	return( N ) ;	
}

int findInScatterTable( 
	char *filename, scatterTableType *scatterTable, int *nCollisions )
{
	int nFound = 0, nColl, index, prevIndex ;
	char *val = NULL ;

	*nCollisions = 0 ;	
	val = malloc(255) ;
	FILE *stream = fopen( filename, "rt" ) ;
	
	if ( stream != NULL )
	{
		while ( fscanf(stream,"%s", val) != EOF)
		{
			nColl = 0 ;	
			if ( find( val, scatterTable, &index, &prevIndex, &nColl ) )
			{
				nFound++ ;
			}
			*nCollisions += nColl ;
		}
	}
			
	fclose( stream ) ;

	return( nFound ) ;	
}
			
int insert( char *val, scatterTableType *scatterTable, int *nCollisions )
{
	int prevIndex, index, result = 0;
	*nCollisions = 0;
	if ( ( scatterTable->N < scatterTable->M )
		&& (!find( val, scatterTable, &prevIndex, &index, nCollisions ) ) )
	{
		scatterTable->array[index] = malloc(strlen(val)+1) ;
		strcpy( scatterTable->array[index], val ) ;

		if ( prevIndex != -1 )
		{
			scatterTable->next[prevIndex] = index ;
		}
		scatterTable->N++ ;
		result = 1;
	}
		
	return( result ) ; 
}

int find( char *val, scatterTableType *s, int *prevIndex, int *index, int *nCollisions ) 
{
	int done, found = 0 ;
	int probe, nhp ;

	*prevIndex = -1 ;
	nhp = hash( val, s->M  ) ;

	done = 0 ;
	*index = nhp ;
	*prevIndex = -1 ;

	while( !done )
	{
		if ( s->array[*index] == NULL )
		{
			done = 1 ;
		}
		else if ( strcmp(val, s->array[*index] ) == 0)
		{
			done = 1 ;
			found = 1 ;
		}
		else
		{
			*prevIndex = *index ;
			*index = s->next[*prevIndex] ;
			(*nCollisions)++;
		
			if ( *index == -1 )
			{
				probe = 1 ;

				while (!done)
				{
					*index = *prevIndex + probe ;
					if (*index >= s->M) 
					{	
						*index -= s->M ;	
					}

					if ( s->array[*index] == NULL)	
					{
						done = 1 ;
					}

					probe++ ;
					if ( probe > s->M ) 
					{
						done = 1 ;
						*index = -1 ;
						*prevIndex = -1 ;
					}
				}
			}
		}
	}

	return( found ) ;	
}

int hash( char *val, int M  )
{
	return( f(val)%M ) ;
}

int f( char *val  )
{
	int i, key = 0 ;

	if ( val != NULL )
	{
		for (i=0; i<strlen(val); i++)
		{
			key += (int) val[i] ;
		}
	}

	return(key) ;
}

	
void printScatterTable( scatterTableType *s )
{
	int i ;

	printf("index\th()\tnext\tvalue\n") ;
	for ( i=0; i<s->M; i++ )
	{
		printf("%d\t%d\t%d\t%s\n", 
			i, hash(s->array[i], s->M), s->next[i], s->array[i]) ;
	}
}

int withdraw( char *val, scatterTableType *scatterTable, int *nCollisions )
{
	int result, index, nextIndex, prevIndex, tmpIndex; 
	int loopBool = 0, swapBool = 0, count = 0;
	result = find (val, scatterTable, &prevIndex, &index, nCollisions);
	if (result)
	{
		tmpIndex = index;
		while (scatterTable->next[tmpIndex] != -1 && count <= scatterTable->M)
		{
			nextIndex = scatterTable->next[tmpIndex];
			if (index >= hash(scatterTable->array[nextIndex], scatterTable->M))
			{
				scatterTable->array[index] = scatterTable->array[nextIndex];
				prevIndex = index;
				index = nextIndex;
				swapBool = 1;
			}
			else
			{
				swapBool = 0;
			}
			
			tmpIndex = nextIndex;
			loopBool = 1;
			count++;
		}
		if (swapBool)
		{
			scatterTable->next[prevIndex] = -1;
			scatterTable->array[index] = NULL;
		}
		else if (loopBool)
		{
			scatterTable->next[prevIndex] = scatterTable->next[index];
			scatterTable->next[index] = -1;
			scatterTable->array[index] = NULL;
		}
		else
		{
			scatterTable->next[index] = -1;
			scatterTable->array[index] = NULL;
		}
	}
	return result;
}

int withdrawScatterTable(char *filename, scatterTableType *scatterTable, int *nCollisions)
{
	int iResult, nColl, N = 0;
	char *val = NULL ;

	val = malloc(255) ;
	/* "r" means open file for reading. "t" means file must already exist */
	FILE *stream = fopen( filename, "rt" ) ;
	
	if ( stream != NULL )
	{
		while ( fscanf(stream, "%s", val) != EOF ) // while end of file not reached
		{
			nColl = 0;
			iResult = withdraw( val, scatterTable, &nColl);
			if (iResult)
			{
				N++;
			}
			(*nCollisions) += nColl;
		}
	}
	
	fclose( stream ) ;

	return( N ) ;
}
