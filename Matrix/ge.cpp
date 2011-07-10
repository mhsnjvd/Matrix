#include <iostream>
#include "matrix.h"
#include "error.h"

/////////////////////////////////////////////
//Gaussian Elimination via LU Factorization//
/////////////////////////////////////////////

//Solving a lower triangular system Lc = b
//L is assumed to be a square lower triangular matrix
//b is assumed to be a matrix with same number of rows as in L
//forward substitution
Matrix Matrix::solveLowerTriangular( const Matrix& b ) const
{		
	int o = b.getRows();
	int p = b.getCols();

	if( m != n )
	{
		throw error( "solveLowerTriangular: L must be square", "exit" );
	}
	if( m != o )
	{		
		throw error( "solveLowerTriangular:Lc=b:b should have same number of rows as L", "exit" );
	}
	
	Matrix c( o, p );
	for( int i = 0; i < m; i++ )
	{
		Matrix sum = zeros( 1, p );
		for( int j = 0; j < i; j++ )
		{
			sum = sum + a[ i ][ j ]*c.getRowOfMatrix( j );
		}
		c.setRowOfMatrix( 1/( a[ i ][ i ] )*( b.getRowOfMatrix( i ) - sum ), i );
	}
	return c;
}

//Solving an upper triangular system Ux = c
//U is assumed to be a square upper triangular matrix
//b is assumed to be a matrix with same number of rows as in U
//back substitution
Matrix Matrix::solveUpperTriangular( const Matrix& c ) const
{	
	int o = c.getRows();
	int p = c.getCols();

	if( m != n )
	{
		throw error( "solveUpperTriangular: U must be square.", "exit" );
	}
	if( m != o )
	{		
		throw error( "solveUpperTriangular:Ux=c:c should have same number of rows as U", "eixt" );
	}
	

	Matrix x( o, p );
	for( int i = m-1; i >= 0; i-- )
	{
		Matrix sum = zeros( 1, p );
		for( int j = n-1; j > i; j-- )
		{
			sum = sum + a[ i ][ j ]*x.getRowOfMatrix( j );
		}
		x.setRowOfMatrix(  1/( a[ i ][ i ] )*( c.getRowOfMatrix( i ) - sum ), i );
	}
	return x;
}

//solve Ax = b, A is n x n and b is n x m
Matrix operator /( const Matrix& A, const Matrix& b )
{
	int m = A.getRows();
	int n = A.getCols();
	int o = b.getRows();
	int p = b.getCols();

	//check for the case when b is a 1 x 1 matrix
	if( o == 1 && p == 1 )
	{
		//treat this is a matrix divided by a scalar
		return A/b.a[ 0 ][ 0 ];
	}

	if( m != n )
	{
		throw error( "/:Ax=b: A must be square", "exit" );
	}
	if( m != o  )
	{
		throw error( "/:Ax=b: b and A should have same number of rows", "exit" );
	}
	//                L is m x m      U is m x n       P is m x m
	Matrix PLU[] = { Matrix( m, m ), Matrix( m, n ) , Matrix( m, m ) };
	//place P L and U in the array PLU[]
	A.lu( PLU );
	
	//PLU[ 0 ] = L;
	//PLU[ 1 ] = U;
	//PLU[ 2 ] = P;
	
	Matrix Pb( PLU[ 2 ]*b );
	
	//solve LUx = Pb;
	//let Ux = c; and solve Lc = Pb by forward substitution
	Matrix c = PLU[ 0 ].solveLowerTriangular( Pb ); 
	//now solve Ux = c by back substituion
	Matrix x = PLU[ 1 ].solveUpperTriangular( c );
	return x;
}