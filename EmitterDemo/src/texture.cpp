/*
 * PROJECT:
 * FILEPATH:
 * AUTHOR:
 * DATE CREATED:
 * DATE MODIFIED:
 *
 * DESCRIPTION:
 *
 *
 */

#include "../lib/texture.h"
#include "../lib/vertexData2D.h"
#include <string.h>


////////////////////////////////////
//			 PROTECTED			  //
////////////////////////////////////
GLuint Texture::CalcTexturePadding( GLuint val ) {
	//Calculates the padding required for given dimension
	
	GLuint powerOfTwo = 1;

	while ( powerOfTwo < val ) {

		powerOfTwo *= 2;
	}

	return powerOfTwo;
}


bool Texture::InitVBO() {
	//Generates Vertex and Index Buffer Objects

	bool success = true;
	
	if ( mID && !mVBOID ) {

		VertexData2D vData[4];
		GLuint 		 iData[4] = { 0, 1, 2, 3 };

		glGenBuffers( 1, &mVBOID );
		glBindBuffer( GL_ARRAY_BUFFER, mVBOID );
		glBufferData( GL_ARRAY_BUFFER, 4 * sizeof( VertexData2D ), vData, GL_DYNAMIC_DRAW );

		glGenBuffers( 1, &mIBOID );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mIBOID );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof( GLuint ), iData, GL_DYNAMIC_DRAW );

		glBindBuffer( GL_ARRAY_BUFFER, (GLuint)NULL );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, (GLuint)NULL );

	} else {

		if ( !mID ) {
			//Some error code: TEXTURE_ID_NOT_FOUND
			printf("InitVBO failed: mID not found\n");
		} else if ( mVBOID ) {
			//Some error code: TEXTURE_VBO_ALREADY_EXISTS
			// printf("InitVBO failed: VBO already exists\n");
		}

		success = false;
	}

	return success;	
}


bool Texture::FreeVBO() {
	//Free VBO and IBO data buffers

	bool success = true;
	
	if ( mVBOID && mIBOID ) {

		glDeleteBuffers( 1, &mVBOID );
		glDeleteBuffers( 1, &mIBOID );

	} else {
		//Some error code: TEXTURE_VBO_NOT_FOUND
		printf("FreeVBO failed. mVBOID = %d, mIBOID = %d\n", mVBOID, mIBOID);
		success = false;
	}

	return success;
}


bool Texture::Lock() {
	//Lock the texture for editting

	bool success = true;

	if ( mPixels == (GLubyte*)NULL && mID ) {

		GLuint size = mTexWidth * mTexHeight * mPixelSize;
		mPixels = new GLubyte[size];

		glBindTexture( GL_TEXTURE_2D, mID );
		glGetTexImage( GL_TEXTURE_2D, 0, mPixelFormat, GL_UNSIGNED_BYTE, mPixels );

		glBindTexture( GL_TEXTURE_2D, (GLuint)NULL );

	} else {
		//Some error code: TEXTURE_PIXEL_DATA_NOT_FOUND
		printf("Lock() failed: TEXTURE_PIXEL_DATA_NOT_FOUND\n");
		success = false;
	}

	return success;
}


bool Texture::Unlock() {
	//Unlock the texture after edits are complete

	bool success = true;

	if ( mPixels && mID ) {

		glBindTexture( GL_TEXTURE_2D, mID );
		glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, mTexWidth, mTexHeight, mPixelFormat, GL_UNSIGNED_BYTE, mPixels );
		
		delete[] mPixels;
		mPixels = (GLubyte*)NULL;

		glBindTexture( GL_TEXTURE_2D, (GLuint)NULL );

	} else {
		//Some error code: TEXTURE_PIXEL_DATA_NOT_FOUND
		printf("Unlock() failed: TEXTURE_PIXEL_DATA_NOT_FOUND\n");
		success = false;
	}

	return success;
}


