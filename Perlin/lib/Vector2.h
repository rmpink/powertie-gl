/***********************************************************

			My 2-Dimensional Vector Class

***********************************************************/

#ifndef MM_VECTOR_2_H
#define MM_VECTOR_2_H


#include <stdio.h>
#include <math.h>


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

	Vector2 operator/( const int i ) const;

	Vector2 operator/( const double f ) const;

	/*---------------------------
		Additional Operations
	---------------------------*/
	Vector2 unit( void ) const;

	Vector2 projection( const Vector2 &v ) const;

	double  length( void ) const;

	bool equals( const Vector2 &v ) const;

	bool equals( const double vX, const double vY ) const;

	const char*	c_str( void );

	/*---------------------------
		  Member Accessors
	---------------------------*/
	double x( void ) const;

	double y( void ) const;

	/*---------------------------
		  Member Mutators
	---------------------------*/
	void setX( const double newX );

	void setY( const double newY );

	void set( const double newX, const double newY );

	void set( const Vector2 &v );

};


#endif