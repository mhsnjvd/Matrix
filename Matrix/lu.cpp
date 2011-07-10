#include <math.h>
#include "matrix.h"

// LU(A) LU factorization of A such that PA = LU  where P is a unit lower diagonal, U is an upper diagonal
// and P is a permutation matrix.
// LU(A) returns a single matrix C. The strictly lower triangular part of C represents L. Since L is unit diagonal,
// ones on the diagonal are assumed. The upper triangular part of C (including the diagonal) represents U.
// NOTE: The perumutation matrix P is computed internally but not returned.
// Algorithm employes partial (row) pivoting.

Matrix Matrix::lu() const
{
	//make a copy of this matrix in A
	Matrix A( *this );
	//P is the permutation matrix
	Matrix P(m);
	P = eye( m, m); 

	for( int i = 0; i < m-1; i++ )
	{
		//find r the row contianing the largest pivot
		//assume pivot is already in the correct row
		int r = i;
		//look down the column
		for( int k = i; k < m; k++ )
		{
			//floating point comparisons? watchout!!!
			//if the kth row has a larger pivot
			if( fabs( A.a[ k ][ i ] ) > fabs( A.a[ r ][ i ] ) )
			{
				//update the pivot row
				r = k;
			}
		}
		//exchange the pivot row r with the current row i
		A.swapRow( i, r );
		//record this exchange in P as well
		P.swapRow( i, r );
		//extract the pivot
		double pivot = A.a[ i ][ i ];
		
		//!warning floating point comparison?
		// should be fabs(pivot) < eps ?
		if( pivot == 0 )
		{
			return A;
		}
		for( int k = i+1; k < m; k++ )
		{
			A.a[ k ][ i ] = A.a[ k ][ i ] / pivot;
			for( int j = i+1;  j < n; j++ )
			{
				A.a[ k ][ j ] = A.a[ k ][ j ] - A.a[ k ][ i ]*A.a[ i ][ j ];
			}
		}
	}
	
	return A;
}


// LU( A, PLU ) same as LU(A) but does not return any thing.
// Instead, this function expects a pointer to a Matrix array PLU.
// The function returns the following in the array PLU
// PLU[0] = L; A unit lower triangular matrix
// PLU[1] = U; An upper triangular matrix
// PLU[2] = P; A permutation matrix
// such that PA = LU
void Matrix::lu( Matrix * const PLU ) const
{
	//make a copy of this matrix in A
	Matrix A(*this);
	//P is the permutation matrix
	Matrix P(m);
	P = eye( m, m); 

	for( int i = 0; i < m-1; i++ )
	{
		//find r the row contianing the largest pivot
		//assume pivot is already in the correct row
		int r = i;
		//look down the column
		for( int k = i; k < m; k++ )
		{
			//floating point comparisons? watchout!!!
			//if the kth row has a larger pivot
			if( fabs( A.a[ k ][ i ] ) > fabs( A.a[ r ][ i ] ) )
			{
				//update the pivot row index
				r = k;
			}
		}
		//exchange the pivot row r with the current row i
		A.swapRow( i, r );
		//record this exchange in P as well
		P.swapRow( i, r );
		//extract the pivot
		double pivot = A.a[ i ][ i ];
		
		//!warning floating point comparison?
		// should be fabs(pivot) < eps ?
		if( pivot == 0 )
		{
			//what to do?
			std::cerr<<"lu(A,PLU):pivot is 0" << std::endl;
		}
		for( int k = i+1; k < m; k++ )
		{
			A.a[ k ][ i ] = A.a[ k ][ i ] / pivot;
			for( int j = i+1;  j < n; j++ )
			{
				A.a[ k ][ j ] = A.a[ k ][ j ] - A.a[ k ][ i ]*A.a[ i ][ j ];
			}
		}
	}
	
	//L is the lower triangular part of A 
	PLU[ 0 ] = A.triangularLower();
	//Make L a unit lower triangular
	int rows = PLU[ 0 ].getRows();
	for( int i = 0; i < rows; i++ )
	{
		PLU[ 0 ].a[ i ][ i ] = 1; 
	}
	//U is the upper triangular part of A	
	PLU[ 1 ] = A.triangularUpper();
	//P is the permutation matrix such that PA = LU;
	PLU[ 2 ] = P;
}