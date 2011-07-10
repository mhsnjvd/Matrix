// Functions on matrices
// Mohsin Javed
// 1st June, 2011

#include "matrix.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

//Generates an m x n random matrix with entries
//unifrom between 0 and 1
Matrix rand( const int m, const int n )
{
	srand( ( unsigned int ) time( NULL ) );
	Matrix A( m, n );

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			//uniformly distributed number between 0 and 1
			A.a[ i ][ j ] = rand() / ( (double)RAND_MAX );
		}
	}
	return A;
}

Matrix rand( const int m )
{
	return rand( m, m );
}


// m x n identity matrix. Extra rows or columns are padded with zoros in case m != n
Matrix eye( const int m, const int n )
{
	Matrix I( m, n );

	//intialization to 0 assumed in constructor!
	
	//find minimum of m and n
	int diags = m < n ? m:n;

	for( int i = 0; i < diags; i++ )
	{
		I.a[ i ][ i ] = 1;
	}
	return I;
}

//Identity matrix
Matrix eye( const int n )
{
	return eye( n, n );
}


Matrix ones( const int m, const int n )
{
	Matrix A( m, n );
	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			A.a[ i ][ j ] = 1.0;
		}
	}
	return A;
}

Matrix ones( const int n )
{
	return ones( n, n );
} 

Matrix zeros( const int m, const int n )
{
	Matrix A( m, n );
	
	//although this is done at construction
	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			A.a[ i ][ j ] = 0.0;
		}
	}
	return A;
}

Matrix zeros( const int n )
{
	return zeros( n, n );
}

/////////////////////////////////////////////////

Matrix diag( const Matrix& A, int k )
{
	int m = A.getRows();
	int n = A.getCols();

	//If A is a vector, return a matrix with
	//A as its diagonal.
	if( m == 1 || n == 1 )
	{
		//if A is a row vector
		if( m == 1 )
		{
			if( k >= 0 )
			{
				//make a square matrix of size ( n + k ) x ( n + k )
				int dim = n + k;
				Matrix C( dim );
				for( int i = 0; i < n; i++ )
				{
					C.a[ i ][ i + k ] = A.a[ 0 ][ i ];
				}
				return C;
			}
			if( k < 0 )
			{
				//make a square matrix of size ( n - k ) x ( n - k )
				int dim = n - k;
				Matrix C( dim );
				for( int i = 0; i < n; i++ )
				{
					C.a[ i-k ][ i ] = A.a[ 0 ][ i ];
				}
				return C;
			}
		}
		//if A is a column vector
		if( n == 1 )
		{
			if( k >= 0 )
			{
				//make a square matrix of size ( m + k ) x ( m + k )
				int dim = m + k;
				Matrix C( dim );
				for( int i = 0; i < m; i++ )
				{
					C.a[ i ][ i + k ] = A.a[ i ][ 0 ];
				}
				return C;
			}
			if( k < 0 )
			{
				//make a square matrix of size ( m - k ) x ( m - k )
				int dim = m - k;
				Matrix C( dim );
				for( int i = 0; i < m; i++ )
				{
					C.a[ i-k ][ i ] = A.a[ i ][ 0 ];
				}
				return C;
			}
		}
	}
	
	// A is a matrix, not a vector, return the kth diagonal of the matrix A as a column vector.
	return A.diag( k );
}

Matrix diag( const Matrix& A )
{
	const int k = 0;
	return diag( A, k );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////