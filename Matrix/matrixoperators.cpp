#include "matrix.h"
#include "error.h"
#include <math.h>


//********************************************************
//    Assignment Operators
//********************************************************
//The assignment operator is implemented almost the same way as the copy constructor, 
//However, it checks for self-assignment, returns *this for chained assignments, 
// and deallocates any previously allocated memory before deep copying. 
Matrix& Matrix::operator=( const Matrix& A )
{
	//check for self assignment
	if( &A != this )
	{
		int rows = A.getRows();
		int cols = A.getCols();
				
		//if A has different size then
		//delete this memory and reassign
		//memory compatible with A
		if( m != rows || n != cols )
		{
			//call the desctructor to
			//delete this memory.
			this->Matrix::~Matrix();

			//call the constructor with new
			//parameters to allocate new memory
			Matrix( rows, cols );
		}
		
		//Now this matrix and A have same sizes
		//copy components of A in this
		//NOTE: if any of A or this matrix is empty, 
		//the following loops would
		//exit without a single iteration.
		for( int i = 0; i < m; i++ )
		{
			for( int j = 0; j < n; j++ )
			{
				a[ i ][ j ] = A.a[ i ][ j ];
			}
		}
		return *this;
		
		////////////////////////////////
		//instead of the above loop we can 
		//simply use the copy constructor: 
		//this->Matrix::Matrix( A ); 
		//but this call will probably be slower, so not used.
		//////////////////////////////
		
	}
	else
	{
		//self assignment. do nothing and return!
		return *this;
	}
}

Matrix& Matrix::operator = ( const double c )
{
	//make a matrix out of the double c
	Matrix A( 1, 1 );
	A.a[ 0 ][ 0 ] = c;
	
	//call the matrix to matrix assignment
	//operator. 
	*this = A; 
	return *this;
}

Matrix& Matrix::operator = ( const int i )
{
	//make a matrix out of the integer i
	Matrix A( 1, 1 );
	A.a[ 0 ][ 0 ] = i;
	
	//call the matrix to matrix assignment operator
	*this = A; 
	return *this;
}

//***********************************************
// Printing matrices
//***********************************************
//overloaded output stream operator
std::ostream& operator << ( std::ostream& matrixOut, const Matrix& A )
{
	int m = A.getRows();
	int n = A.getCols();
	
	matrixOut.setf( std::ios::fixed, std::ios::floatfield );
	matrixOut.setf( std::ios::showpoint );
	//matrixOut.setf(std::ios_base::left, std::ios_base::adjustfield);	
	//matrixOut.precision( 6 );
	//matrixOut.fill( ':' );
	
	if( m == 0 || n == 0 )
	{
		//empty matrix
		matrixOut << "[]";
	}
	else
	{
		for( int i = 0; i < m; i++ )
		{
			for( int j = 0; j < n-1; j++ )
			{
				matrixOut << A.a[ i ][ j ] << " ";
			}	
			matrixOut << A.a[ i ][ n - 1 ] << std::endl;
		}
	}

	return matrixOut;
}
//****************************************************************


//***********************************************
// Binary Arithmetic operators +, -, *, /
//***********************************************
//Adding a constant to a matrix
Matrix operator + ( const Matrix& A, const double c )
{
	int m = A.getRows();
	int n = A.getCols();

	Matrix C( m, n );

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			C.a[ i ][ j ] = A.a[ i ][ j ] + c;
		}
	}
	return C;
}

Matrix operator + ( const double c, const Matrix& A )
{
	return A + c;
}

//Adding two matrices
Matrix operator + ( const Matrix& A, const Matrix& B )
{
	int m = A.getRows();
	int n = A.getCols();
	int o = B.getRows();
	int p = B.getCols();

	//check for cases when A or B are 1 x 1 matrices
	if( m == 1 && n == 1 )
	{
		return A.a[ 0 ][ 0 ] + B;
	}
	if( o == 1 && p == 1 )
	{

		return A + B.a[ 0 ][ 0 ];
	}

	if(  m != o  || n != p )
	{
		throw error( "+:matrix sizes not same", "exit" );
	}
	
	Matrix C(m,n);

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			C.a[ i ][ j ] = A.a[ i ][ j ] + B.a[ i ][ j ];
		}
	}
	return C;
}


//Subtracting a constant c from a matrix A: A - c
Matrix operator - ( const Matrix& A, const double c )
{
	int m = A.getRows();
	int n = A.getCols();

	Matrix C( m, n );

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			C.a[ i ][ j ] = A.a[ i ][ j ] - c;
		}
	}
	return C;
}

Matrix operator - ( const double c, const Matrix& A )
{
	int m = A.getRows();
	int n = A.getCols();

	Matrix C( m, n );

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			C.a[ i ][ j ] = c - A.a[ i ][ j ];
		}
	}
	return C;
	
	//we could have said:
	//return -1*A + c;
	//but likely to be slower.
}

