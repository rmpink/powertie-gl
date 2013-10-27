#ifndef PERLIN_H
#define PERLIN_H

#include "Vector2.h"

#define Uint   unsigned int
#define Uchar  unsigned char
#define P_SEED 0xDEADBEEF


Uchar* whiteNoise( const Uint w, const Uint h, const Uint seed = P_SEED );


Uchar* smoothNoise( Uchar* noise, const Uint w, const Uint h, const Uint octave, const Uint seed );


Uchar* perlinNoise( Uchar* noise, const Uint w, const Uint h, const Uint octaveNum, const Uint seed = P_SEED );


// Uchar* featherNoise( const Uint w, const Uint h, const Uint seed = P_SEED );


//unsigned char* simplexNoise( const Uint w, )


#endif