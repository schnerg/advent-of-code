#include "include/main.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


//both have to be true
//  The levels are either all increasing or all decreasing.
//  Any two adjacent levels differ by at least one and at most three.


typedef struct
{
	int * nums;
	int count;
	int i;
}Nums;

Nums nums;



int is_greater( int a, int b )
{
	if( a == b )
		return 0;
	if(a > b )
		return 1;
	if( a < b )
		return -1;
}

bool dec_or_inc( void )
{
	int inc = is_greater( nums.nums[0], nums.nums[1] );
	if(inc == 0 )
		return false;

	for( int i = 0; i < nums.i-1; i++ )
	{
		if( inc != is_greater( nums.nums[i], nums.nums[i+1] )  )
			return false;
	}
		
	return true;
}



bool count( void )
{
	for(int i = 0; i < nums.i -1; i++ )
	{
		int d = nums.nums[i] - nums.nums[i+1];
		if( d > 3  || d < -3 ) 
			return false;
	}
	return true;
}


int check_array()
{
	if( dec_or_inc() && count() )
		return 1;
	return 0;
}


void append_to_nums( int num )
{
	if(nums.nums == NULL)
		nums.nums = realloc( nums.nums, ++nums.count * sizeof( int ) );

	nums.nums[nums.i++] = num;
	if( nums.i >= nums.count )
		nums.nums = realloc( nums.nums, ++nums.count * sizeof( int ) );
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
			append_to_nums( num );
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
	return 0;
}
