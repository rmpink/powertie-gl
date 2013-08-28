/***********************************************************

			My 2-Dimensional Vector Class

***********************************************************/

#ifndef MM_VECTOR_2_H
#define MM_VECTOR_2_H


// #include "matrixmath.h"
#include <stdio.h>
#include <math.h>
class Matrix2x2;


class Vector2 {

private:
	double mX;	//X-coordinate displacement
	double mY;	//Y-coordinate displacement
	char*  mString;	//String representation

protected:


public:
	Vector2( void );

	Vector2( double newX, double newY );

	~Vector2( void );

	/*---------------------------
		Overloaded Operators
	---------------------------*/
	Vector2 operator+( const Vector2 &v ) const;

	Vector2 operator-( const Vector2 &v ) const;

	Vector2 operator*( const int i ) const;

	Vector2 operator*( const double f ) const;

	double 	operator*( const Vector2 &v ) const;

	Vector2 operator*( const Matrix2x2 &m ) const;

	Vector2 operator/( const int i ) const;

	Vector2 operator/( const double f ) const;

	/*---------------------------
		Additional Operations
	---------------------------*/
	Vector2 unit( void ) const;

	Vector2 projection( const Vector2 &v ) const;

	double  length( void ) const;

	const char*	c_str( void );

	/*---------------------------
		  Member Accessors
	---------------------------*/
	double x( void ) const;

	double y( void ) const;

};


#endif