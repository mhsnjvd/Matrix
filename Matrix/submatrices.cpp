#include "matrix.h"
#include "assert.h"
#include "error.h"

//**************************************************
//       Sub Matrices of a Matrix
//**************************************************
// returns the rth row of matrix as a matrix
// r must be from 0 to m-1 (NOT MATLAB style)
Matrix Matrix::getRowOfMatrix( const int r ) const
{
	bool p = ( r >= 0 ) && ( r < m );
	
	if( !p )
	{
		throw error( "Matrix:getRowOfMatrix:invalid row range", "exit" );
	}

	Matrix R( 1, n );
	for( int j = 0; j < n; j++ )
	{
		R.a[ 0 ][ j ] = a[ r ][ j ];
	}
	return R;
}
	
//returns the cth column of matrix as a matrix
// c must be from 0 to n-1 (NOT MATLAB style)
Matrix Matrix::getColOfMatrix( const int c ) const
{
	bool p = ( c >= 0 ) && ( c < n );
	if( !p )
	{
		throw error( "Matrix:getColOfMatrix:invalid column range", "exit" );
	}
	Matrix C( m, 1 );
	for( int i = 0; i < m; i++ )
	{
		C.a[ i ][ 0 ] = a[ i ][ c ];
	}
	return C;
}

void Matrix::setRowOfMatrix( const Matrix& R, const int r )
{
	//exception?
	if( r < 0 || r > m-1 )
	{
		throw error( "setRowOfMatrix: invalid row", "exit" );
	}
	
	if( R.getRows() != 1 || R.getCols() != n )
	{
		throw error( "setRowOfMatrix:input row size not compatible", "exit" );
	}

	//copy the row
	for( int j = 0; j < n; j++ )
	{
		a[ r ][ j ] = R.a[ 0 ][ j ];
	}
}
	
void Matrix::setColOfMatrix( const Matrix& C, const int c )
{
	//exception?
	if( c < 0 || c > n-1 )
	{
		throw error( "setColOfMatrix: invalid row", "exit" );
	}
	
	if( C.getCols() != 1 || C.getRows() != m )
	{
		throw error( "setColOfMatrix:input column size not compatible", "exit" );
	}

	//copy the column
	for( int i = 0; i < m; i++ )
	{
		a[ i ][ c ] = C.a[ i ][ 0 ];
	}
}


//returns the submatrix formed by rows r1:rowinc:r2 and columns c1:colinc:c2
//index range is not MATLAB style: r1 can be from 0 to m-1 and so on
Matrix Matrix::getSubMatrix( const int r1, const int rowinc, const int r2, const int c1, const int colinc, const int c2 ) const
{
	if( rowinc == 0 || colinc == 0 )
	{
		//empty matrix;
		return Matrix();
	}
	if( r1 < r2 && rowinc < 0 )
	{	//empty matrix;
		return Matrix();
	}
	if( r1 > r2 && rowinc > 0 )
	{
		//empty matrix;
		return Matrix();
	}
	if( c1 < c2 && colinc < 0 )
	{
		//empty matrix;
		return Matrix();
	}
	if( c1 > c2 && colinc > 0 )
	{
		//empty matrix;
		return Matrix();
	}
	if( r1 < 0 || r2 < 0 || c1 < 0 || c2 < 0 )
	{
		throw error( "getSubmatrix:index must be a positive integer", "exit" );
	}
	if( r1 > m-1 || r2 > m-1 || c1 > n-1 || c2 > n-1 )
	{
		throw error( "getSubmatrix::index exceeds matrix dimensions", "exit" );
	}

	//determint the number of rows and number of columns in the submatrix
	//Note: rowinc and colinc are sure to be non zero here
	int rows = ( r2 - r1 ) / rowinc + 1;
	int cols = ( c2 - c1 ) / colinc + 1;
	
	Matrix S( rows, cols );
	
	for( int i = 0, ii = r1; i < rows; i++ )
	{
		for( int j = 0, jj = c1; j < cols; j++ )
		{
			S.a[ i ][ j ] = a[ ii ][ jj ];
			jj = jj + colinc;
		}
		ii = ii + rowinc;
	}
	return S;
}
////////////////////////////////////////////////////////////////////////////////////