/***********************************************************

			My 3-Dimensional Vector Class

***********************************************************/

#ifndef MM_VECTOR_3_H
#define MM_VECTOR_3_H


// #include "matrixmath.h"
#include <stdio.h>
#include <math.h>
class Matrix3x3;


class Vector3 {

private:
	double mX;	//X-coordinate displacement
	double mY;	//Y-coordinate displacement
	double mZ;	//Z-coordinate displacement
	char*  mString;	//String representation

protected:


public:
	Vector3( void );

	Vector3( double newX, double newY, double newZ );

	~Vector3( void );

	/*---------------------------
		Overloaded Operators
	---------------------------*/
	Vector3 operator+( const Vector3 &v ) const;

	Vector3 operator-( const Vector3 &v ) const;

	Vector3 operator*( const int i ) const;

	Vector3 operator*( const double f ) const;

	double 	operator*( const Vector3 &v ) const;

	Vector3 operator*( const Matrix3x3 &m ) const;

	Vector3 operator/( const int i ) const;

	Vector3 operator/( const double f ) const;

	/*---------------------------
		Additional Operations
	---------------------------*/
	Vector3 cross( const Vector3 &v ) const;

	Vector3 unit( void ) const;

	Vector3 projection( const Vector3 &v ) const;

	double  length( void ) const;

	const char*	c_str( void );

	/*---------------------------
		  Member Accessors
	---------------------------*/
	double x( void ) const;

	double y( void ) const;

	double z( void ) const;

};


#endif