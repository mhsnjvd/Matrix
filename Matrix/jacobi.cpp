#include "matrix.h"
// Jacobi iteration method to solve Ax=b
// x0 is the intitial guess and tol as the tolearance allowed
Matrix jacobi( Matrix A, Matrix b, Matrix x0, double tol = 1e-8 )
{
	//Define L and R where A = L + D + R;
	Matrix L = tril( A, -1 );
	Matrix R = triu( A, +1 );

	//Calculate inverse of D, where D is a diagonal
	//matrix with entries taken from diagonal of A
	//for diagonal matrices, inverse can be computed
	//by simply taking reciporcal of the entries
	Matrix Dinv = diag(diag(A)^-1);

	Matrix x = x0;
	Matrix xold;
	do
	{
		xold = x;
		x = Dinv*(-(L+R)*x+b);
	} while( norm( x-xold ) > tol );
	
	return x;
}

//function gaussSiedel( A, b, x0, tol )
//Gauss-Siedel iteration method to solve Ax=b
//x0 is the intitial guess and tol as the tolearance allowed
Matrix gaussSiedel( Matrix A, Matrix b, Matrix x0, double tol = 1e-8 )
{
	//Define L and R where A = L + D + R;
	Matrix D = diag( diag( A ) );
	Matrix L = tril( A, -1 );
	Matrix R = triu( A, +1 );

	Matrix x = x0;
	Matrix xold;
	do
	{
		xold = x;
		x = inv(L+D)*(-R*x+b);
	} while( norm(x-xold) > tol );
	return x;
}

/*
int main()
{
	//declare A as a symmetric matrix
	Matrix A = rand( 4, 4 );
	A = A * tr( A ); 
	Matrix b = rand( 4, 1 );
	Matrix x = gaussSiedel( A, b, zeros( 4,1 ) );

	std::cout << A << std::endl;
	std::cout << b << std::endl;
	std::cout << x << std::endl;

	return 0;
}
*/