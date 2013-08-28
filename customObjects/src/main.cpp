#include "../lib/matrixmath.h"
#include "../lib/Vector3.h"


int main(int argc, char const *argv[])
{
	
	Vector3 myXVec( 5.f, 3.f, -2.f );
	Vector3 myYVec( -13.f, 5.f, 7.f );

	printf("\nMy first vector:  %s\n", myXVec.c_str() );
	printf("My second vector: %s\n\n", myYVec.c_str() );

	Vector3 result( 0.f, 0.f, 0.f );

	result = myXVec + myYVec;
	printf("%s + %s = %s\t\tVector Addition\n", myXVec.c_str(), myYVec.c_str(), result.c_str() );

	Vector3 result2 = myXVec - myYVec;
	printf("%s - %s = %s\tVector Subtraction\n", myXVec.c_str(), myYVec.c_str(), result2.c_str() );

	result = myXVec * 3;
	printf("3*%s = %s\t\t\t\tScalar Multiplication\n", myXVec.c_str(), result.c_str() );

	result = myXVec.cross( myYVec );
	double scalarresult = myXVec * myYVec;

	printf("%s * %s = %.1f\t\t\tDot Product\n", myXVec.c_str(), myYVec.c_str(), scalarresult );

	result = myXVec.projection( myYVec );

	printf("%s proj %s = %s\tProjection of A onto B\n\n", myXVec.c_str(), myYVec.c_str(), result.c_str() );

	return 0;
}