/***********************************************************

			My 2-Dimensional Vector Class

***********************************************************/

#include "../lib/Vector2.h"


Vector2::Vector2() {

	this->mX = 0.f;
	this->mY = 0.f;
	this->mString = new char[100];

}


Vector2::Vector2( double newX, double newY ) {

	this->mX = newX;
	this->mY = newY;
	this->mString = new char[100];
	sprintf( this->mString, "(%.2f, %.2f)", this->mX, this->mY );

}


Vector2::~Vector2() {

	this->mX = 0;
	this->mY = 0;
	this->mString = NULL;

}


/*---------------------------
	Overloaded Operators
---------------------------*/
Vector2 Vector2::operator+( const Vector2 &v ) const {

	Vector2 result;

	result.mX = this->mX + v.x();
	result.mY = this->mY + v.y();

	return result;

}


Vector2 Vector2::operator-( const Vector2 &v ) const {

	Vector2 result;

	result.mX = this->mX - v.x();
	result.mY = this->mY - v.y();

	return result;

}


Vector2 Vector2::operator*( const int i ) const {

	Vector2 result;

	result.mX = this->mX * i;
	result.mY = this->mY * i;

	return result;

}


Vector2 Vector2::operator*( const double f ) const {

	Vector2 result;

	result.mX = this->mX * f;
	result.mY = this->mY * f;

	return result;

}


double Vector2::operator*( const Vector2 &v ) const {

	double result = ( this->mX * v.x() )+
					( this->mY * v.y() );

	return result;

}


Vector2 Vector2::operator*( const Matrix2x2 &m ) const {

	double newX = ( this->x() * m.col1().x() ) +
				  ( this->y() * m.col2().x() );
	double newY = ( this->x() * m.col1().y() ) +
				  ( this->y() * m.col2().y() );

	Vector2 result( newX, newY );

	return result;

}


Vector2 Vector2::operator/( const int i ) const {

	Vector2 result;

	result.mX = this->mX / i;
	result.mY = this->mY / i;

	return result;

}


Vector2 Vector2::operator/( const double f ) const {

	Vector2 result;

	result.mX = this->mX / f;
	result.mY = this->mY / f;

	return result;

}


/*---------------------------
	Additional Operations
---------------------------*/
Vector2 Vector2::unit() const {

	Vector2 result;
	double length = this->length();

	result = *this / length;

	return result;

}


Vector2 Vector2::projection( const Vector2 &v ) const {

	Vector2 result;

	double numerator = *this * v;
	double denominator = v.length();

	result = v.unit() * ( numerator / denominator );

	return result;

}


double   Vector2::length() const {

	double result = ( this->mX * this->mX ) + (this->mY * this->mY );
	result = sqrt( result );

	return result;

}


const char* Vector2::c_str() {

	sprintf( this->mString, "(%.1f, %.1f)", this->mX, this->mY );	
	return mString;

}


/*---------------------------
	  Member Accessors
---------------------------*/
double Vector2::x() const {

	return this->mX;

}


double Vector2::y() const {

	return this->mY;

}