////////////////////////////////////
//			   PUBLIC			  //
////////////////////////////////////
Texture::Texture( GLuint pixelFormat ) {
	//Texture constructor with pixel format

	mID = 0;

	mPixels = (GLubyte*)NULL;

	if ( pixelFormat == TEX_ALPHA || pixelFormat == TEX_RGBA ) {
		
		mPixelSize = pixelFormat;

		if ( mPixelFormat == TEX_ALPHA ) {
			mPixelFormat = GL_ALPHA;
		} else if ( mPixelFormat == TEX_RGBA ) {
			mPixelFormat = GL_RGBA;
		}
	
	} else {

		mPixelFormat = GL_RGBA;
		mPixelSize = TEX_RGBA;

	}

	mImgWidth  = 0;
	mImgHeight = 0;

	mTexWidth  = 0;
	mTexHeight = 0;

	mVBOID = 0;
	mIBOID = 0;
}


Texture::~Texture() {
	//Default texture destructor

	FreeTexture();
	FreeVBO();
}


bool Texture::LoadFromFile( std::string path, GLuint pixelFormat ) {
	//Load texture data from a file

	bool success = false;

	ILuint imgID = 0;
	ilGenImages( 1, &imgID );
	ilBindImage( imgID );

	ILboolean loadSuccess = ilLoadImage( path.c_str() );

	if ( loadSuccess == IL_TRUE ) {

		if ( mPixelFormat == GL_ALPHA ) {
			loadSuccess = ilConvertImage( IL_LUMINANCE, IL_UNSIGNED_BYTE );
		} else if ( mPixelFormat == GL_RGBA ) {
			loadSuccess = ilConvertImage( IL_RGBA, IL_UNSIGNED_BYTE );
		} else {
			loadSuccess = false;
		}

		if ( loadSuccess == IL_TRUE ) {

			GLuint imgWidth = (GLuint)ilGetInteger( IL_IMAGE_WIDTH );
			GLuint imgHeight = (GLuint)ilGetInteger( IL_IMAGE_HEIGHT );

			GLuint texWidth = CalcTexturePadding( imgWidth );
			GLuint texHeight = CalcTexturePadding( imgHeight );

			if ( imgWidth != texWidth || imgHeight != texHeight ) {

				iluImageParameter( ILU_PLACEMENT, ILU_UPPER_LEFT );
				iluEnlargeCanvas( (int)texWidth, (int)texHeight, 1 );

			}

			success = LoadFromPixels( (GLubyte*)ilGetData(), imgWidth, imgHeight, mPixelFormat );

		} else {
			//Some error code: TEXTURE_IMAGE_CONVERT_ERROR
			printf("LoadFromFile() failed: TEXTURE_IMAGE_CONVERT_ERROR\n");
		}

		ilDeleteImages( 1, &imgID );

	} else {
		//Some error code: TEXTURE_IMAGE_LOAD_ERROR
		printf("LoadFromFile() failed: TEXTURE_IMAGE_LOAD_ERROR\n");
	}

	return success;
}


// bool Texture::LoadFromPixels() {
// 	//Load texture data from member pixel array

// 	bool success = true;

// 	if ( ( mID == 0 ) && ( mPixels != (GLubyte*)NULL ) ) {

// 		glGenTextures( 1, &mID );
// 		glBindTexture( GL_TEXTURE_2D, mID );

// 		glTexImage2D( GL_TEXTURE_2D, 0, mPixelFormat, mTexWidth, mTexHeight, 0, mPixelFormat, GL_UNSIGNED_BYTE, mPixels );

// 		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
// 		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
// 		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
// 		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

// 		glBindTexture( GL_TEXTURE_2D, (GLuint)NULL );

// 		GLenum  error = glGetError();

// 		if ( error == GL_NO_ERROR ) {

// 			delete[] mPixels;
// 			mPixels = (GLubyte*)NULL;

