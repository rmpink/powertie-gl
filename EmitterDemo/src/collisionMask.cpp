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

#include "../lib/collisionMask.h"


CollisionMask::CollisionMask() {

	mWidth = 0;
	mHeight = 0;

	mPixels = (GLubyte*)NULL;
}


CollisionMask::CollisionMask( GLuint w, GLuint h ) {

	mWidth = w;
	mHeight = h;

	mPixels = new GLubyte[ w*h ];
}


CollisionMask::~CollisionMask() {

	Clear();
}


void CollisionMask::Add( Clip newclip ) {

	for ( GLuint x = (GLuint)newclip.x; x < (GLuint)(newclip.x + newclip.w) && x < mWidth; ++x ) {

		for ( GLuint y = (GLuint)newclip.y; y < (GLuint)(newclip.y + newclip.h) && y < mHeight; ++y ) {

			mPixels[ (y*mWidth) + x ] = 0xFF;
		}
	}
}


void CollisionMask::Erase( Clip newclip ) {

	for ( GLuint x = (GLuint)newclip.x; x < (GLuint)(newclip.x + newclip.w) && x < mWidth; ++x ) {

		for ( GLuint y = (GLuint)newclip.y; y < (GLuint)(newclip.y + newclip.h) && y < mHeight; ++y ) {

			mPixels[ (y*mWidth) + x ] = 0x00;
		}
	}
}


bool CollisionMask::Touch( GLuint x, GLuint y, GLuint w, GLuint h ) {

	bool success = false;

	if ( (x <= mWidth) && (x >= 0) && (y <= mHeight) && (y >= 0) && (mPixels[ (y*mWidth) + x ] == 0xFF) ) {
		
		success = true;
	}

	return success;
}


void CollisionMask::Clear() {

	mWidth = 0;
	mHeight = 0;

	delete[] mPixels;

	mPixels = (GLubyte*)NULL;
}


bool CollisionMask::SetWidth( GLuint w ) {

	mWidth = w;

	return true;
	// Needs to be modified to adjust pixel data
}


bool CollisionMask::SetHeight( GLuint h ) {

	mHeight = h;

	return true;
	// Needs to be modified to adjust pixel data
}


GLuint CollisionMask::GetWidth() {

	return mWidth;
}


GLuint CollisionMask::GetHeight() {

	return mHeight;
}


GLubyte* CollisionMask::GetPixelData() const {

	return mPixels;
}