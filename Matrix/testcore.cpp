/*
 * main.cpp
 *
 *  Created on: May 5, 2011
 *      Author: math32
 */

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "matrix.h"
#include <math.h>
#include <time.h>

int main()
{
	//srand( time( NULL ) );
	int m = 2;
	int n = 3;

	Matrix T(0,0);
	std::cout << "Matrix T(0,0) = " << T << std::endl;
	std::cout << "isrow( T )  = " << isrow( T ) << std::endl;
	std::cout << "iscolumn( T )  = " << iscolumn( T ) << std::endl;
	std::cout << "isempty( T )  = " << isempty( T ) << std::endl;
	
	Matrix TT(1,0);
	std::cout << "Matrix TT(1,0) = " << TT << std::endl;
	std::cout << "isrow( TT )  = " << isrow( TT ) << std::endl;
	std::cout << "iscolumn( TT )  = " << iscolumn( TT ) << std::endl;
	std::cout << "isempty( TT )  = " << isempty( TT ) << std::endl;
	
	Matrix TTT(0,1);
	std::cout << "Matrix TTT(0,1)  = " << TTT << std::endl;
	std::cout << "isrow( TTT )  = " << isrow( TTT ) << std::endl;
	std::cout << "iscolumn( TTT )  = " << iscolumn( TTT ) << std::endl;
	std::cout << "isempty( TTT )  = " << isempty( TTT ) << std::endl;
	
	{
		//checking assignments and constructors for nasty cases!
		Matrix A(5,0);
		Matrix B(0,6);
		Matrix C(0,7);
		Matrix D(8,0);

		A = 0;
		B = 1/A;
		std::cout << B <<std::endl;
		A = rand( 5 );
		A = B;
		C = D;
		A = C;
		D = B;
	}
	//Matrix M = 4;
	//std::cout << M << std::endl;
	std::cout << "Declaring an " << m << " by " << n << " matrix A:" << std::endl;
	Matrix A(m,m);
	A.printMatrix();
	
	std::cout << "Size of A is: " << size( A ) << std::endl;
	std::cout << "any(A) = " << any(A) << std::endl;

	std::cout << "Declaring a " << m << " by " << n << " identity matrix I:" << std::endl;
	std::cout << eye( m, n ) << std::endl;
	
	std::cout << "Declaring a " << n << " by " << m << " identity matrix I:" << std::endl;
	std::cout << eye( n, m ) << std::endl;
	
	Matrix I( m );
	I = eye( m );

	std::cout << "Declaring a " << m << " by " << m << " identity matrix I:" << std::endl;
	std::cout << I << std::endl;
	
	std::cout << "any(I) = " << any(I) << std::endl;

	A = rand( m );
	std::cout << "The random matrix A:" << std::endl;
	std::cout << A << std::endl;

	std::cout << "tril(A):" << std::endl;
	std::cout << tril(A) << std::endl;

	std::cout << "triu(A):" << std::endl;
	std::cout << triu(A) << std::endl;

	std::cout << "sum(A):" << std::endl;
	std::cout << sum(A) << std::endl;

	std::cout << "sum( diag( A ) )" << std::endl;
	std::cout << sum( diag( A ) ) << std::endl;

	
	std::cout << "sum( tr( diag( A ) ) )" << std::endl;
	std::cout << sum( tr( diag( A ) ) ) << std::endl;

	std::cout << "diff(A):" << std::endl;
	std::cout << diff(A) << std::endl;

	std::cout << "diff( diag( A ) )" << std::endl;
	std::cout << diff( diag( A ) ) << std::endl;

	
	std::cout << "diff( tr( diag( A ) ) )" << std::endl;
	std::cout << diff( tr( diag( A ) ) ) << std::endl;

	std::cout << "prod(A):" << std::endl;
	std::cout << prod(A) << std::endl;

	std::cout << "prod( diag( A ) )" << std::endl;
	std::cout << prod( diag( A ) ) << std::endl;

	std::cout << "prod( tr( diag( A ) ) )" << std::endl;
	std::cout << prod( tr( diag( A ) ) ) << std::endl;

	std::cout<<"diag( rand( 4, 1 ) )" << std::endl;
	std::cout << diag( rand(4,1) ) << std::endl;
	std::cout << "A+4:" << std::endl;
	std::cout << A+4 << std::endl;

	std::cout << "4+A:" << std::endl;
	std::cout << 4+A << std::endl;

	std::cout << "A-4:" << std::endl;
	std::cout << A-4 << std::endl;

	std::cout << "4-A:" << std::endl;
	std::cout << 4-A << std::endl;


	std::cout << "I + 6*A"<<std::endl;
	std::cout << I + 6*A;
	
	std::cout << "(I + A)/4"<<std::endl;
	std::cout << (I + A)/4;
	
	std::cout << "A - I"<<std::endl;
	std::cout << A - I;
	std::cout << "I - I"<<std::endl;
	std::cout << I - I;

	A = rand( m, n );
	
	std::cout <<"The matrix A: "<<std::endl;
	std::cout << A << std::endl;
	
	std::cout <<"The same matrix printed with single index notation:" << std::endl;
	for( int i = 1; i <= m*n; i++ )
	{
		std::cout << A(i) << " ";
	}
	std::cout << std::endl;

	Matrix O( m );
	O = ones( m );
	std::cout << "Declaring an " << m << " by " << m << " matrix of ones O:" << std::endl;
	std::cout << O << std::endl;

	double a = .5;
	A = a*I;
	std::cout << "A is obtained by Multiplying I with "<< a << " :" << std::endl;
	std::cout << A << std::endl;

	Matrix B( m );
	B = rand( m );
	std::cout << "B is a random matrix:" << std::endl;
	std::cout << B << std::endl;
	
	std::cout << "Trasnspose of B is: " << std::endl;
	std::cout << tr(B) << std::endl;

	std::cout << "B(2,2):" << std::endl;
	std::cout << B(2,2) << std::endl;

	std::cout << "B.isVector() = " << B.isVector()<<std::endl;
	std::cout << "B.isColumnVector() = " << B.isColumnVector()<<std::endl;
	std::cout << "B.isRowVector() = " << B.isRowVector()<<std::endl;
	
	std::cout << "The 1st row of B is: " << std::endl;
	Matrix R( B.getRowOfMatrix( 0 ) ); //note the new notation
	std::cout << R;

	std::cout << "isvector(R) = " << isvector( R )<<std::endl;
	std::cout << "iscolumn(R) = " << iscolumn( R )<<std::endl;
	std::cout << "isrow(R) = " << isrow( R )<<std::endl;
	
	Matrix s(1,1);
	std::cout << "Matrix s = " << s << std::endl;
	std::cout << "isscalar( s ) = " << isscalar( s ) << std::endl;


	std::cout << "The 1st column of B is: " << std::endl;
	std::cout << B.getColOfMatrix( 0 )<<std::endl;

	std::cout << "The diagonal of B is:" << std::endl;
	std::cout << diag( B ) << std::endl;

	std::cout <<"norm(diag(B),1)"<<std::endl;
	std::cout <<norm(diag(B),1)<<std::endl;

	std::cout <<"norm(diag(B),2)"<<std::endl;
	std::cout <<norm(diag(B),2)<<std::endl;

	std::cout << "The sumbatirx B(1,1, 2,1,1, 2):" << std::endl;
	std::cout << B.getSubMatrix( 0, 1, 1, 0, 1, 1 );

	Matrix C( m );
	A = rand( m, n );
	B = rand( n, m );
	C = A*B;
	std::cout << "A" << std::endl;
	std::cout << A << std::endl;
	std::cout << "B" << std::endl;
	std::cout << B << std::endl;
	std::cout << "C=A*B :" << std::endl;
	std::cout << C << std::endl;
	
	std::cout << "LU-factorization of C is: " << std::endl;
	std::cout << lu(C) << std::endl;

	std::cout << "Determinant of C is: " << std::endl;
	std::cout << det(C) << std::endl;

	std::cout << "C(2,2) = " << C(2,2) << std::endl;

	
	m = 10;
	Matrix G = rand( m, m );
	Matrix b = rand( m, 1 );
	//make G symmetric
	G = tr(G)*G;
	Matrix x = G/b;

	std::cout << "G:" << std::endl;
	std::cout << G << std::endl;
	std::cout << "b:" << std::endl;
	std::cout << b << std::endl;
	std::cout << "x=" << std::endl;
	std::cout << x << std::endl;

	std::cout<<"|G*x-b|"<<std::endl;
	std::cout << abs(G*x - b)<< std::endl;

	x = cgs( G, b, zeros( m,1 ), 1e-8 );
	std::cout << "cg(A,b,x0,tol)" << std::endl;
	std::cout << x << std::endl;
	
	std::cout<<"G*x-b"<<std::endl;
	std::cout << (G*x - b )<< std::endl;

	std::cout <<"linspace(.1,1,10)"<<std::endl;
	std::cout << linspace(0.1,1,10) << std::endl;
	
	A = rand( 5, 5 );
	b = rand( 5, 10 );
	
	std::cout << "A" << std::endl;
	std::cout << A << std::endl;
	std::cout << "b" << std::endl;
	std::cout << b << std::endl;
	std::cout << "A/b" << std::endl;
	std::cout << A/b << std::endl;
	std::cout << "inv( A )" << std::endl;
	std::cout << inv( A ) << std::endl;
	std::cout << "A*inv( A )" << std::endl;
	std::cout << A * inv( A ) << std::endl;

	//std::cout << "Press any key to continue . . .";
	//std::cin.get();
	return 0;
}