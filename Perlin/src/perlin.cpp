#include <stdlib.h>

#include "../lib/perlin.h"


Uchar* whiteNoise( const Uint w, const Uint h, const Uint seed ) {
	
	Uchar* noise = new Uchar[ w*h ];

	for ( Uint i = 0; i < w*h; ++i ) {
		noise[i] = 0x00;
	}

	srand( seed );

	for ( Uint i = 0; i < w*h; ++i ) {

		noise[i] = (Uchar)(rand() % 256);
	}

	return noise;
}


Uchar* smoothNoise( Uchar* noise, const Uint w, const Uint h, const Uint octave ) {

	Uchar* smoothNoise = new Uchar[ w*h ];

	for ( Uint i = 0; i < w*h; ++i ) {
		smoothNoise[i] = 0x00;
	}

	Uint  waveLength = 1 << octave;
	float frequency  = 1.f / waveLength;

	for ( Uint x = 0; x < w; ++x ) {

		Uint x0 = ( x / waveLength ) * waveLength;
		Uint x1 = ( x0 + waveLength ) % w;
		float hBlend = ( x - x0 ) * frequency;

		for ( Uint y = 0; y < h; ++y ) {

			Uint y0 = ( y / waveLength ) * waveLength;
			Uint y1 = ( y0 + waveLength ) % h;
			float vBlend = ( y - y0 ) * frequency;

			float top = ( noise[ (y0*w) + x0 ] * ( 1-hBlend ) ) + ( hBlend * noise[ (y0*w) + x1 ] );
			float bottom = ( noise[ (y1*w) + x0 ] * ( 1-hBlend ) ) + ( hBlend * noise[ (y1*w) + x1 ] );

			smoothNoise[ (y*w) + x ] = ( top * ( 1-vBlend ) ) + ( vBlend * bottom );
		}
	}

	return smoothNoise;
}


Uchar* perlinNoise( Uchar* noise, const Uint w, const Uint h, const Uint octaveNum, const Uint seed ) {

	Uchar* smewthNoise = new Uchar[ w*h*octaveNum ];
	Uchar* perlinNoise = new Uchar[ w*h ];

	for ( Uint i = 0; i < w*h; ++i ) {
		perlinNoise[i] = 0x00;
	}

	float persistence = 0.5f;
	float amplitude   = 1.0f;
	float totalAmp    = 0.0f;

	printf("before smoothNoise\n");

	for ( Uint o = 0; o < octaveNum; ++o ) {

		Uchar* newSmooth = smoothNoise( noise, w, h, o );

		for ( Uint ns = 0; ns < w*h; ++ns ) {

			smewthNoise[ o*(w*h) + ns ] = newSmooth[ns];
		}
	}

	printf("before perlin population\n");

	for ( Uint o = octaveNum; o >= 1; --o ) {

		amplitude *= persistence;
		totalAmp  += amplitude;

		for ( Uint x = 0; x < w; ++x ) {

			for ( Uint y = 0; y < h; ++y ) {

				perlinNoise[ (y*w) + x ] += ( smewthNoise[ (o*w*h) + (y*w) + x ] * amplitude );
			}
		}

		printf("octaveNum = %d\n", octaveNum );
	}

	delete[] smewthNoise;

	for ( Uint x = 0; x < w; ++x ) {

		for ( Uint y = 0; y < h; ++y ) {

			perlinNoise[ (y*w) + x ] /= totalAmp;
		}
	}

	return perlinNoise;
}


// Uchar* featherNoise( const Uint w, const Uint h, const Uint seed ) {

// 	Uchar* noise  = new Uchar[ w*h ];
// 	int loBound = 0x00;
// 	int hiBound = 0xFF;

// 	int leftVal = 0x00;
// 	int topVal  = 0x00;

// 	for ( Uint x = 0; x < w; ++x ) {

// 		for ( Uint y = 0; y < h; ++y ) {

// 			if ( 0 < x ) {
// 				leftVal = noise[ (y*w)+(x-1) ];
// 			} else {
// 				leftVal = rand() % 256;
// 			}

// 			if ( 0 < y ) {
// 				topVal = noise[ ( (y-1)*w)+x ];
// 			} else {
// 				topVal = rand() % 256;
// 			}

// 			if ( leftVal < topVal ) {
// 				loBound = leftVal;
// 				hiBound = topVal;
// 			} else {
// 				loBound = topVal;
// 				hiBound = leftVal;
// 			}

// 			if ( hiBound == loBound ) {
// 				noise[ (y*w)+x ] = hiBound;
// 			} else {
// 				noise[ (y*w)+x ] = ( rand() % (hiBound-loBound) ) + loBound;
// 			}
// 		}
// 	}

// 	return noise;
// }