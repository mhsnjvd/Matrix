#include "matrix.h"
#include "error.h"
//det(A) returns the determinant
//of a square matrix A.
double Matrix::det() const
{
	if( n != m )
	{
		throw error( "matrix:det:The matrix is not square", "exit" );
	}

	//call the LU factorization of this matrix
	Matrix C( this->lu() );
	
	double determinant = 1;
	for( int i = 0;  i < m; i++ )
	{
		determinant = determinant * C.a[ i ][ i ];
	}
	return determinant;
}