// 			InitVBO();

// 		} else {
// 			//Some error code: TEXTURE_GENERATE_FAILED
// 			printf("Error: %d\nmPixelFormat = %d\nmTexWidth = %d\tmTexHeight = %d\nmImgWidth = %d\tnImgHeight = %d", error, mPixelFormat, mTexWidth, mTexHeight, mImgWidth, mImgHeight );
// 			success = false;
// 		}

// 	} else {
		
// 		if ( mID != 0 ) {
// 			//Some error code: TEXTURE_ALREADY_LOADED
// 			printf("ERROR: TEXTURE_ALREADY_LOADED\n");
// 		} else if ( mPixels == (GLubyte*)NULL ) {
// 			//TEXTURE_PIXEL_DATA_NOT_FOUND
// 			printf("ERROR: TEXTURE_PIXEL_DATA_NOT_FOUND\n");
// 		}

// 		success = false;
// 	}

// 	return success;
// }


bool Texture::LoadFromPixels( GLubyte* pixels, GLuint imgWidth, GLuint imgHeight, GLuint pixelFormat ) {
	//Load texture data from given pixel array

	bool success = true;

	if ( imgWidth > 0 && imgHeight > 0 ) {

		mImgWidth = imgWidth;
		mImgHeight = imgHeight;
		mTexWidth = imgWidth;
		mTexHeight = imgHeight;

		glGenTextures( 1, &mID );
		glBindTexture( GL_TEXTURE_2D, mID );

		glTexImage2D( GL_TEXTURE_2D, 0, mPixelFormat, mTexWidth, mTexHeight, 0, mPixelFormat, GL_UNSIGNED_BYTE, pixels );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

		glBindTexture( GL_TEXTURE_2D, (GLuint)NULL );

		PadPixels();

		GLenum error = glGetError();

		if ( error == GL_NO_ERROR ) {

			InitVBO();

		} else {
			//Some error code: TEXTURE_IMAGE_GENERATE_FAILED
			printf("LoadFromPixels() failed: TEXTURE_IMAGE_GENERATE_FAILED\n");
		}
	} else {
		//Some error code: TEXTURE_IMAGE_SIZE_ZERO
		printf("LoadFromPixels() failed: TEXTURE_IMAGE_SIZE_ZERO\n");
	}

	return success;
}


bool Texture::CreatePixels( GLuint imgWidth, GLuint imgHeight, GLuint pixelFormat ) {
	//Clears and allocates new data to member pixels

	bool success = SetPixelData( NULL, imgWidth, imgHeight, pixelFormat );

	return success;

}


bool Texture::PadPixels() {
	//Pads a given non-power-of-two texture to a power of two

	bool success = true;

	Lock();

	if ( mPixels != (GLubyte*)NULL ) {

		GLuint oldTexWidth = mTexWidth;

		mTexWidth = CalcTexturePadding( mImgWidth );
		mTexHeight = CalcTexturePadding( mImgHeight );

		if ( mTexWidth != mImgWidth || mTexHeight != mImgHeight ) {

			GLuint size = mTexWidth * mTexHeight * mPixelSize;

			GLubyte* newPixels = new GLubyte[size];

			for ( unsigned int i = 0; i < mImgHeight; ++i ) {
				
				memcpy( &newPixels[ ( i * mTexWidth ) * mPixelSize ], &mPixels[ ( i * oldTexWidth ) * mPixelSize ], mImgWidth * mPixelSize );

			}

			delete[] mPixels;
			mPixels = newPixels;

		}

	} else {
		//Some error code: TEXTURE_PIXEL_DATA_NOT_FOUND
		printf("PadPixels() failed: TEXTURE_PIXEL_DATA_NOT_FOUND\n");
		success = false;
	}

	Unlock();

	return success;
}


