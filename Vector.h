#pragma once
#include<assert.h>
#include<iostream>
#include<fstream>
#include<math.h>


//using std::cout;
//using std::cin;
//using std::endl;
//using std::ostream;

template <typename T>
class Vector 
{

	private :
	int len;
	T *ptr;

	public :
	
	int size() const
	{
	return len;
	}

	Vector(int n, T val);  // Constructor
	Vector(int n);  // Constructor

	~Vector();				// Destructor
	Vector(const Vector &obj);		// Copy Constructor
	Vector & operator= (const Vector &obj);  //Copy Assignment Operator

	Vector operator+ (const Vector &obj) const;
	Vector  operator- (const Vector &obj) const;
	// operator* (const Vector &obj);

	T  operator() (int index) const;
	T& operator() (int index);

	Vector & operator+= (const Vector &obj);
	Vector & operator-= (const Vector &obj);
	//Vector operator*= (const Vector &obj);

	bool operator== (const Vector &obj);
	bool operator!= (const Vector &obj);

    T l2Norm() const;
	
	void displayVector() const;


} ;



template <typename T>
Vector<T> :: Vector (int n, T val)  // Constructor
	{

	//std::cout<<"\nConstructor called for "<< n <<" len" << std::endl; 

	this->len = n;
	ptr = new T[this->len];

	for(size_t i=0 ; i < this->len ; ++i)
	    {	
	      *(this->ptr+i)=val;
	    }

	}


template <typename T>
Vector<T> :: Vector (int n)  // Constructor
	{

	//std::cout<<"\nConstructor called for "<< n <<" len. Initializes values to 0" << std::endl; 

	this->len = n;
	ptr = new T[this->len];

	for(size_t i=0 ; i < this->len ; ++i)
	    {	
	      *(this->ptr+i)=0;
	    }

	}

template <typename T>	
Vector<T>::Vector(const Vector &obj)       // Copy Constructor
	 {
	   
	 //std::cout<<"\nCopy constructor called"<<std::endl;
	  
	  this->len =obj.len;
	  
	  ptr = new T[len];
	  
	  for(size_t i=0 ; i < len ; ++i)
	    {	
	      *(ptr+i)=*(obj.ptr+i);
	    }
	 }

template <typename T>	 
Vector<T> & Vector<T>::operator=(const Vector &obj)
	 {
	  //std::cout<<"\nCopy assignment operator called"<<std::endl;
	  
	  if(this != &obj)
	  {
	   
	     this->len =obj.len;
	  
	     for(size_t i=0 ; i < len ; ++i)
	     {	
	      *(ptr+i)=*(obj.ptr+i);
	     }
	  
	  }
	  
	  return *this;
	  
	 }

template <typename T>
Vector<T>  Vector<T>::operator+ (const Vector &obj) const
{
	assert(this->len == obj.len);

	Vector sum(*this);
	sum += obj;

	return sum;
}

template <typename T>
Vector<T> & Vector<T>::operator+= (const Vector &obj)
{
	assert(this->len == obj.len);

	for(size_t i=0; i<len ; ++i)
		*(this->ptr+i) = (*(this->ptr + i)) + (*(obj.ptr +i));

	return *this;
}

template <typename T>
Vector<T>  Vector<T>::operator- (const Vector &obj) const
{
	assert(this->len == obj.len);

	Vector subtract(*this);
	subtract -= obj;

	return subtract;
}	

template <typename T>
Vector<T> & Vector<T>::operator-= (const Vector &obj)
{
	assert(this->len == obj.len);

	for(size_t i=0; i<len ; ++i)
		*(this->ptr+i) = (*(this->ptr + i)) - (*(obj.ptr +i));

	return *this;
}


template <typename T>
bool Vector<T> :: operator== (const Vector &obj)
{
	bool flag = true;

	if(((this->len) != (obj.len)))
	{
		flag = false;
		//cout<<"I am in flag"<<endl;
	}
	else 
	{
		for(size_t i=0;i < this->len ;++i)
		{
			if(*(this->ptr + i ) != *(obj.ptr + i))
				{
					flag = false;
					//cout<<"I am in for loop for i: " << i << endl;
					break;
				}
		}
	}

	return flag;
	
}

template <typename T>
bool Vector<T> :: operator!= (const Vector &obj)
{
	return !(*this == obj);
}

template <typename T>
Vector<T>::~Vector()
	{
	//cout<<"\nDestructor called " << endl; 
	
	delete[] ptr; 

	}

template <typename T>
T Vector<T> :: operator() (int index) const
{
	//cout<<"I am inside const operator ()" <<  endl; 	
	return *(ptr+ index);
} 

template <typename T>
T& Vector<T> :: operator() (int index)
{	
	//cout<<"I am inside operator ()" <<  endl; 	
	return *(ptr+ index);
}	



template<typename T>
 std::ostream& operator<< (std::ostream& os,const Vector<T>& obj)
 {
   
   obj.displayVector();
   return os;
 }

template <typename T>
T Vector<T> :: l2Norm() const
{
	T norm = 0.0,val = 0.0;

	for(size_t i=0; i< this->len ; ++i)
	{
		val = *(this->ptr + i) ; 
		norm += (val*val) ;
	}


	return sqrt(norm);
}


	
template <typename T>	
void Vector<T>::displayVector() const
      {

	std::cout<<"\nThe contents of the Vector are: "<< std::endl;
	
	for(size_t i=0 ; i < this->len ; ++i)
	    {
	      std::cout<< *(ptr+i) <<"\t";
	    }
	
	  std::cout<<std::endl;
      }




