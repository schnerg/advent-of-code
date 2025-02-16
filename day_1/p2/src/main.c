#include <stdio.h>
#include <stdlib.h>
#include "include/main.h"

typedef struct
{
	int * left;
	int * mid;
	int * right;
	int count;
}lists;


lists l;

void append_to_list( int a, int b )
{
	l.count++;
	l.right = realloc( l.right , l.count * sizeof( int ) );
	l.left  = realloc( l.left , l.count * sizeof( int ) );
	l.mid  = realloc( l.mid , l.count * sizeof( int ) );
	l.left[l.count-1] = a;
	l.right[l.count-1] = b;
	return;
}

void parse_file( const char * file_name )
{
	FILE * fp = fopen( file_name, "r" );
	int n1, n2, i = 0, count = 1;
	char c;
	char * buf = calloc( count, sizeof( char ) );
	while( ( c = fgetc( fp ) ) != EOF )
	{
		switch( c )
		{
			case '\n':
			{
				buf[i] = '\0';
				sscanf( buf, "%i%i", &n1, &n2 );
				append_to_list( n1, n2 );
				i = 0;
			}break;
			
			default:
			{
				buf[i++] = c;
				if( i >= count )	
					buf = realloc( buf, ++count * sizeof( char ) );
			}break;
		
		}
	}
	fclose(fp);
	return;
}
//right?
int comp( const void * a, const void * b )
{
	return (*(int*)a - *(int*)b);
}
void sort_lists( void )
{
	qsort(l.left, l.count, sizeof(int), comp);	
	qsort(l.right, l.count, sizeof(int), comp);	
	return;
}


void count( void )
{
	for( int i = 0; i < l.count; i++ )
	{
		l.mid[i] = 0;
		for( int j = 0; j < l.count; j++ )	
		{
			if( l.left[i] == l.right[j] )
				l.mid[i]++;
		}
	}
	return;
}



int diff( int a, int b )
{
	int i = ( a > b )? a - b: b - a;
	return i;
}


int find_diff()
{
	int result = 0, n;
	for( int i = 0; i < l.count; i++ )
	{
		n = l.left[i] * l.mid[i];
		result += n;
	}
	return result;
}


void free_lists( void )
{
	free( l.right );
	free( l.left );
	return;
}


int main(int argc, char * argv[])
{
	l.count = 0;
	parse_file( "input.txt" );
	sort_lists();
	count();
	int result = find_diff();
	free_lists();
	printf( "%i\n", result );
	return 0;
}
