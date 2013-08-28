/***********************************************************

			My 2-Dimensional Matrix Class

***********************************************************/

#ifndef MM_MATRIX_2X2_H
#define MM_MATRIX_2X2_H


// #include "matrixmath.h"
#include <stdio.h>
#include <math.h>
// #include "Vector2.h"
class Vector2;


enum VectorOrder {
	MATRIX_ROWS,
	MATRIX_COLS
};


class Matrix2x2 {

private:
	Vector2 mCol1;		//Vector column 1
	Vector2 mCol2;		//Vector column 2
	char*   mString;	//String representation

protected:


public:
	Matrix2x2( void );

	Matrix2x2( Vector2 newVec1, Vector2 newVec2, VectorOrder vOrder = MATRIX_COLS );

	~Matrix2x2( void );

	/*---------------------------
		Overloaded Operators
	---------------------------*/
	Matrix2x2 operator+( const Matrix2x2 &m ) const;

	Matrix2x2 operator-( const Matrix2x2 &m ) const;

	Matrix2x2 operator*( const int i ) const;

	Matrix2x2 operator*( const double f ) const;

	Vector2   operator*( const Vector2 &v ) const;

	double 	  operator*( const Matrix2x2 &m ) const;

	Matrix2x2 operator/( const int i ) const;

	Matrix2x2 operator/( const double f ) const;

	/*---------------------------
		Additional Operations
	---------------------------*/
	static Matrix2x2 inverse( const Matrix2x2 &m );

	static Matrix2x2 minors( const Matrix2x2 &m );

	static Matrix2x2 cofactors( const Matrix2x2 &m );

	static Matrix2x2 adjugate( const Matrix2x2 &m );

	static Matrix2x2 transpose( const Matrix2x2 &m );

	static double    determinant( const Matrix2x2 &m );

	static Matrix2x2 identity( void );

	const char*	c_str( void );

	/*---------------------------
		  Member Accessors
	---------------------------*/
	Vector2 col1( void ) const;

	Vector2 col2( void ) const;

};


#endif