#include "matrix.h"
#include <iostream>
#include <math.h>
#include <cfloat>

Matrix cgs( Matrix& A, Matrix& b, Matrix& x0, double tol )
{

	//Check matrix and right hand side vector inputs have appropriate sizes
	int m = size( A, 1 );                         //number of rows of A
	int n = size( A, 2 );                         //number of columns of A
	
	if( m != n )                                  //if A is not square
	{
		exit(1);
	}
	if( size( b, 1 ) != n || size( b, 2) != 1 )   //if b does not match A or is not a column vector
	{
		exit(1);
	}
	if( size( x0, 1 ) != m || size( x0, 2 ) !=  1)//if x0 does not match A or is not a column vector
	{
		exit(1);
	}
	
	if( !iscolumn( b ) )
	{
		exit(1);
	}
	//  Assign default values to unspecified parameters
	//minimum tolerance is 1e-6
	if( tol >  1e-6 )
	{
		tol = 1e-6;
	}
	
	int maxit = n < 20 ? n:20;              //maximum iterations are 20
	Matrix x = x0;                          //initial guess x0
	
	//  Check for all zero right hand side vector => all zero solution
	double n2b = norm(b);                   //  Norm of rhs vector, b
	if( fabs( n2b ) <= DBL_EPSILON )		//  if rhs vector is all zeros
	{
		x = zeros( n, 1 );                  //  then  solution is all zeros
		return x;				            
	}
	
	//  Set up for the method
	int flag = 1;
	Matrix xmin = x;                        //  Iterate which has minimal residual so far
	int imin = 0;                           //  Iteration at which xmin was computed
	double tolb = tol * n2b;                //  Relative tolerance
	Matrix r = b - A*x;                     //  Residual vector
	double normr = norm(r);                 //  Norm of residual
	double normr_act = normr;

	// other column vectors needed
	Matrix u;
	Matrix p;
	Matrix q;
	Matrix vh;
	Matrix rtvh;
	Matrix uh;
	Matrix qh;
	
	if( normr <= tolb )                     //  Initial guess is a good enough solution
	{
		return x;
	}
	
	Matrix rt = r;                          //  Shadow residual
	Matrix resvec = zeros(maxit+1,1);       //  Preallocate vector for norms of residuals
	resvec(1) = normr;                      //  resvec(1) = norm(b-A*x0)
	double normrmin = normr;                //  Norm of residual from xmin
	Matrix rho;                             //double rho = 1;
	rho = 1.0;
	Matrix rho1;
	double alpha;
	double beta;
	int stag = 0;                           //  stagnation of the method
	int moresteps = 0;
	int maxmsteps = (n/50) < 5 ? (n/50):5;  //  maxmsteps is min( floor(n/50), 5, n-maxit )
	maxmsteps = maxmsteps < n-maxit ? maxmsteps:n-maxit;
	int maxstagsteps = 3;

	//  loop over maxit iterations (unless convergence or failure)
	for( int i = 1; i <= maxit; i++ )
	{
		rho1 = rho;
		rho = tr( rt )*r;
		if( fabs( rho(1) ) <= DBL_EPSILON || fabs( rho(1) ) >= DBL_MAX )
		{
			flag = 4;
			break;
		}
		
		if(  i == 1 )
		{
			u = r;
			p = u;
		}
		else
		{
			beta = rho(1) / rho1(1);
			if( fabs( beta ) < DBL_EPSILON || fabs( beta ) > DBL_MAX  )
			{
				flag = 4;
				break;
			}
			u = r + beta * q;
			p = u + beta * (q + beta * p);
		}

		vh = A*p;
		rtvh = tr( rt ) * vh;
		if( fabs( rtvh( 1 ) )  <= DBL_EPSILON )
		{
			flag = 4;
			break;
		}
		else
		{
			alpha = rho(1) / rtvh(1);
		}
		
		if( fabs( alpha ) >= DBL_MAX )
		{
			flag = 4;
			break;
		}
		q = u - alpha * vh;
		uh = u+q;
	    
		//  Check for stagnation of the method
		if( fabs(alpha)*norm(uh) < DBL_EPSILON*norm(x) )
		{
			stag = stag + 1;
		}
		else
		{
			stag = 0;
		}
	    
		x = x + alpha * uh;            //  form the new iterate
		qh = A*uh;
		r = r - alpha * qh;
		normr = norm(r);
		normr_act = normr;
		resvec(i+1) = normr;
	    
		//  check for convergence
		if( normr <= tolb || stag >= maxstagsteps || moresteps )
		{
			r = b - A*x;
			normr_act = norm(r);
			resvec(i+1,1) = normr_act;
			if( normr_act <= tolb )
			{
				flag = 0;
				break;
			}
			else
			{
				if( stag >= maxstagsteps && moresteps == 0 )
				{
					stag = 0;
				}
				moresteps = moresteps + 1;
			}	
		}
	    
		if( normr_act < normrmin )         //  update minimal norm quantities
		{
			normrmin = normr_act;
			xmin = x;
		}
	}                                      //  for i = 1 : maxit
	
	if( flag == 0 )
	{
		//tolerance achieved
		return x;
	}
	else
	{
		if( flag == 4)
		{
			std::cerr<<"too small or too large a number encountered."<<std::endl;
		}
		r = b - A*xmin;
		if( norm(r) <= normr_act )
		{
			x = xmin;
		}
		return x;
	}
}