bool Texture::BlitPixels( GLuint x, GLuint y, Texture& destination ) {
	//Copies pixel data of member texture to coordinates on given texture

	bool success = true;

	Lock();

	if ( mPixels && destination.mPixels ) {

		GLubyte* dstPixels = destination.mPixels;
		GLubyte* srcPixels = mPixels;

		for ( GLuint i = 0; i < mImgHeight; ++i ) {
			
			memcpy( &dstPixels[ ( ( ( i + y ) * destination.mTexWidth ) + x ) * destination.mPixelSize ], &srcPixels[ ( i * mTexWidth ) * mPixelSize ], mImgWidth * mPixelSize );
		}

	} else {
		//Some error code: TEXTURE_PIXEL_DATA_NOT_FOUND
		success = false;
	}

	Unlock();

	return success;
}


bool Texture::Render( GLfloat x, GLfloat y, GLfloat w, GLfloat h, Clip* clip ) {
	//Renders the texture to the screen according to given coordinates and bounding clip

	bool success = true;

	if ( mID ) {

		GLfloat texTop  = 0.f;
		GLfloat texLeft = 0.f;
		GLfloat texBottom = (GLfloat)mImgHeight / (GLfloat)mTexHeight;
		GLfloat texRight  = (GLfloat)mImgWidth  / (GLfloat)mTexWidth;

		GLfloat clipWidth  = w;
		GLfloat clipHeight = h;

		if ( clip ) {

			texTop  = clip->y / mTexHeight;
			texLeft = clip->x / mTexWidth;
			texBottom = ( clip->y + clip->h ) / mTexHeight;
			texRight  = ( clip->x + clip->w ) / mTexWidth;

		}

		VertexData2D vData[4];

		vData[0].tPos.s = texLeft;  vData[0].tPos.t = texTop;
		vData[1].tPos.s = texRight; vData[1].tPos.t = texTop;
		vData[2].tPos.s = texRight; vData[2].tPos.t = texBottom;
		vData[3].tPos.s = texLeft;  vData[3].tPos.t = texBottom;

		vData[0].vPos.x = 0.f; 		 vData[0].vPos.y = 0.f;
		vData[1].vPos.x = clipWidth; vData[1].vPos.y = 0.f;
		vData[2].vPos.x = clipWidth; vData[2].vPos.y = clipHeight;
		vData[3].vPos.x = 0.f; 		 vData[3].vPos.y = clipHeight;

		glTranslatef( x, y, 0.f );
		glBindTexture( GL_TEXTURE_2D, mID );

		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );

			glBindBuffer( GL_ARRAY_BUFFER, mVBOID );
			glBufferSubData( GL_ARRAY_BUFFER, 0, 4 * sizeof( VertexData2D ), vData );

			glTexCoordPointer( 2, GL_FLOAT, sizeof( VertexData2D ), (GLvoid*)offsetof( VertexData2D, tPos ) );
			glVertexPointer( 2, GL_FLOAT, sizeof( VertexData2D ), (GLvoid*)offsetof( VertexData2D, vPos ) );

			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mIBOID );
			glDrawElements( GL_QUADS, 4, GL_UNSIGNED_INT, NULL );

		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
		glDisableClientState( GL_VERTEX_ARRAY );

	} else {
		//Some error code: TEXTURE_DOES_NOT_EXIST
		printf("Render() failed: TEXTURE_DOES_NOT_EXIST\n");
		success = false;
	}

	return success;
}


void Texture::SetColorKey( GLubyte r, GLubyte g, GLubyte b, GLubyte a ) {
	//Load 32-bit texture data from a file with given colour key

	if ( mPixelFormat == GL_RGBA ) {

		Lock();

		GLuint size = mImgWidth * mImgHeight * mPixelSize;

		for ( unsigned int i = 0; i <= size; ++i ) {

			GLubyte* rgba = mPixels;

			if ( rgba[i+3] == r && rgba[i+2] == g && rgba[i+1] == b && ( 0x00 == a || rgba[i+0] == a ) ) {

				rgba[i+0] = 0x00;
				rgba[i+1] = 0x00;
				rgba[i+2] = 0x00;
				rgba[i+3] = 0x00;
			}
		}

		Unlock();
	}
}


