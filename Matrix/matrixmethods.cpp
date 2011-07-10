// Functions on matrices
// Mohsin Javed
// 1st June, 2011

#include "matrix.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "error.h"

int Matrix::getRows() const
{
	return m;
}

int Matrix::getCols() const
{
	return n;
}

//size of a matrix
Matrix Matrix::size() const
{
	Matrix S(1,2);
	S.a[0][0] = m;
	S.a[0][1] = n;
	return S;
}
int Matrix::size( const int dim ) const
{
	if( dim == 1 )
	{
		//return the number of rows
		return m;
	}
	if( dim == 2 )
	{
		//return the number of columns
		return n;
	}
	else
	{
		std::cerr<<"size:size(A,1) or size(A,2) allowed only."<<std::endl;
		exit(0);
	}
}
// LENGTH Length of a matrix or a vector. It is equivalent
// to MAX(SIZE()).
int Matrix::length() const
{
	return ( m > n ? m:n );
}
 
bool Matrix::isEmpty() const
{
	return ( m == 0 || n == 0 );
}

bool Matrix::isVector() const
{
	return ( m == 1 || n == 1 );
}

bool Matrix::isRowVector() const
{
	return ( m == 1 );
}

bool Matrix::isColumnVector() const
{
	return ( n == 1 );
}
bool Matrix::isScalar() const
{
	return ( m == 1 && n == 1 );
}

// SWAPROW swaps the ith row of the matrix with the jth row
void Matrix::swapRow( const int i, const int j )
{
	//check bounds on i and j
	bool p = ( i < 0 || i > m - 1 || j < 0 || j > m - 1 );
	if( p )
	{
		throw error( "swapRow: invalid row index.", "exit" );
	}
	
	if( i == j )
	{
		return;
	}
	else
	{
		double *tmp = a[ i ];
		a[ i ] = a[ j ];
		a[ j ] = tmp;
	}
}


// C = RESHAPE(M,N) returns the M-by-N matrix C whose elements
// are taken columnwise from this matrix.  An error results if
// this matrix does not have M*N elements.
Matrix Matrix::reshape( const int rows, const int cols) const
{
	//number of element of this matrix
	int numel = m*n;
	bool p = ( ( rows > 0 ) && ( cols > 0 ) && ( rows*cols == numel ) );
	
	if( !p )
	{
		throw error( "reshape:rows and cols must be positive and should give the same number of elements", "exit" );
	}
	
	Matrix C( rows, cols );

	for( int i = 1; i <= numel; i++ )
	{
		//find the corresponding
		//index in this matrix
		int r = i%m;
		int c = i/m;
		if( r == 0 )
		{
			C(i) = a[ m - 1 ][ c - 1 ];
		}
		else
		{
			C(i) = a[ r - 1 ][ c ];
		}
	}
	return C;
}


//returns the kth diagonal as a column vecotr
Matrix Matrix::diag( const int k ) const
{
	if( k >= 0 && k < n )
	{
		//if k > 0 then number of elements in the kth diagonal are min( m, n-k )
		int diags = m < n-k ? m:n-k;
		Matrix D( diags,1 );
		
		for( int i = 0; i < diags; i++ )
		{
			D.a[ i ][ 0 ] = a[ i ][ i+k ];
		}
		return D;
	}
	if( k < 0 && -k < m )
	{
		//if k < 0 then number of elements in the kth diagonal are min( m+k, n )
		int diags = m+k < n ? m+k:n;
		Matrix D( diags, 1 );

		for( int i = 0; i < diags; i++ )
		{
			D.a[ i ][ 0 ] = a[ i-k ][ i ];
		}
		return D;
	}
	//should empty matrices be treturned?
	std::cerr<<"matrix::diags:invalid diagonal requested.Returning an empty matrix."<<std::endl;
	Matrix D;
	return D;
}

//returns the main diagonal as a column vector
Matrix Matrix::diag() const
{
	const int k = 0;
	return diag(k);
}

bool Matrix::any() const
{
	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			if( a[ i ][ j ] != 0 )
			{
				return true;
			}
		}
	}
	return false;
}

//Take the transpose of a matrix
Matrix Matrix::transpose() const
{
	Matrix C( n, m );

	for( int i = 0; i < n; i++ )
	{
		for( int j = 0; j < m; j++ )
		{
			C.a[ i ][ j ] = a[ j ][ i ];
		}
	}
	return C;
}

// For vectors, SUM() is the sum of the elements of the vector.
// For matrices, SUM() is a row vector with the sum over each column.
Matrix Matrix::sumOfColumns() const
{
	//if a row vector
	//we could have been fancy by making a recursive
	//call as: sum( tr( A ) ); but this is likely to be slow!
	if( m == 1 )
	{
		double sum = 0;
		for( int j = 0; j < n; j++ )
		{
			sum = sum + a[ 0 ][ j ];
		}
		//important!!!!
		//how to deal a 1 x 1 matrix
		//should be a scalar?
		Matrix S( 1, 1 );
		S.a[ 0 ][ 0 ] = sum;
		return S;
	}

	//if not a row vector
	//return the sum of each column as a 
	//row vector (this also handles a column vector) 
	Matrix S( 1, n );

	for( int j = 0; j < n; j++ )
	{
		//compute sum of a column
		double sum = 0;
		for( int i = 0; i < m; i++ )
		{
			sum = sum + a[ i ][ j ];
		}
		//assign that sum to the returning row vector
		S.a[ 0 ][ j ] = sum;
	}
	return S;
}

