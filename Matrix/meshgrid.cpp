#include "matrix.h"
#include "error.h"

//meshgrid(x,y, xx, yy) transforms the domain specified by vectors
//x and y into matrices xx and yy. xx is a matrix with copies of x
//row wise. yy is a matrix with copies of y column wise.
void meshgrid( const Matrix& x, const Matrix& y, Matrix& xx, Matrix& yy )
{
	if( !x.isVector() || !y.isVector() )
	{
		throw error( "meshgrid:x and y must be vectors.", "exit" );
	}
	//Make sure x is a full row vector.
	Matrix xrow = tr(x(":"));
	//Make sure y is a full column vector.
    Matrix ycol = y(":");

    int nx = length(xrow); 
	int ny = length(ycol);
    
	//make ny copies of x in xx row-wise
	xx = zeros( ny, nx );
	for( int i = 0; i < ny; i++ )
	{
		xx.setRowOfMatrix( xrow, i );
	}

    //maek nx copies of y in yy col-wise
	yy = zeros( ny, nx );
	for( int j = 0; j < nx; j++ )
	{
		yy.setColOfMatrix( ycol, j );
	}
}

void meshgrid( const Matrix& x, Matrix& xx, Matrix& yy )
{
	meshgrid( x, x, xx, yy );
	return;
}