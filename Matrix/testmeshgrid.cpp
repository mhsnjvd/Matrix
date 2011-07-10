#include "matrix.h"
#include <iostream>
#include <math.h>

int main()
{
	Matrix x = rand( 3 );
	Matrix y;

	y = x;

	
	/*
	int n = 5;
	meshgrid( linspace( 0, 1, n ), x, y );
	double pi = atan( ( long double ) 1 )*4;
	Matrix g = 13*pi*pi*sin( 2*pi*x ) & sin( 3*pi*y );
	std::cout << size( g  ) << std::endl;
	
	//make g a column vector of (n-1)^2 rows
	//g = reshape( g, (n)^2, 1 );

	//build the matrix A
	//Matrix A = (n+1)^2*delsq(numgrid('S',n+2));

	//compute the solution
	//Matrix u= A/g;
	
	//convert the solution back to a 2D matrix
	//u = reshape( u, n, n );
*/
}