// For vectors, PROD() is the prdouct of the elements of the vector.
// For matrices, PROD() is a row vector with the product over each column.
Matrix Matrix::productOfColumns() const
{
	//if a row vector
	if( m == 1 )
	{
		double product = 1;
		for( int j = 0; j < n; j++ )
		{
			product = product * a[ 0 ][ j ];
		}
		
		Matrix P( 1, 1 );
		P.a[ 0 ][ 0 ] = product;
		return P;
	}

	//if not a row vector
	//return the product of each column as a 
	//row vector (this also handles a column vector) 
	Matrix P( 1, n );

	for( int j = 0; j < n; j++ )
	{
		//compute product of a column
		double product = 1;
		for( int i = 0; i < m; i++ )
		{
			product = product * a[ i ][ j ];
		}
		//assign current product to the returning row vector
		P.a[ 0 ][ j ] = product;
	}
	return P;
}

// DIFF Difference and approximate derivative.
// DIFF(), for a vector X, is [X(2)-X(1)  X(3)-X(2) ... X(n)-X(n-1)].
// DIFF(X), for a matrix X, is the matrix of row differences,
// [X(2:n,:) - X(1:n-1,:)].
Matrix Matrix::differenceOfRows() const
{
	//if a row vector
	if( m == 1 )
	{
		Matrix D( 1, n - 1 );
		for( int j = 0; j < n-1; j++ )
		{
			D.a[ 0 ][ j ] = a[ 0 ][ j + 1 ] - a[ 0 ][ j ];
		}
		return D;
	}

	//if not a row vector
	//return the difference of consecutive rows
	//in a matrix (this also handles a column vector) 
	Matrix D( m-1, n );

	for( int i = 0; i < m-1; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			D.a[ i ][ j ] = a[ i + 1 ][ j ] - a[ i ][ j ];
		}
	}
	return D;
}

//Lower triangular part including the main diagonal
Matrix Matrix::triangularLower( const int k ) const
{
	if( k >= n - 1 )
	{
		//return the whole matrix
		return *this;
	}

	//possibly some super diagonals
	//needed as well
	if( k >= 0 && k < n - 1 )
	{
		Matrix L(m, n);
		//zero initialization of L 
		//assumed in constructor
	
		for( int i = 0; i < m; i++ )
		{
			for( int j = 0; j <= i+k && j < n; j++ )
			{
				L.a[ i ][ j ] = a[ i ][ j ];
			}
		}
		return L;
	}
	
	//do not include some diagonals
	if( k < 0 && k > -m )
	{		
		Matrix L( m, n );
		//zero initialization of L 
		//assumed in constructor
		for( int i = -k; i < m; i++ )
		{
			for( int j = 0; j <= i+k && j < n; j++ )
			{
				L.a[ i ][ j ] = a[ i ][ j ];
			}
		}
		return L;
	}
	
	//the only case left is:
	//if( k <= -m )
	//which means all diagonals are omitted
	return zeros( m, n );
}
Matrix Matrix::triangularLower() const
{
	const int k = 0;
	return triangularLower( k );
}

//Upper triangular part of A including the main diagonal
Matrix Matrix::triangularUpper( const int k ) const
{
	if( k >= n )
	{
		//return the zero matrix
		return zeros( m, n );
	}

	if( k >= 0 && k < n )
	{
		Matrix U(m, n);
		//zero initialization of U
		//assumed in constructor
	
		for( int i = 0; i < m; i++ )
		{
			for( int j = i+k; j < n; j++ )
			{
				U.a[ i ][ j ] = a[ i ][ j ];
			}
		}
		return U;
	}
	

	//do not include some diagonals
	if( k < 0 && k > -(m-1) )
	{		
		Matrix U( m, n );
		//zero initialization of U 
		//assumed in constructor
		for( int i = 0; i < m; i++ )
		{
			if( i <= -k )
			{
				for( int j = 0; j < n; j++ )
				{
					U.a[ i ][ j ] = a[ i ][ j ];
				}
			}
			if( i > -k )
			{
				for( int j = i + k; j < n; j++ )
				{
					U.a[ i ][ j ] = a[ i ][ j ];
				}
			}
		}
		return U;
	}
	
	//the only case left is: 
	//if( k <= -(m-1) )
	//which means all diagonals are required
	return *this;
}

Matrix Matrix::triangularUpper() const
{
	const int k = 0;
	return triangularUpper( k );
}
//////////////////////////////////////
//             NORMS                //
//////////////////////////////////////
double Matrix::norm( double const p ) const
{	
	if( m != 1 && n != 1 )
	{
		std::cerr<<"norm:currently norm works on vectors only."<<std::endl;
	}

	double pNormOfV = 0.0;
	
	if( m == 1 )
	{
		for( int j = 0; j < n; j++ )
		{
			pNormOfV += pow( fabs( a[ 0 ][ j ] ), p );
		}
	}
	
	if( n == 1)
	{
		for( int i = 0; i < m; i++ )
		{
			pNormOfV += pow( fabs( a[ i ][ 0 ] ), p );
		}
	}

	pNormOfV = pow( pNormOfV, 1/( (double) (p) ));
	return pNormOfV;
}

double Matrix::norm() const
{
	const double p = 2;
	return norm( p );
}
/////////////////////////////////////////////////

void Matrix::printMatrix() const
{
	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n-1; j++ )
		{
			std::cout << a[ i ][ j ] << " ";
		}
		std::cout << a[ i ][ n - 1 ] << std::endl;
	}
}
