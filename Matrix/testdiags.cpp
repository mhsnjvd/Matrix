
#include <iostream>
#include <stdlib.h>
#include "matrix.h"
#include <math.h>

int main()
{
	int m = 4;
	int n = 7;

	Matrix M = rand( m, n );

	std::cout<<"M"<<std::endl;
	std::cout<<M<<std::endl;

	for( int k = -m+1; k < n; k++ )
	{
		std::cout<<"diag(M,"<<k<<")"<<std::endl;
		std::cout<<diag(M,k)<<std::endl;
	
		std::cout<<"diag(diag(M,"<<k<<"))"<<std::endl;
		std::cout<<diag(diag(M,k) )<<std::endl;

		std::cout<<"diag(diag(M,"<<k<<"),"<<k<<")"<<std::endl;
		std::cout<<diag( diag(M,k), k ) <<std::endl;
	}
	return 0;
}