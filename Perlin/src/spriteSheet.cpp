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

#include "../lib/spriteSheet.h"


////////////////////////////////////
//			   PUBLIC			  //
////////////////////////////////////
SpriteSheet::SpriteSheet() {
	//Default sprite sheet constructor

	mVBOID = 0;
	mIBOIDs = 0;

}


SpriteSheet::~SpriteSheet() {
	//Default sprite sheet destructor

	FreeSheet();

}


int SpriteSheet::AddSprite( Clip& newClip ) {
	//Adds sprite clip to sprite array, and returns the index

	//printf("SpriteSheet::AddSprite()\n");

	mClips.push_back( newClip );
	return mClips.size() - 1;

}


bool SpriteSheet::GenerateVBO( SpriteOrigin origin ) {
	//Generates VBO and IBOs for rendering sprites

	bool success = true;

	if ( GetID() && mClips.size() ) {

		VertexData2D* vData = new VertexData2D[ mClips.size() * 4 ];
		mIBOIDs 			= new GLuint[ mClips.size() ];

		glGenBuffers( 1, &mVBOID );
		glGenBuffers( mClips.size(), mIBOIDs );

		GLfloat texWidth = GetTextureWidth();
		GLfloat texHeight = GetTextureHeight();
		GLuint iData[4] = { 0 };

		GLfloat vTop = 0.f;
		GLfloat vLeft = 0.f;
		GLfloat vBottom = 0.f;
		GLfloat vRight = 0.f;

		for ( unsigned int i = 0; i < mClips.size(); ++i ) {

			iData[0] = ( i * 4 ) + 0;
			iData[1] = ( i * 4 ) + 1;
			iData[2] = ( i * 4 ) + 2;
			iData[3] = ( i * 4 ) + 3;

			switch( origin ) {
				case SPRITE_ORIGIN_CENTER:
					vTop  	= -mClips[i].h / 2;
					vLeft 	= -mClips[i].w / 2;
					vBottom =  mClips[i].h / 2;
					vRight  =  mClips[i].w / 2;

					break;
				case SPRITE_ORIGIN_TOP_LEFT:
					vTop  	=  0.f;
					vLeft 	=  0.f;
					vBottom =  mClips[i].h;
					vRight  =  mClips[i].w;

					break;
				case SPRITE_ORIGIN_BOTTOM_LEFT:
					vTop  	= -mClips[i].h;
					vLeft 	=  0.f;
					vBottom =  0.f;
					vRight  =  mClips[i].w;

					break;
				case SPRITE_ORIGIN_TOP_RIGHT:
					vTop  	=  0.f;
					vLeft 	= -mClips[i].w;
					vBottom =  mClips[i].h;
					vRight  =  0.f;

					break;
				case SPRITE_ORIGIN_BOTTOM_RIGHT:
					vTop  	= -mClips[i].h;
					vLeft 	= -mClips[i].w;
					vBottom =  0.f;
					vRight  =  0.f;

					break;
			}

			// Top left corner
			vData[ iData[0] ].tPos.s = ( mClips[i].x ) / texWidth;
			vData[ iData[0] ].tPos.t = ( mClips[i].y ) / texHeight;
			vData[ iData[0] ].vPos.x = vLeft;  vData[ iData[0] ].vPos.y = vTop;
			
			//Top right corner
			vData[ iData[1] ].tPos.s = ( mClips[i].x + mClips[i].w ) / texWidth;
			vData[ iData[1] ].tPos.t = ( mClips[i].y ) / texHeight;
			vData[ iData[1] ].vPos.x = vRight; vData[ iData[1] ].vPos.y = vTop;
			
			//Bottom right corner
			vData[ iData[2] ].tPos.s = ( mClips[i].x + mClips[i].w ) / texWidth;
			vData[ iData[2] ].tPos.t = ( mClips[i].y + mClips[i].h ) / texHeight;
			vData[ iData[2] ].vPos.x = vRight; vData[ iData[2] ].vPos.y = vBottom;
			
			//Bottom left corner
			vData[ iData[3] ].tPos.s = ( mClips[i].x ) / texWidth;
			vData[ iData[3] ].tPos.t = ( mClips[i].y + mClips[i].h ) / texHeight;
			vData[ iData[3] ].vPos.x = vLeft;  vData[ iData[3] ].vPos.y = vBottom;

			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mIBOIDs[i] );
			glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof( GLuint ), iData, GL_STATIC_DRAW );

		}

		glBindBuffer( GL_ARRAY_BUFFER, mVBOID );
		glBufferData( GL_ARRAY_BUFFER, mClips.size() * ( 4 * sizeof( VertexData2D ) ), vData, GL_STATIC_DRAW );

		delete[] vData;

	} else {

		if ( !GetID() ) {
			//Some error code: SPRITE_ID_NOT_FOUND
			printf("GenerateVBO: SPRITE_ID_NOT_FOUND\n");
		} else if ( !mClips.size() ) {
			//Some error code: SPRITE_NO_CLIPS_FOUND
			printf("GenerateVBO: SPRITE_NO_CLIPS_FOUND\n");
		}

		success = false;

	}

	return success;

}


