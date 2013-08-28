#ifndef MM_MATRIXMATH_H
#define MM_MATRIXMATH_H

	#include <math.h>
	#include <stdio.h>

	#if   defined(MM_VECTOR_2_H)
		#include "Matrix2x2.h"
	#elif defined(MM_VECTOR_3_H)
		#include "Matrix3x3.h"
	#elif defined(MM_MATRIX_2X2_H)
		#include "Vector2.h"
	#elif defined(MM_MATRIX_3X3_H)
		#include "Vector3.h"
	#endif

	enum VectorOrder {
		MATRIX_ROWS,
		MATRIX_COLS
	};

#endif