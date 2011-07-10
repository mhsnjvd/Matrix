#include "matrix.h"
#include <iostream>


int main()
{
	int n = 100;
	Matrix y = tr( sin( linspace( 0, 1, n ) ) );

	Matrix A = diag( -4*ones( n, 1 ) ) + diag( ones( n - 1, 1 ), 1 ) + diag( ones( n - 1, 1 ), -1 );

	A = rand( n );
	A = tr(A)*A;
	y = rand( n, 1 );

	Matrix xlu = A/y;

	double tol = 1e-16;
	Matrix xcgs = cgs( A, y, zeros( n, 1 ), tol );

	std::cout << "norm( xlu - xcgs )" << std::endl;
	std::cout << norm( xlu - xcgs ) << std::endl;
	
	return 0;
}
	
