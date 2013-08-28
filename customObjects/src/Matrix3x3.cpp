/***********************************************************

			My 3-Dimensional Matrix Class

***********************************************************/

#include "../lib/Matrix3x3.h"


Matrix3x3::Matrix3x3() {

	Vector3 newVec;

	this->mCol1 = newVec;
	this->mCol2 = newVec;
	this->mCol3 = newVec;
	this->mString = new char[100];

}


Matrix3x3::Matrix3x3( Vector3 newVec1, Vector3 newVec2, Vector3 newVec3, VectorOrder vOrder ) {

	if ( vOrder == MATRIX_ROWS ) {

		Vector3 newCol1( newVec1.x(), newVec2.x(), newVec3.x() );
		Vector3 newCol2( newVec1.y(), newVec2.y(), newVec3.y() );
		Vector3 newCol3( newVec1.z(), newVec2.z(), newVec3.z() );

		this->mCol1 = newCol1;
		this->mCol2 = newCol2;
		this->mCol3 = newCol3;

	} else if ( vOrder == MATRIX_COLS ) {

		this->mCol1 = newVec1;
		this->mCol2 = newVec2;
		this->mCol3 = newVec3;

	}

	this->mString = new char[100];

}


Matrix3x3::~Matrix3x3() {

	this->mString = NULL;

}


/*---------------------------
	Overloaded Operators
---------------------------*/
Matrix3x3 Matrix3x3::operator+( const Matrix3x3 &m ) const {

	Matrix3x3 result;

	result.mCol1 = this->mCol1 + m.mCol1;
	result.mCol2 = this->mCol2 + m.mCol2;
	result.mCol3 = this->mCol3 + m.mCol3;

	return result;

}


Matrix3x3 Matrix3x3::operator-( const Matrix3x3 &m ) const {

	Matrix3x3 result;

	result.mCol1 = this->mCol1 - m.mCol1;
	result.mCol2 = this->mCol2 - m.mCol2;
	result.mCol3 = this->mCol3 - m.mCol3;

	return result;

}


Matrix3x3 Matrix3x3::operator*( const int i ) const {

	Matrix3x3 result;

	result.mCol1 = this->mCol1 * i;
	result.mCol2 = this->mCol2 * i;
	result.mCol3 = this->mCol3 * i;

	return result;

}


Matrix3x3 Matrix3x3::operator*( const double f ) const {

	Matrix3x3 result;

	result.mCol1 = this->mCol1 * f;
	result.mCol2 = this->mCol2 * f;
	result.mCol3 = this->mCol3 * f;

	return result;

}


Vector3 Matrix3x3::operator*( const Vector3 &v ) const {

	Vector3 result;

	return result;

}


double Matrix3x3::operator*( const Matrix3x3 &m ) const {

	double result = 0.f;

	return result;

}


Matrix3x3 Matrix3x3::operator/( const int i ) const {

	Matrix3x3 result;

	result.mCol1 = this->mCol1 / i;
	result.mCol2 = this->mCol2 / i;
	result.mCol3 = this->mCol3 / i;

	return result;

}


Matrix3x3 Matrix3x3::operator/( const double f ) const {

	Matrix3x3 result;

	result.mCol1 = this->mCol1 / f;
	result.mCol2 = this->mCol2 / f;
	result.mCol3 = this->mCol3 / f;

	return result;

}


/*---------------------------
	Additional Operations
---------------------------*/
Matrix3x3 Matrix3x3::inverse( const Matrix3x3 &m ) {

	Matrix3x3 result;

	return result;

}


Matrix3x3 Matrix3x3::minors( const Matrix3x3 &m ) {

	Matrix3x3 result;

	return result;

}


Matrix3x3 Matrix3x3::cofactors( const Matrix3x3 &m ) {

	Matrix3x3 result;

	return result;

}


Matrix3x3 Matrix3x3::adjugate( const Matrix3x3 &m ) {

	Matrix3x3 result;

	return result;

}


Matrix3x3 Matrix3x3::transpose( const Matrix3x3 &m ) {

	Matrix3x3 result;

	return result;

}


double Matrix3x3::determinant( const Matrix3x3 &m ) {

	double result = 0.f;

	return result;

}


Matrix3x3 Matrix3x3::identity() {

	Vector3 iVec1( 1.f, 0.f, 0.f );
	Vector3 iVec2( 0.f, 1.f, 0.f );
	Vector3 iVec3( 0.f, 0.f, 1.f );

	Matrix3x3 result( iVec1, iVec2, iVec3 );

	return result;

}


const char* Matrix3x3::c_str() {

	return this->mString;

}


/*---------------------------
	  Member Accessors
---------------------------*/
Vector3 Matrix3x3::col1() const {

	return this->mCol1;

}


Vector3 Matrix3x3::col2() const {

	return this->mCol2;

}


Vector3 Matrix3x3::col3() const {

	return this->mCol3;

}