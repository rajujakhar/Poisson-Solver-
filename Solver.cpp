#include <iostream>
#include <chrono>
#include "MatrixLike.h"
#include "Matrix.h"
#include "Vector.h"
#include "Stencil.h"

#define PI 3.141592653589793

 template<typename T,class MatrixImpl >
 void solve (const MatrixLike<T, MatrixImpl>& A,
            const Vector<T>& b, Vector<T>& u) 
 {
	const size_t numGridPoints = u.size( );

	double initRes = (b - A * u).l2Norm( ); // determine the initial residual
	double curRes = initRes;
	std::cout << "Initial residual:\t\t" << initRes << std::endl;

	unsigned int curIt = 0; // store the current iteration index

	while (curRes > 1.e-5 * initRes) { // solve until the residual is reduced by a certain amount
		++curIt;

		u += A.inverseDiagonal( ) * (b - A * u); // Jacobi step

		curRes = (b - A * u).l2Norm( ); // update the residual

		if (0 == curIt % 500) // print some info every few steps
			std::cout << "Residual after iteration " << curIt << ":\t" << curRes << std::endl;
	}

	std::cout << "Residual after iteration " << curIt << ":\t" << curRes << std::endl << std::endl; // print the final number of iterations and the final residual
}

void testFullMatrix (const int numGridPoints) 
{
	std::cout << "Starting full matrix solver for " << numGridPoints << " grid points" << std::endl;

	const double hx = 1. / (numGridPoints - 1);
	const double hxSq = hx * hx;
	
	Matrix<double> A(numGridPoints, numGridPoints, 0.);
	Vector<double> u(numGridPoints, 0.);
	Vector<double> b(numGridPoints, 0.);
	
	A(0, 0) = 1.;
	for (int x = 1; x < numGridPoints - 1; ++x) {
		A(x, x - 1) = 1. / hxSq;
		A(x, x) = -2. / hxSq;
		A(x, x + 1) = 1. / hxSq;
	}
	A(numGridPoints - 1, numGridPoints - 1) = 1.;

	for (int x = 0; x < numGridPoints; ++x) {
		b(x) = sin(2. * PI * (x / (double)(numGridPoints - 1)));
	}

	std::cout << "Initialization for Full Matrix complete\n";

	std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
	startTime = std::chrono::system_clock::now();
	solve(A, b, u);
	endTime = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_sec = endTime - startTime;
	std::cout<< "Time taken for "<< numGridPoints << " grid points in FullMatrix Implementation is " << elapsed_sec.count() <<" seconds" <<std::endl;

}

void testStencil (const int numGridPoints) {
	std::cout << "\nStarting Stencil Solver for " << numGridPoints << " grid points" << std::endl;  

	const double hx = 1. / (numGridPoints - 1);
	const double hxSq = hx * hx;
	Vector<double> u(numGridPoints, 0.);
	Vector<double> b(numGridPoints, 0.);

	Stencil<double> ASten({ { 0, 1. } }, { { -1, 1. / hxSq },{ 0, -2. / hxSq },{ 1, 1. / hxSq } });

	for (int x = 0; x < numGridPoints; ++x) {
		b(x) = sin(2. * PI * (x / (double)(numGridPoints - 1)));
	}
    
	std::cout << "Initialization for Stencil Matrix complete\n";

	std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
	startTime = std::chrono::system_clock::now();
	solve(ASten, b, u);
	endTime = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_sec = endTime - startTime;
	std::cout<< "Time taken for "<< numGridPoints << " grid points in  Stencil Implementation is " << elapsed_sec.count() <<" seconds"<< std::endl;

}

int main(int argc, char* argv[]) {
	testFullMatrix(129 );
	testStencil( 129);


}
