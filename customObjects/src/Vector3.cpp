/***********************************************************

			My 3-Dimensional Vector Class

***********************************************************/

#include "../lib/Vector3.h"


Vector3::Vector3() {

	this->mX = 0.f;
	this->mY = 0.f;
	this->mZ = 0.f;
	this->mString = new char[100];

}


Vector3::Vector3( double newX, double newY, double newZ ) {

	this->mX = newX;
	this->mY = newY;
	this->mZ = newZ;
	this->mString = new char[100];
	sprintf( this->mString, "(%.2f, %.2f, %.2f)", this->mX, this->mY, this->mZ );

}


Vector3::~Vector3() {

	this->mX = 0;
	this->mY = 0;
	this->mZ = 0;
	this->mString = NULL;

}


/*---------------------------
	Overloaded Operators
---------------------------*/
Vector3 Vector3::operator+( const Vector3 &v ) const {

	Vector3 result( 0.f, 0.f, 0.f );

	result.mX = this->mX + v.x();
	result.mY = this->mY + v.y();
	result.mZ = this->mZ + v.z();

	return result;

}


Vector3 Vector3::operator-( const Vector3 &v ) const {

	Vector3 result( 0.f, 0.f, 0.f );

	result.mX = this->mX - v.x();
	result.mY = this->mY - v.y();
	result.mZ = this->mZ - v.z();

	return result;

}


Vector3 Vector3::operator*( const int i ) const {

	Vector3 result;

	result.mX = this->mX * i;
	result.mY = this->mY * i;
	result.mZ = this->mZ * i;

	return result;

}


Vector3 Vector3::operator*( const double f ) const {

	Vector3 result;

	result.mX = this->mX * f;
	result.mY = this->mY * f;
	result.mZ = this->mZ * f;

	return result;

}


double Vector3::operator*( const Vector3 &v ) const {

	double result = ( this->mX * v.x() )+
					( this->mY * v.y() )+
					( this->mZ * v.z() );

	return result;

}


Vector3 Vector3::operator*( const Matrix3x3 &m ) const {

	Vector3 result;

	return result;

}


Vector3 Vector3::operator/( const int i ) const {

	Vector3 result;

	result.mX = this->mX / i;
	result.mY = this->mY / i;
	result.mZ = this->mZ / i;

	return result;

}


Vector3 Vector3::operator/( const double f ) const {

	Vector3 result;

	result.mX = this->mX / f;
	result.mY = this->mY / f;
	result.mZ = this->mZ / f;

	return result;

}


/*---------------------------
	Additional Operations
---------------------------*/
Vector3 Vector3::cross( const Vector3 &v ) const {

	Vector3 result;

	result.mX = ( this->mY * v.z() )-( this->mZ * v.y() );
	result.mY = ( this->mZ * v.x() )-( this->mX * v.z() );
	result.mZ = ( this->mX * v.y() )-( this->mY * v.x() );

	return result;

}


Vector3 Vector3::unit() const {

	Vector3 result;
	double length = this->length();

	result = *this / length;

	return result;

}


Vector3 Vector3::projection( const Vector3 &v ) const {

	Vector3 result;

	double numerator = *this * v;
	double denominator = v.length();

	result = v.unit() * ( numerator / denominator );

	return result;

}


double   Vector3::length() const {

	double result = ( this->mX * this->mX )+( this->mY * this->mY )+( this->mZ * this->mZ );
	result = sqrt( result );

	return result;

}


const char* Vector3::c_str() {

	sprintf( this->mString, "(%.1f, %.1f, %.1f)", this->mX, this->mY, this->mZ );	
	return mString;

}


/*---------------------------
	  Member Accessors
---------------------------*/
double Vector3::x() const {

	return this->mX;

}


double Vector3::y() const {

	return this->mY;

}


double Vector3::z() const {

	return this->mZ;

}