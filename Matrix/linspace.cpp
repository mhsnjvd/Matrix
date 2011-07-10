#include "matrix.h"
// LINSPACE Linearly spaced vector.
// LINSPACE( X1, X2 ) generates a row vector of 100 linearly
// equally spaced points between X1 and X2.
// LINSPACE(X1, X2, N) generates N points between X1 and X2.
// For N < 2, LINSPACE returns X2.
Matrix linspace( const double x1, const double x2, const int n=100 )
{
	if( n < 2 )
	{
		Matrix V( 1, 1 );
		V.a[ 0 ][ 0 ] = x2;
		return V;
	}
	
	Matrix V( 1, n );
	double increment = (x2-x1)/(n-1);
	double currentValue = x1;
	for( int j = 0; j < n; j++ )
	{
		V.a[ 0 ][ j ] = currentValue;
		currentValue = currentValue + increment;
	}
	return V;
}

Matrix linspace( const double x1, const double x2 )
{
	const int n = 100;
	return linspace( x1, x2, n );
}