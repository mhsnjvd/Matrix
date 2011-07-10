#include "matrix.h"
#include <math.h>

/////////////////////////////////////////////
//overloaded commmon mathematical functions//
/////////////////////////////////////////////

Matrix Matrix::sine() const
{
	Matrix SIN( m, n );

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			SIN.a[ i ][ j ] = sin( a[ i ][ j ] );
		}
	}
	return SIN;
}

Matrix Matrix::cosine() const
{
	Matrix COS( m, n );

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			COS.a[ i ][ j ] = cos( a[ i ][ j ] );
		}
	}
	return COS;
}

Matrix Matrix::tangent() const
{
	Matrix TAN( m, n );

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			TAN.a[ i ][ j ] = tan( a[ i ][ j ] );
		}
	}
	return TAN;
}

Matrix Matrix::arcsine() const
{
	Matrix ASIN( m, n );

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			ASIN.a[ i ][ j ] = asin( a[ i ][ j ] );
		}
	}
	return ASIN;
}

Matrix Matrix::arccosine() const
{
	Matrix ACOS( m, n );

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			ACOS.a[ i ][ j ] = acos( a[ i ][ j ] );
		}
	}
	return ACOS;
}

Matrix Matrix::arctangent() const
{
	Matrix ATAN( m, n );

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			ATAN.a[ i ][ j ] = atan( a[ i ][ j ] );
		}
	}
	return ATAN;
}

Matrix Matrix::absoluteValue() const
{
	Matrix ABS( m, n );

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			ABS.a[ i ][ j ] = fabs( a[ i ][ j ] );
		}
	}
	return ABS;
}


Matrix Matrix::squareRoot() const
{
	Matrix SQRT( m, n );
	
	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			SQRT.a[ i ][ j ] = sqrt( a[ i ][ j ] );
		}
	}
	return SQRT;
}


Matrix Matrix::exponential() const
{
	Matrix EXP( m, n );

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			EXP.a[ i ][ j ] = exp( a[ i ][ j ] );
		}
	}
	return EXP;
}

Matrix Matrix::logarithm() const
{
	Matrix LOG( m, n );

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			LOG.a[ i ][ j ] = log( a[ i ][ j ] );
		}
	}
	return LOG;
}

Matrix Matrix::logarithm10() const
{
	Matrix LOG10( m, n );

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			LOG10.a[ i ][ j ] = log10( a[ i ][ j ] );
		}
	}
	return LOG10;
}

Matrix Matrix::ceilValue() const
{
	Matrix CEIL( m, n );

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			CEIL.a[ i ][ j ] = ceil( a[ i ][ j ] );
		}
	}
	return CEIL;
}

Matrix Matrix::floorValue() const
{
	Matrix FLOOR( m, n );

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			FLOOR.a[ i ][ j ] = floor( a[ i ][ j ] );
		}
	}
	return FLOOR;
}