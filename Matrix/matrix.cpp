/*
 * Matrix.cpp
 Author: Mohsin Javed
 30th May, 2011
 */
#include "matrix.h"
#include <iostream>
#include <math.h>
#include <assert.h>

Matrix::Matrix()
{
	//empty matrix declared
	m = 0;
	n = 0;
	a = NULL;
}

//General constructor for a rectangular matrix
Matrix::Matrix( int const nrows, int const ncols  )
{
	//assert( nrows > 0 && ncols > 0 );
	m = nrows;
	n = ncols;
	
	//check for empty matrices
	if( m == 0 || n == 0 )
	{
		//no memory needed.
		a = NULL;
	}
	else
	{
		a = new double* [m];

		for( int i = 0; i < m; i++ )
		{
				a[i] = new double [n] ;
				//initialize matrix
				for( int j = 0; j < n; j++ )
				{
					a[ i ][ j ] = 0.0;
				}
		}
	}
}

//Constructor for a square matrix
Matrix::Matrix( int const nrows )
{
	m = nrows;
	n = nrows;
	
	//check for empty matrices
	//Note: if nrows is negative, new would
	//give an error
	if( m == 0 )
	{
		//no memory needed.
		a = NULL;
	}
	else
	{
		a = new double* [m];

		for( int i = 0; i < m; i++ )
		{
				a[ i ] = new double [n] ;
				//initialize matrix
				for( int j = 0; j < n; j++ )
				{
					a[ i ][ j ] = 0.0;
				}
		}
	}
}

//Copy constructor
Matrix::Matrix( const Matrix& A )
{
	m = A.getRows();
	n = A.getCols();

	//check for empty matrix
	if( m == 0 || n == 0 )
	{
		//no copying needed
		a = NULL;
	}
	else
	{
		//allocate memeory and 
		//copy A into this
		a = new double* [ m ];
		for( int i = 0; i < m; i++ )
		{
			a[ i ] = new double [ n ] ;

			for( int j = 0; j < n; j++ )
			{
				a[ i ][ j ] = A.a[ i ][ j ];
			}
		}
	}
}

Matrix::~Matrix()
{
	//There is nothing to delete if
	//the matrix is empty
	if( m == 0 || n == 0 )
	{
		return;
	}
	
	//delete each row
	for( int i = 0; i < m; i++ )
	{
		delete [] a[i];
	}
	//delete the row of pointers
	delete [] a;
}