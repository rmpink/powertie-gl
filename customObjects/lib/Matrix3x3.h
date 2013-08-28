/***********************************************************

			My 3-Dimensional Matrix Class

***********************************************************/

#ifndef MM_MATRIX_3X3_H
#define MM_MATRIX_3X3_H


// #include "matrixmath.h"
#include <stdio.h>
#include <math.h>
// #include "Vector3.h"
class Vector3;


enum VectorOrder {
	MATRIX_ROWS,
	MATRIX_COLS
};


class Matrix3x3 {

private:
	Vector3 mCol1;		//Vector column 1
	Vector3 mCol2;		//Vector column 2
	Vector3 mCol3;		//Vector column 3
	char*   mString;	//String representation

protected:


public:
	Matrix3x3( void );

	Matrix3x3( Vector3 newVec1, Vector3 newVec2, Vector3 newVec3, VectorOrder vOrder = MATRIX_COLS );

	~Matrix3x3( void );

	/*---------------------------
		Overloaded Operators
	---------------------------*/
	Matrix3x3 operator+( const Matrix3x3 &m ) const;

	Matrix3x3 operator-( const Matrix3x3 &m ) const;

	Matrix3x3 operator*( const int i ) const;

	Matrix3x3 operator*( const double f ) const;

	Vector3   operator*( const Vector3 &v ) const;

	double 	  operator*( const Matrix3x3 &m ) const;

	Matrix3x3 operator/( const int i ) const;

	Matrix3x3 operator/( const double f ) const;

	/*---------------------------
		Additional Operations
	---------------------------*/
	static Matrix3x3 inverse( const Matrix3x3 &m );

	static Matrix3x3 minors( const Matrix3x3 &m );

	static Matrix3x3 cofactors( const Matrix3x3 &m );

	static Matrix3x3 adjugate( const Matrix3x3 &m );

	static Matrix3x3 transpose( const Matrix3x3 &m );

	static double    determinant( const Matrix3x3 &m );

	static Matrix3x3 identity( void );

	const char*	c_str( void );

	/*---------------------------
		  Member Accessors
	---------------------------*/
	Vector3 col1( void ) const;

	Vector3 col2( void ) const;

	Vector3 col3( void ) const;

};


#endif