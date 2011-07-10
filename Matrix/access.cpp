#include "matrix.h"
#include "index.h"
#include "assert.h"
#include "error.h"
#include <math.h>

//*****************************************************************************
//       Access Operators to allow MATLAB style access to matrix entries
//*****************************************************************************
//Accessing entries of a matrix with double subscript.
//Note:indices start from 1 (MATLAB style).
double& Matrix::operator ()( const int i, const int j )
{
	//check range for indices
	bool p = ( i >= 1 && j >= 1 && i <= m && j <= n );
	assert( p );
	
	return a[ i-1 ][ j-1 ];
}

//Accessing entries of a matrix with single subscript (useful for vectors).
//The subscript starts from the first column running top to
//bottom and then moving to the next column.
//Note: index starts from 1 (MATLAB syle).
double& Matrix::operator ()( const int i )
{
	//check range of the index i
	bool p = ( i >= 1 && i <= m*n );
	assert( p );
		
	int r = i%m;
	int c = i/m;
	
	if( r == 0 )
	{
		return a[ m - 1 ][ c - 1 ];
	}
	else
	{
		return a[ r - 1 ][ c ];
	}
}

//********************************************************
//  Using MATLAB style indexing to get submatrices
//********************************************************
#include <string>
#include <sstream>

int stringToInteger( const std::string& str )
{
	int i;
	std::istringstream stream( str );
	if( ( stream >> i ).fail() )
	{
		throw error( "stringToInteger:can not convert string to integer.", "exit" );
	}
	else
	{
		return i;
	}
}

//extract integers from a string like "n:i:m", start = n, increment = i; end = m;
//if string is of the form "n:m", increment = 1
Index::Index( const std::string& str )
{
	//check if the string is just a ":"
	if( str == ":" )
	{
		colon = true;
		return;
	}
	else
	{
		colon = false;
	}

	//look for the first ':'
	int firstColonIndex = str.find_first_of( ':' );
	
	if( firstColonIndex != std::string::npos )
	{
		//now look for the second ':'
		int secondColonIndex = str.find( ':', firstColonIndex + 1 );
		if( secondColonIndex != std::string::npos )
		{
			//extract substrings and convert to integers
			//-1 is due to offset from Matlab indexing
			start = stringToInteger( str.substr( 0, firstColonIndex ) )-1;
			increment = stringToInteger( str.substr( firstColonIndex + 1, secondColonIndex - firstColonIndex - 1 ) );
			end = stringToInteger( str.substr( secondColonIndex + 1, str.length() - 1 - secondColonIndex ) )-1;
			
		} 
		//if there is no second ':' then the string is of the form n:m
		else
		{
			//extract substrings and convert to integers
			start = stringToInteger( str.substr( 0, firstColonIndex ) )-1;
			increment = 1;
			end = stringToInteger( str.substr( firstColonIndex + 1, str.length() - 1 - firstColonIndex ) )-1;
		}
	}
	//no colons found. this means a single number
	else
	{
		start = stringToInteger( str )-1;
		increment = 1;  //non zero increment means empy submatrix
		end = start;
	}
}

Matrix Matrix::operator () ( const std::string& str1, const std::string str2 ) const
{
	Index ind1( str1 );
	Index ind2( str2 );

	if( ind1.isColon() && !ind2.isColon() )
	{
		//first index is colon => all rows
		Matrix S( getSubMatrix( 0, 1, m-1, ind2.start, ind2.increment, ind2.end ) );
		return S;
	}
	if( !ind1.isColon() && ind2.isColon() )
	{
		//second index is colon => all columns
		Matrix S( getSubMatrix( ind1.start, ind1.increment, ind1.end, 0, 1, n-1 ) );
		return S;
	}
	if( ind1.isColon() && ind2.isColon() )
	{
		//both indices are colon => return this matrix
		return *this;
	}

	Matrix S( getSubMatrix( ind1.start, ind1.increment, ind1.end, ind2.start, ind2.increment, ind2.end ) );
	return S;
}

Matrix Matrix::operator () ( const std::string& str ) const
{
	Index ind( str );

	if( ind.isColon() )
	{
		return reshape( n*m, 1 );
	}
	else
	{
		//not implemented!!!!!
		return Matrix();
	}
}

Matrix Matrix::operator () ( const Index& ind1, const Index& ind2 ) const
{
	if( ind1.isColon() && !ind2.isColon() )
	{
		//first index is colon => all rows
		Matrix S( getSubMatrix( 0, 1, m-1, ind2.start, ind2.increment, ind2.end ) );
		return S;
	}
	if( ind2.isColon() && !ind1.isColon() )
	{
		//second index is colon => all columns
		Matrix S( getSubMatrix( ind1.start, ind1.increment, ind1.end, 0, 1, n-1 ) );
		return S;
	}
	if( ind1.isColon() && ind2.isColon() )
	{
		//both indices are colon => return this matrix
		return *this;
	}

	//else no colons, normal indices
	Matrix S( getSubMatrix( ind1.start, ind1.increment, ind1.end, ind2.start, ind2.increment, ind2.end ) );
	return S;
}

Matrix Matrix::operator () ( const Index& ind ) const
{
	//return A(:) i.e a column vector
	if( ind.isColon() )
	{
		return reshape( n*m, 1 );
	}
	else
	{
		//needs to be refined!!!
		int numel = ( ind.end - ind.start ) / ind.increment + 1;
		Matrix A( numel, 1);
		Matrix B( *this );
		for( int i = 1, ii = ind.start; i <= numel && ii <= ind.end; i++ )
		{
			A( i ) = B(ii - 1);
			ii = ii + ind.increment;
		}
		return A;
	}
}
//**************************************************************************
//**************************************************************************