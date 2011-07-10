#include "matrix.h"
#include <iostream>

int main()
{
	Matrix A = rand( 10,10 );
	std::cout << A << std::endl;
	std::string str1 = "5";
	std::string str2 = "1";

	Matrix B = A( "5:-2:1", "10:-5:1" );
	std::cout << B << std::endl;

	std::cout << A( Index( 5,-2,1 ), Index( 10, -5, 1 ) ) << std::endl;
	std::cout << A( Index(), Index( 10, -5, 1 ) ) << std::endl;

	//all of A
	std::cout << A( Index(), Index() ) << std::endl;

	//4th row of A
	std::cout << A( Index(4), Index() ) << std::endl;
	
	//2nd column of A A(:,2)
	std::cout << A( Index(), Index(2) ) << std::endl;
	return 0;
}