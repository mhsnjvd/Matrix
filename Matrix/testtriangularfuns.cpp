#include "matrix.h"
#include <iostream>

int main()
{
	Matrix A = rand( 1,4 );
	A = A + 1;
	std::cout << "A: " << std::endl;
	std::cout << A << std::endl;

	for( int i = -5; i <= 5; i++ )
	{
		std::cout << "tril(A, " << i <<" )" << std::endl;
		std::cout << tril(A, i ) << std::endl;
	}
	for( int i = -5; i <= 5; i++ )
	{
		std::cout << "triu(A, " << i <<" )" << std::endl;
		std::cout << triu(A, i ) << std::endl;
	}
	
	return 0;
}