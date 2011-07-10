#include "matrix.h"
#include "math.h"
#include <iostream>

//Solving 1-D heat equation with homogenous Dirichlet boundary conditions
void solve1DHeatEquation()
{
	//define the boundaries
	double leftBoundary = 0;
	double rightBoundary = 1;
	
	//discretize the domain
	//n is the number of interior points of the 
	//domain where we want to solve the equation
	//this excludes right and left boundary points
	int n = 100;
	
	//dx is the distance between two adjacent grid points
	double dx = ( rightBoundary - leftBoundary ) / ( ( double ) n + 1 ); 
	Matrix x = linspace( leftBoundary + dx, rightBoundary - dx, n );
	
	//make x a column vector;
	x = x(":");
	//define time step
	double dt = dx/2; 
	//define maximum iterations
	int maxit = 20;
	//the parameter nu
	double nu = dt/(dx*dx);

	//specify the initial condition
	
	//initial condition is sin(pi*x)
	//const double pi = atan( (double) 1 ) * 4;
	//Matrix u = sin( pi*x );
	
	//initial condition is a hat function centred at the centre of the domain
	Matrix u = 1.0 - 2*abs( x - (leftBoundary + rightBoundary)/2 );

	
	//select method
	enum { EXPLICIT, IMPLICIT };
	int method = IMPLICIT;

	if( method == EXPLICIT )
	{
		////////////////////
		// Explicit Euler //
		////////////////////

		//Make the finite difference matrix A for the explicit Euler scheme
		Matrix A = (1-2*nu)*diag(ones(n,1)) +nu*diag( ones(n-1, 1 ), -1 ) + nu*diag( ones( n-1,1), 1 );
		//solve the heat equation
		for( int i = 1; i <= maxit; i++ )
		{
			u = A*u;
		}
	}

	if( method == IMPLICIT )
	{
		////////////////////
		// Implicit Euler //
		////////////////////
		
		//Make the finite difference matrix A for the implicit Euler scheme
		Matrix A = (1+2*nu)*diag(ones(n,1 ))-nu*diag(ones(n-1,1),-1)-nu*diag(ones(n-1,1),1 ); 
		
		//solve the heat equation
		for( int i = 1; i <= maxit; i++ )
		{
			//the overloaded / operator solves the linear system
			u = A/u;
		}
	}

	//output the solution vector
	std::cout << u << std::endl;
}
/*
int main()
{
	//solve1DHeatEquation();
	
	return 0;
}
*/