void Texture::FreeTexture() {
	//Free the texture data

	if ( mID ) {

		glDeleteTextures( 1, &mID );
		mID = 0;
	}

	delete[] mPixels;
	mPixels = (GLubyte*)NULL;

	mImgWidth = 0;
	mImgHeight = 0;
	mTexWidth = 0;
	mTexHeight = 0;

	mPixelFormat = (GLuint)NULL;
	mPixelSize = 0;
}


/*********** MUTATORS ***********/
bool Texture::SetPixelData( GLubyte* pixels, GLuint imgWidth, GLuint imgHeight, GLuint pixelFormat ) {
	//Sets the member pixels to given pixel data, and updates dimensions

	bool success = true;

	if ( imgWidth > 0 && imgHeight > 0 ) {

		FreeTexture();
		SetPixelFormat( pixelFormat );

		GLuint size = imgWidth * imgHeight * mPixelSize;
		mPixels = new GLubyte[size];

		if ( pixels == (GLubyte*)NULL ) {
			memset( mPixels, 0, size );
		} else {
			memcpy( mPixels, pixels, size );
		}

		mImgWidth = imgWidth;
		mImgHeight = imgHeight;
		mTexWidth = mImgWidth;
		mTexHeight = mImgHeight;

	} else {
		success = false;
		printf("SetPixelData() failed: TEXTURE_IMAGE_SIZE_ZERO\n");
		//Some error code: TEXTURE_IMAGE_SIZE_ZERO
	}

	return success;
}


bool Texture::SetPixel( GLuint x, GLuint y, GLuint pixel ) {
	//Sets individual pixel data for a given location

	bool success = true;
	GLubyte apixel = 0;

	Lock();

	if ( x <= mImgWidth && y <= mImgHeight ) {

		if ( mPixelFormat == GL_ALPHA ) {
			apixel = pixel & 0xff;
			mPixels[ ( ( mImgWidth * y ) + x ) * mPixelSize ] = apixel;
		} else if ( mPixelFormat == GL_RGBA ) {
			GLuint* tempPix = (GLuint*)mPixels;
			tempPix[ ( mImgWidth * y ) + x ] = pixel;
		}
	} else {
		success = false;
		printf("SetPixel() failed: TEXTURE_DIMENSION_OUT_OF_BOUNDS\n");
		//Some error code: TEXTURE_DIMENSION_OUT_OF_BOUNDS
	}

	Unlock();

	return success;
}


bool Texture::SetPixelFormat( GLuint pixelFormat ) {

	bool success = true;
	
	if ( pixelFormat == GL_ALPHA || pixelFormat == GL_RGBA ) {
		mPixelFormat = pixelFormat;

		if ( mPixelFormat == GL_ALPHA ) {
			mPixelSize = TEX_ALPHA;
		} else if ( mPixelFormat == GL_RGBA ) {
			mPixelSize = TEX_RGBA;
		}

	} else {
		printf("SetPixelFormat() failed: TEXTURE_FORMAT_INVALID\n");
		success = false;
	}

	return success;
}


void Texture::FlipVert() {

	GLuint size = mImgWidth * mImgHeight * mPixelSize;
	GLubyte* pixels = new GLubyte[size];

	Lock();

	for ( GLuint y = mImgHeight; y >= 1; --y ) {

		memcpy( &pixels[ ( ( mImgHeight-y ) * mImgWidth ) * mPixelSize ], &mPixels[ ( (y-1) * mImgWidth ) * mPixelSize ], mImgWidth * mPixelSize );
	}	//end for

	delete[] mPixels;
	mPixels = pixels;

	Unlock();
}


