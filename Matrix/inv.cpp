#include "matrix.h"
#include "error.h"

//calculate inverse of a square matrix
Matrix Matrix::inv() const
{
	if( m != n )
	{
		throw error( "Matrix:inv:matrix is not square", "exit" );
	}
	//sovle a linear system AX = I
	return (*this)/eye(m);
}