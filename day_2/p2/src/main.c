#include "include/main.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
// all 3 have to be true
//  The levels are either all increasing or all decreasing.
//  Any two adjacent levels differ by at least one and at most three.
//  if removing a single level from an unsafe report would make it safe, the report instead counts as safe.



typedef struct
{
	int * nums;
	int count;
	int i;
}Nums;

Nums nums;
Nums temp;


int is_greater( int a, int b )
{
	if( a == b )
		return 0;
	if(a > b )
		return 1;
	if( a < b )
		return -1;
}

bool dec_or_inc( Nums * n )
{
	int inc = is_greater( n->nums[0], n->nums[1] );
	if(inc == 0 )
		return false;

	for( int i = 0; i < n->i-1; i++ )
	{
		if( inc != is_greater( n->nums[i], n->nums[i+1] )  )
			return false;
	}

		return true;
}



bool count( Nums * n )
{
	//int inc = is_greater( nums.nums[0], nums.nums[1] );	
	for(int i = 0; i < n->i -1; i++ )
	{
		int d =  n->nums[i] - n->nums[i+1];
		if( d > 3  || d < -3 ) 
			return false;
	}
	return true;
}

void append_to_nums( Nums * n, int num );

int check_array()
{
	temp.i = 0;
	temp.count = 0;
		
	if( dec_or_inc( &nums ) && count( &nums ) )
		return 1;
	else
	{
		for( int i = 0; i < nums.i; i++ )
		{
			for(int j = 0; j < nums.i; j++ )
			{
				if(j == i )
					continue;
				append_to_nums( &temp, nums.nums[j] );
			}
			if( dec_or_inc( &temp ) && count( &temp) )
			return 1;
			temp.i = 0;
		}
	}	
	return 0;
}


void append_to_nums( Nums * n, int num )
{
	if(n->nums == NULL)
		n->nums = realloc( n->nums, ++n->count * sizeof( int ) );

	n->nums[n->i++] = num;
	if( n->i >= n->count )
		n->nums = realloc( n->nums, ++n->count * sizeof( int ) );
	return;
}



int load_file( const char * file_path )
{		
	FILE * fp = fopen( file_path, "r" );
	int i = 0, count = 0, num, safe = 0;
	char * buf = calloc( ++count, sizeof( int ) );
	char c;
	while( ( c = fgetc(fp) ) != EOF )
	{
		
		if( c == ' ' || c == '\n' )	
		{
			buf[i] = '\0';
			sscanf( buf, "%i", &num );
			append_to_nums( &nums, num );
			i = 0;
		}
		if( c == '\n' )	
		{
			safe += check_array();
			nums.i = 0;
			continue;
		}
		buf[i++] = c;
		if( i >= count )
			buf = realloc( buf, ++count * sizeof( int ) );
	}
	fclose( fp );
	return safe;
}



int main( int argc, char * argv[] )
{
	nums.i = 0;
	nums.count = 0;
	printf( "%i\n", load_file( "input.txt" ) );
	free( temp.nums );
	free( nums.nums );
	return 0;
}
