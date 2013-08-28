/***********************************************************

			My 2-Dimensional Matrix Class

***********************************************************/

#include "../lib/Matrix2x2.h"


Matrix2x2::Matrix2x2() {

	Vector2 newVec;

	this->mCol1 = newVec;
	this->mCol2 = newVec;
	this->mString = new char[100];

}


Matrix2x2::Matrix2x2( Vector2 newVec1, Vector2 newVec2, VectorOrder vOrder ) {

	if ( vOrder == MATRIX_ROWS ) {

		Vector2 newCol1( newVec1.x(), newVec2.x() );
		Vector2 newCol2( newVec1.y(), newVec2.y() );

		this->mCol1 = newCol1;
		this->mCol2 = newCol2;

	} else if ( vOrder == MATRIX_COLS ) {

		this->mCol1 = newVec1;
		this->mCol2 = newVec2;

	}

	this->mString = new char[100];

}


Matrix2x2::~Matrix2x2() {

	this->mString = NULL;

}


/*---------------------------
	Overloaded Operators
---------------------------*/
Matrix2x2 Matrix2x2::operator+( const Matrix2x2 &m ) const {

	Matrix2x2 result;

	result.mCol1 = this->mCol1 + m.mCol1;
	result.mCol2 = this->mCol2 + m.mCol2;

	return result;

}


Matrix2x2 Matrix2x2::operator-( const Matrix2x2 &m ) const {

	Matrix2x2 result;

	result.mCol1 = this->mCol1 - m.mCol1;
	result.mCol2 = this->mCol2 - m.mCol2;

	return result;

}


Matrix2x2 Matrix2x2::operator*( const int i ) const {

	Matrix2x2 result;

	result.mCol1 = this->mCol1 * i;
	result.mCol2 = this->mCol2 * i;

	return result;

}


Matrix2x2 Matrix2x2::operator*( const double f ) const {

	Matrix2x2 result;

	result.mCol1 = this->mCol1 * f;
	result.mCol2 = this->mCol2 * f;

	return result;

}


Vector2 Matrix2x2::operator*( const Vector2 &v ) const {

	Vector2 result;

	return result;

}


double Matrix2x2::operator*( const Matrix2x2 &m ) const {

	double result = 0.f;

	return result;

}


Matrix2x2 Matrix2x2::operator/( const int i ) const {

	Matrix2x2 result;

	result.mCol1 = this->mCol1 / i;
	result.mCol2 = this->mCol2 / i;

	return result;

}


Matrix2x2 Matrix2x2::operator/( const double f ) const {

	Matrix2x2 result;

	result.mCol1 = this->mCol1 / f;
	result.mCol2 = this->mCol2 / f;

	return result;

}


/*---------------------------
	Additional Operations
---------------------------*/
Matrix2x2 Matrix2x2::inverse( const Matrix2x2 &m ) {

	Matrix2x2 result;

	return result;

}


Matrix2x2 Matrix2x2::minors( const Matrix2x2 &m ) {

	Matrix2x2 result;

	return result;

}


Matrix2x2 Matrix2x2::cofactors( const Matrix2x2 &m ) {

	Matrix2x2 result;

	return result;

}


Matrix2x2 Matrix2x2::adjugate( const Matrix2x2 &m ) {

	Matrix2x2 result;

	return result;

}


Matrix2x2 Matrix2x2::transpose( const Matrix2x2 &m ) {

	Matrix2x2 result;

	return result;

}


double Matrix2x2::determinant( const Matrix2x2 &m ) {

	double result = 0.f;

	return result;

}


Matrix2x2 Matrix2x2::identity() {

	Vector2 iVec1( 1.f, 0.f );
	Vector2 iVec2( 0.f, 1.f );

	Matrix2x2 result( iVec1, iVec2 );

	return result;

}


const char* Matrix2x2::c_str() {

	return this->mString;

}


/*---------------------------
	  Member Accessors
---------------------------*/
Vector2 Matrix2x2::col1() const {

	return this->mCol1;

}


Vector2 Matrix2x2::col2() const {

	return this->mCol2;

}