//Subtracting two matrices
Matrix operator - ( const Matrix& A, const Matrix& B )
{
	int m = A.getRows();
	int n = A.getCols();
	int o = B.getRows();
	int p = B.getCols();

	//check for cases when A or B is 1 x 1
	if( m == 1 && n == 1 )
	{
		return A.a[ 0 ][ 0 ] - B;
	}

	if( o == 1 && p == 1 )
	{
		return A - B.a[ 0 ][ 0 ];
	}
 
	if( m != o || n != p  )
	{
		throw error( "-:matrix sizes not same", "exit" );
	}
	
	Matrix C(m,n);

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			C.a[ i ][ j ] = A.a[ i ][ j ] - B.a[ i ][ j ];
		}
	}
	return C;
}

//Returns the m x p matrix AB, where A is m x n and B is n x p
Matrix operator * ( const Matrix& A, const Matrix& B )
{
	int m = A.getRows();
	int n = A.getCols();
	int o = B.getRows();
	int p = B.getCols();

	//check for cases when A or B are 1x1 matrices
	if( m == 1 && n == 1 )
	{
		//treat this is a scalar times a matrix
		return A.a[ 0 ][ 0 ] * B;
	}
	if( o == 1 && p == 1 )
	{
		//treat this is a scalar times a matrix
		return B.a[ 0 ][ 0 ]*A;
	}
	
	if( n != o )
	{
		throw error( "*:matrices not compatible for multiplication", "exit" );
	}
	
	Matrix C( m, p );

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < p; j++ )
		{
			for( int k = 0; k < n; k++ )
			{
				C.a[ i ][ j ] += A.a[ i ][ k ] * B.a[ k ][ j ];
			}
		}
	}
	return C;
}

Matrix operator * ( double c, const Matrix& A )
{
	int m = A.getRows();
	int n = A.getCols();
	
	Matrix C( m, n );

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			C.a[ i ][ j ] = A.a[ i ][ j ] * c;
		}
	}
	return C;
}
	
Matrix operator * ( const Matrix& A, double a )
{
	return a*A;
}

Matrix operator &( const Matrix& A, const Matrix& B )
{
	int m = A.getRows();
	int n = A.getCols();
	int o = B.getRows();
	int p = B.getCols();

	if( m != o || n != p )
	{
		throw error( ".*:Matrix dimensions must agree.", "exit" );
	}
	
	Matrix C( m, n );

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			C.a[ i ][ j ] = A.a[ i ][ j ] * B.a[ i ][ j ];
		}
	}
	return C;
}

//Dividing a matrix by a constant
Matrix operator /( const Matrix& A, const double c )
{	
	int m = A.getRows();
	int n = A.getCols();

	Matrix C( m, n );

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			C.a[ i ][ j ] = A.a[ i ][ j ] / c;
		}
	}
	return C;
}

//Dividing a constant by a matrix
//NOTE: performs the MATLAB's c./A operator
Matrix operator /( const double c, const Matrix& A )
{
	int m = A.getRows();
	int n = A.getCols();

	
	Matrix C( m, n );
	//Note: divide by zero would be handled
	//by underlying IEEE-754
	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			C.a[ i ][ j ] = c / ( A.a[ i ][ j ] );
		}
	}
	return C;
}

//see lu.cpp for 
//Matrix operator /( const Matrix& A, const Matrix& b )

//the .^ operator NOTE: this is not matrix power
Matrix Matrix::operator ^( const double c ) const
{
	Matrix A( m, n );
	
	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			A.a[ i ][ j ] = pow( a[ i ][ j ], c );
		}
	}
	return A;
}
Matrix Matrix::operator ^( const int c ) const
{
	return this->operator ^( (double) c );
}

//*********************************************
// Unary operators
//*********************************************
Matrix operator + ( const Matrix& A )
{
	return A;
}

Matrix operator - ( const Matrix& A )
{
	int m = A.getRows();
	int n = A.getCols();

	Matrix C( m, n );

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			C.a[ i ][ j ] = -A.a[ i ][ j ];
		}
	}
	return C;
}

//****************************************************************************
//            LOGICAL Operators
//****************************************************************************
//checks if two matrices are equal
//Note: different from MATLAB's == whcih
//returns a matrix of logicals
bool operator==( const Matrix& A, const Matrix& B )
{
	int m = A.getRows();
	int n = A.getCols();
	int o = B.getRows();
	int p = B.getCols();

	if( m != o || n != p  )
	{
		return false;
	}
	else
	{
		for( int i = 0; i < m; i++ )
		{
			for( int j = 0; j < n; j++ )
			{
				if( A.a[i][j] != B.a[ i ][ j ] )
				{
					return false;
				}
			}
		}
		return true;
	}

}

bool operator != ( const Matrix& A, const Matrix& B )
{	
	return !( A == B);
}

//***************************************************************