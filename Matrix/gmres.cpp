/*function [x,flag,relres,iter,resvec] = gmres(A,b,restart,tol,maxit,M1,M2,x,varargin)
%GMRES   Generalized Minimum Residual Method.
%   X = GMRES(A,B) attempts to solve the system of linear equations A*X = B
%   for X.  The N-by-N coefficient matrix A must be square and the right
%   hand side column vector B must have length N. This uses the unrestarted
%   method with MIN(N,10) total iterations.
%

*/

#include "matrix.h"

Matrix gmres( Matrix A, Matrix b, double tol )
{
	int n = size( A, 1 );
	int m = size( A, 2 );

	if( m != n )
	{
		throw error( "grmes:SquareMatrix:Matrix must be square.", "exit" );
	}
	if( size( b, 1 ) != m )
	{
		throw error( "gmres:VectorSize:Right hand side must be a column vector to match the coefficient matrix.", "exit" );
	}
	if( size( b, 2 ) != 1 )
	{
		throw error( " gmres:Vector: Right hand side must be a column vector.", "exit" );
	}

    bool restarted = false;
    if( tol > 1e-6 )
	{
		tol = 1e-6;
	}
	
	int maxit = n < 10 ? n:10;
	int outer = 1;
	int inner = maxit;


	// Check for all zero right hand side vector => all zero solution
	n2b = norm( b ); //                  % Norm of rhs vector, b
	if( n2b == 0 )  //                  % if    rhs vector is all zeros
	{
		Matrix x = zeros(n,1); //             % then  solution is all zeros
		return x;
	}

    Matrix x = zeros(n,1);

	//% Set up for the method
	bool flag = 1;
	Matrix xmin = x; //                       % Iterate which has minimal residual so far
	int imin = 0;  //                      % "Outer" iteration at which xmin was computed
	int jmin = 0;   //                     % "Inner" iteration at which xmin was computed
	double tolb = tol * n2b;  //              % Relative tolerance
	bool evalxm = 0;
	int stag = 0;
	int moresteps = 0;
	//int maxmsteps = min([floor(n/50),5,n-maxit]);
	int maxmsteps = floor(n/50) < 5 ? floor(n/50):5;
	maxmsteps = maxmsteps < n - maxit ? maxmsteps: n - maxit;
	int maxstagsteps = 3;
	int minupdated = 0;

	//x0iszero = (norm(x) == 0);
	bool x0iszero = true;
	r = b; //initial residual
    normr = norm(r); //                % Norm of initial residual
	if( normr <= tolb ) //              % Initial guess is a good enough solution
	{
		return x;
	}

	Matrix resvec = zeros(inner*outer+1,1); // % Preallocate vector for norm of residuals
	resvec(1) = normr;//                % resvec(1) = norm(b-A*x0)
	double normrmin = normr; //                 % Norm of residual from xmin

	//%  Preallocate J to hold the Given's rotation constants.
	Matrix J = zeros(2,inner);

	Matrix U = zeros(n,inner);
	Matrix R = zeros(inner,inner);
	Matrix w = zeros(inner+1,1);

	Matrix u;
	for( int outiter = 1; outiter <= outer; outiter++ )
	{
		//%  Construct u for Householder reflector.
		//%  u = r + sign(r(1))*||r||*e1
		u = r;
		normr = norm(r);
		double beta = scalarsign(r(1))*normr;
		u(1) = u(1) + beta;
		u = u / norm(u);
		
		//U(:,1) = u;
		U.setColOfMatrix( u, 1 );
		
		
		//%  Apply Householder projection to r.
		//%  w = r - 2*u*u'*r;
		w(1) = -beta;
    
		for( int initer = 1;  initer <= inner; initer++ )
		{
			//%  Form P1*P2*P3...Pj*ej.
			//%  v = Pj*ej = ej - 2*u*u'*ej
			Matrix v = zeros( size(u, 1 ), 1 );
			v = -2*u(initer)*u;
			v(initer) = v(initer) + 1;
			//%  v = P1*P2*...Pjm1*(Pj*ej)
			for( int k = (initer-1); k >= 1; k-- )
			{
				//Matrix uk = U.getColOfMatrix( k );
				Matrix uk = U( Index(), Index( k ) );
				v = v - uk*2*(tr(uk)*v);
			}
			
			//%  Explicitly normalize v to reduce the effects of round-off.
			v = v/norm(v);
			
			//%  Apply A to v.
			v = A*v;
			
			//%  Form Pj*Pj-1*...P1*Av.
			for( int k = 1; k <= initer; k++ )
			{
				//Matrix uk = U.getColOfMatrix( k );
				Matrix uk = U( Index(), Index(k) );
				v = v - uk*2*(tr(uk)*v);
			}
	       
		    //%  Determine Pj+1.
			if (initer != length(v))
			{
				//%  Construct u for Householder reflector Pj+1.
				//u = [zeros(initer,1); v(initer+1:end)];
				u = zeros( size( v, 1 ), 1 );
				for( int i = initer+1; i <= size( v, 1 ); i++ )
				{
					u( i ) = v( i );
				}
				double alpha = norm(u);
				if (alpha != 0)
				{
					alpha = scalarsign(v(initer+1))*alpha;
					//%  u = v(initer+1:end) +
					//%        sign(v(initer+1))*||v(initer+1:end)||*e_{initer+1)
					u(initer+1) = u(initer+1) + alpha;
					u = u / norm(u);
					//U(:,initer+1) = u;
					U.setColOfMatrix( u, initer+1 );
			
					//%  Apply Pj+1 to v.
					//%  v = v - 2*u*(u'*v);
					for( int i = initer+2; i <= length( v ); i++ )
					{
						v(i) = 0;
					}
					v(initer+1) = -alpha;
				}
			}
        
			//%  Apply Given's rotations to the newly formed v.
			for( int colJ = 1; colJ <=initer-1; colJ++ )
			{
				double tmpv = v(colJ);
				v(colJ)   = J(1,colJ)*v(colJ) + J(2,colJ)*v(colJ+1);
				v(colJ+1) = -J(2,colJ)*tmpv + J(1,colJ)*v(colJ+1);
			}
			
			//%  Compute Given's rotation Jm.
			if( !(initer==length(v)) )
			{
				//rho = norm(v(initer:initer+1));
				Matrix Tmp(2,1);
				Tmp(1) = v(initer);
				Tmp(2) = v(initer+1);
				double rho = norm( Tmp );
				//J(:,initer) = v(initer:initer+1)./rho;
				J.setColOfMatrix( Tmp/rho, initer );
				w(initer+1) = -J(2,initer)*w(initer);
				w(initer) = J(1,initer)*w(initer);
				v(initer) = rho;
				v(initer+1) = 0;
			}
        
			//R(:,initer) = v(1:inner);
			Matrix Tmp(inner, 1 );
			for( int i = 1; i <= innner; i++ )
			{
				Tmp( i ) = v( i );
			}
			R.setColOfMatrix( Tmp, initer );
			 
			normr = fabs(w(initer+1));
			resvec((outiter-1)*inner+initer+1) = normr;
			normr_act = normr;
        
			if( normr <= tolb || stag >= maxstagsteps || moresteps)
			{
				if( evalxm == 0 )
				{
					Matrix Rsub = R.getSubMatrix( 1, initer, 1, initer );
					Matrix wsub = w.getSubMatrix( i, initer, 1, 1 );
					Matrix ytmp = Rsub / wsub;
					Matrix Uiniter = U.getColOfMatrix( initer );
					Matrix additive = Uiniter*(-2*ytmp(initer)*U(initer,initer));
					additive(initer) = additive(initer) + ytmp(initer);
					for( int k = initer-1; k >= 1; k-- )
					{
						additive(k) = additive(k) + ytmp(k);
						Matrix uk = U.getColOfMatrix( k );
						additive = additive - uk*(2*tr(uk)*additive);
					}
					if(  norm(additive) < eps*norm(x) )
					{
						stag = stag + 1;
					}
					else
					{
						stag = 0;
					}
					xm = x + additive;
					evalxm = 1;
				else 
				{
					if evalxm == 1
					{
						addvc = [-(R(1:initer-1,1:initer-1)\R(1:initer-1,initer))*...
						(w(initer)/R(initer,initer)); w(initer)/R(initer,initer)];
						if norm(addvc) < eps*norm(xm)
						{
							stag = stag + 1;
						}
						else
						{
							stag = 0;
						}
                     additive = U(:,initer)*(-2*addvc(initer)*conj(U(initer,initer)));
				     additive(initer) = additive(initer) + addvc(initer);
					for k = initer-1 : -1 : 1
						additive(k) = additive(k) + addvc(k);
						additive = additive - U(:,k)*(2*(U(:,k)'*additive));
					end
					xm = xm + additive;
				end
				r = b - iterapp('mtimes',afun,atype,afcnstr,xm,varargin{:});
            if norm(r) <= tol*n2b
                x = xm;
                flag = 0;
                iter = [outiter, initer];
                break
            end
            minv_r = r;
            
            normr_act = norm(minv_r);
            resvec((outiter-1)*inner+initer+1) = normr_act;
            
            if normr_act <= normrmin
                normrmin = normr_act;
                imin = outiter;
                jmin = initer;
                xmin = xm;
                minupdated = 1;
            end
            
            if normr_act <= tolb
                x = xm;
                flag = 0;
                iter = [outiter, initer];
                break
            else
                if stag >= maxstagsteps && moresteps == 0
                    stag = 0;
                end
                moresteps = moresteps + 1;
                if moresteps >= maxmsteps
                    if ~warned
                        warning('MATLAB:gmres:tooSmallTolerance', ...
                            strcat('Input tol might be obviously smaller than',...
                            ' eps*cond(A) and may not be achieved by GMRES\n',...
                            '         Try to use a bigger tolerance'));
                    end
                    flag = 3;
                    iter = [outiter, initer];
                    break;
                end
            end
        end
        
        if normr_act <= normrmin
            normrmin = normr_act;
            imin = outiter;
            jmin = initer;
            minupdated = 1;
        end
        
        if stag >= maxstagsteps
            flag = 3;
            break;
        end
    end         % ends inner loop
    
    evalxm = 0;
    
    if flag ~= 0
        if minupdated
            idx = jmin;
        else
            idx = initer;
        end
        y = R(1:idx,1:idx) \ w(1:idx);
        additive = U(:,idx)*(-2*y(idx)*conj(U(idx,idx)));
        additive(idx) = additive(idx) + y(idx);
        for k = idx-1 : -1 : 1
            additive(k) = additive(k) + y(k);
            additive = additive - U(:,k)*(2*(U(:,k)'*additive));
        end
        x = x + additive;
        xmin = x;
        r = b - iterapp('mtimes',afun,atype,afcnstr,x,varargin{:});
        minv_r = r;
        if existM1
            minv_r = iterapp('mldivide',m1fun,m1type,m1fcnstr,r,varargin{:});
            if ~all(isfinite(minv_r))
                flag = 2;
                break
            end
        end
        if existM2
            minv_r = iterapp('mldivide',m2fun,m2type,m2fcnstr,minv_r,varargin{:});
            if ~all(isfinite(minv_r))
                flag = 2;
                break
            end
        end
        normr_act = norm(minv_r);
        r = minv_r;
    end
    
    if normr_act <= normrmin
        xmin = x;
        normrmin = normr_act;
        imin = outiter;
        jmin = initer;
    end
    
    if flag == 3
        break;
    end
    if normr_act <= tolb
        flag = 0;
        iter = [outiter, initer];
        break;
    end
    minupdated = 0;
end         % ends outer loop

% returned solution is that with minimum residual
if flag == 0
    relres = normr_act / n2minv_b;
else
    x = xmin;
    iter = [imin jmin];
    relres = normr_act / n2minv_b;
end

% truncate the zeros from resvec
if flag <= 1 || flag == 3
    resvec = resvec(1:(outiter-1)*inner+initer+1);
    indices = resvec==0;
    resvec = resvec(~indices);
else
    if initer == 0
        resvec = resvec(1:(outiter-1)*inner+1);
    else
        resvec = resvec(1:(outiter-1)*inner+initer);
    end
end

;
int scalarsgn( double d )
{
	if( d >= 0 )
	{
		return 1;
	}
	else
	{
		return -1;
	}
}
/*
function sgn = scalarsign(d)
sgn = sign(d);
if (sgn == 0)
    sgn = 1;
end
*/