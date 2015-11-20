#pragma once

#include <cassert>
#include <utility> 		//std::swap
#include <algorithm>	 // std::find_if
#include <vector>

#include "MatrixLike.h"

template<typename T>
using StencilEntry = std::pair<int, T>; // convenience type for stencil entries

template<typename T>
class Stencil : public MatrixLike < T, Stencil<T> > /* TODO: inherit MatrixLike */ {
public:
	Stencil(const std::vector<StencilEntry<T> >& boundaryEntries, const std::vector<StencilEntry<T> >& innerEntries)
		: boundaryStencil_(boundaryEntries), innerStencil_(innerEntries) { }
	Stencil(const std::vector<StencilEntry<T> >& innerEntries)	// c'tor for stencils w/o explicit boundary handling
		: boundaryStencil_(innerEntries), innerStencil_(innerEntries) { }

	Stencil(const Stencil & o);
	Stencil(Stencil && o) noexcept;

	~Stencil( ) noexcept override{ }  

	Stencil& operator=(const Stencil & o);
	Stencil& operator=(Stencil && o) noexcept;

	/*const T & operator() (int r, int c) const ; 
	T & operator() (int r, int c) ;*/

	// HINT: stencil entries are stored as offset/coefficient pair, that is the offset specifies which element of a
	// vector, relative to the current index, is to be regarded. It is then multiplied with the according coefficient.
	// All of these expressions are evaluated and then summed up to get the final result.
	Vector<T> operator* (const Vector<T> & o) const override;

	Stencil<T> inverseDiagonal() const override;

protected:
	// containers for the stencil entries -> boundary stencils represent the first and last rows of a corresponding
	// matrix and are to be applied to the first and last element of a target vector; inner stencils correspond to
	// the remaining rows of the matrix
	std::vector<StencilEntry<T> > boundaryStencil_;	// feel free to change the datatype if convenient
	std::vector<StencilEntry<T> > innerStencil_;	// feel free to change the datatype if convenient
};

 // Overloaded multiplication operator which multiplies a stencil and a vector and returns vector
template<typename T>        
Vector<T> Stencil<T> :: operator* (const Vector<T> & o) const
{
 
 int size = o.size();
 Vector<T> v(size);

 int innerStencilSize = innerStencil_.size();
 //int boundaryStencilSize = boundaryStencil_.size();

 v(0) = (this->boundaryStencil_[0].second)*(o(0 +  this->boundaryStencil_[0].first));

 	for(size_t i=1; i < size-1 ; ++i )
 	{
 		for(size_t j=0; j<innerStencilSize ; ++j)
 		{
    	v(i) +=(this->innerStencil_[j].second)* (o(this->innerStencil_[j].first + i) ) ; 	
    	}

 	}

 v(size-1) = (this->boundaryStencil_[0].second)*(o(size-1));

 return v;
}

 // Copy Assignment Operator for Stencil class
 template<typename T>
 Stencil<T> & Stencil<T> :: operator=(const Stencil & o)
 {
 	 if (this != &o)
 	 {
 	 this->innerStencil_ = o.innerStencil_;
 	 this->boundaryStencil_ = o.boundaryStencil_;
 	 }

 	 return (*this);
 }


 // Copy constructor
 template<typename T>
 Stencil<T> :: Stencil(const Stencil & o)
 {
  std::vector< StencilEntry<T> > innerStencil_;
  std::vector< StencilEntry<T> > boundaryStencil_ ;

  this->innerStencil_  = o.innerStencil_;
  this->boundaryStencil_ = o.boundaryStencil_;
  }



 // This function returns inverse of digonal entries of matrix represented by a stencil
 template<typename T>
 Stencil<T> Stencil<T> :: inverseDiagonal( ) const
 {
  int sizeInnerStencil = this->innerStencil_.size(); 

  Stencil<T> invSten(  { { 0, 0. } }, { { 0, 0. } } );

  invSten.boundaryStencil_[0].second =  1./(this-> boundaryStencil_[0].second);
  invSten.innerStencil_[0].second = 1./(this-> innerStencil_[0.5*sizeInnerStencil].second) ;
 
  return invSten;

 } 

