void SpriteSheet::FreeSheet() {
	//Deallocates VBO, IBOs, and sprite array

	if ( mVBOID ) {

		glDeleteBuffers( 1, &mVBOID );
		mVBOID = (GLuint)NULL;

	}

	if ( mIBOIDs ) {

		glDeleteBuffers( mClips.size(), mIBOIDs );
		delete[] mIBOIDs;
		mIBOIDs = (GLuint*)NULL;

	}

	mClips.clear();

}


void SpriteSheet::FreeTexture() {
	//Deallocates sprite sheet data and base texture data

	FreeSheet();
	Texture::FreeTexture();

}


bool SpriteSheet::Render( int index ) {
	//Renders sprite at given index in sprite array

	bool success = true;

	if ( mVBOID ) {

		glBindTexture( GL_TEXTURE_2D, GetID() );

		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );

			glBindBuffer( GL_ARRAY_BUFFER, mVBOID );

			glTexCoordPointer( 2, GL_FLOAT, sizeof( VertexData2D ), (GLvoid*)offsetof( VertexData2D, tPos ) );
			glVertexPointer( 2, GL_FLOAT, sizeof( VertexData2D ), (GLvoid*)offsetof( VertexData2D, vPos ) );

			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mIBOIDs[index] );
			glDrawElements( GL_QUADS, 4, GL_UNSIGNED_INT, NULL );

		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
		glDisableClientState( GL_VERTEX_ARRAY );

	} else {
		//Some error code: SPRITE_VBO_DOES_NOT_EXIST
		printf("SPRITE_VBO_DOES_NOT_EXIST\n");
		success = false;
	}

	return success;

}


/*********** MUTATORS ***********/
bool SpriteSheet::SetClipX( int index, GLfloat x ) {

	bool success = true;

	if ( index >= 0 && index < (int)mClips.size() ) {

		mClips[index].x = x;

	} else {
		//Some error code: SPRITESHEET_SET_CLIP_X_FAIL
		success = false;
	}

	return success;

}


bool SpriteSheet::SetClipY( int index, GLfloat y ) {

	bool success = true;

	if ( index >= 0 && index < (int)mClips.size() ) {

		mClips[index].y = y;

	} else {
		//Some error code: SPRITESHEET_SET_CLIP_Y_FAIL
		success = false;
	}

	return success;

}


bool SpriteSheet::SetClipWidth( int index, GLfloat width ) {

	bool success = true;

	if ( index >= 0 && index < (int)mClips.size() ) {

		mClips[index].w = width;

	} else {
		//Some error code: SPRITESHEET_SET_CLIP_W_FAIL
		success = false;
	}

	return success;

}


bool SpriteSheet::SetClipHeight( int index, GLfloat height ) {

	bool success = true;

	if ( index >= 0 && index < (int)mClips.size() ) {

		mClips[index].h = height;

	} else {
		//Some error code: SPRITESHEET_SET_CLIP_H_FAIL
		success = false;
	}

	return success;

}


/*********** ACCESSORS ***********/
Clip SpriteSheet::GetClip( int index ) {
	//Retrieves QuadClip struct of clip at given index

	return mClips[index];

}


GLuint SpriteSheet::GetVBOID() {

	return mVBOID;

}


GLuint* SpriteSheet::GetIBOIDs() {

	return mIBOIDs;

}