void Texture::FlipHori() {

	GLuint size = mImgWidth * mImgHeight * mPixelSize;
	GLuint pixCtr = 0;
	GLubyte*   apixels = new GLubyte[size];

	Lock();

	GLuint*     pixels = (GLuint*)apixels;
	GLuint* rgbaPixels = (GLuint*)mPixels;

	for ( GLuint y = 0; y < mImgHeight; ++y ) {

		for ( GLuint x = mImgWidth; x >= 1; --x ) {

			if ( mPixelFormat == GL_ALPHA ) {
				apixels[ pixCtr ] = mPixels[ ( y * mImgWidth ) + x-1 ];
			} else if ( mPixelFormat == GL_RGBA ) {
				pixels[ pixCtr ] = rgbaPixels[ ( y * mImgWidth ) + x-1 ];
			}

			pixCtr++;
		}
	}

	delete[] mPixels;
	
	if ( mPixelFormat == GL_ALPHA ) {
		mPixels = apixels;
	} else if ( mPixelFormat == GL_RGBA ) {
		mPixels = (GLubyte*)pixels;
	}

	Unlock();
}


void Texture::ShiftPixelsRight( GLuint cols ) {
	/////////////////////////////
}


void Texture::ShiftPixelsLeft( GLuint cols ) {
	/////////////////////////////
}


void Texture::ShiftPixelsUp( GLuint rows ) {
	/////////////////////////////
}


void Texture::ShiftPixelsDown(GLuint rows ) {
	/////////////////////////////
}


/*********** ACCESSORS ***********/
const GLubyte* Texture::GetPixelData() const {
	//Retrieves 32-bit pixel data

	return mPixels;
}


const GLubyte Texture::GetAlpha( GLuint x, GLuint y ) {

	GLubyte pixel = 0;

	Lock();

	if ( mPixelFormat == GL_ALPHA ) {

		if ( x <= mImgWidth && y <= mImgHeight ) {

			pixel = mPixels[ ( mTexWidth * y ) + x ];

		} else {
			//Some error code: TEXTURE_DIMENSION_OUT_OF_BOUNDS
			printf("GetAlpha() failed: TEXTURE_DIMENSION_OUT_OF_BOUNDS\n");
		}

	} else {
		// ERROR: INCORRECT PIXEL FORMAT
		printf("GetAlpha() failed: INCORRECT_PIXEL_FORMAT\n");
	}

	Unlock();

	return pixel;
}


const GLuint Texture::GetPixel( GLuint x, GLuint y ) {
	//Retrieves 32-bit pixel data

	Lock();

	GLuint pixel = 0;
	GLuint* pixelPtr = (GLuint*)mPixels;

	if ( mPixelFormat == GL_RGBA ) {

		if ( x <= mImgWidth && y <= mImgHeight ) {

			pixel = pixelPtr[ ( mImgWidth * y ) + x ];
			
		} else {
			//Some error code: TEXTURE_DIMENSION_OUT_OF_BOUNDS
			printf("GetPixel() failed: TEXTURE_DIMENSION_OUT_OF_BOUNDS\n");
		}

	} else {
		//ERROR: INCORRECT PIXEL FORMAT
		printf("GetPixel() failed: INCORRECT_PIXEL_FORMAT\n");
	}

	Unlock();

	return pixel;
}


const GLuint Texture::GetID() const {
	//Retrieves Texture ID

	return mID;
}


const GLuint Texture::GetPixelFormat() const {
	
	return mPixelFormat;
}


const GLuint Texture::GetTextureWidth() const {
	//Retrieves Texture width

	return mTexWidth;
}


const GLuint Texture::GetTextureHeight() const {
	//Retrieves Texture Height

	return mTexHeight;
}


const GLuint Texture::GetImageWidth() const {
	//Retrieves Image width

	return mImgWidth;
}


const GLuint Texture::GetImageHeight() const {
	//Retrieves Image height

	return mImgHeight;
}