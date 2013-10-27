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

#ifndef TEXTURE_H
#define TEXTURE_H

#include "initGL.h"
#include "clip.h"
#include "const.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include <string>


class Texture {

private:
	/*********** Attributes ***********/
	GLuint mID;

	GLubyte* mPixels;

	GLuint  mPixelFormat;
	GLubyte mPixelSize;

	GLuint mTexWidth, mTexHeight;
	GLuint mImgWidth, mImgHeight;

	GLuint mVBOID;
	GLuint mIBOID;

protected:
	/***********   Methods  ***********/
	GLuint CalcTexturePadding( GLuint val );
	//Calculates the padding required for given dimension
	//Parameters:
	//	GLuint val: Integer value to pad
	//Returns:
	//	GLuint: Padded value

	bool InitVBO( void );
	//Generates Virtual and Index Buffer Objects
	//Parameters:
	//	N/A
	//Returns:
	//	bool: Load successful

	bool FreeVBO( void );
	//Free VBO and IBO data buffers
	//Parameters:
	//	N/A
	//Returns:
	//	bool: Load successful

public:
	/***********   Methods  ***********/
	Texture( GLuint pixelFormat = GL_RGBA );
	//Default texture constructor
	//Parameters:
	//	N/A
	//Returns:
	//	N/A

	~Texture( void );
	//Default texture destructor
	//Parameters:
	//	N/A
	//Returns:
	//	N/A

	bool LoadFromFile( std::string path, GLuint pixelFormat = GL_RGBA );
	//Load 8-bit texture data from a file
	//Parameters:
	//	std::string path:	texture file path
	//Returns:
	//	bool:	Load successful

	bool LoadFromPixels( void );
	//Load 8-bit texture data from pixel array
	//Parameters:
	//	N/A
	//Returns:
	//	bool:	Load successful

	bool LoadFromPixels( GLubyte* pixels, GLuint imgWidth, GLuint imgHeight, GLuint texWidth, GLuint texHeight, GLuint pixelFormat = GL_RGBA );
	//Load 8-bit texture data from given pixel array
	//Parameters:
	//	GLubyte* pixels	: Pixel data
	//	GLuint imgWidth : image width
	//	GLuint imgHeight: image height
	//	GLuint texWidth	: texture width (for non-power-of-two textures)
	//	GLuint texHeight: texture height (for non-power-of-two textures)
	//Returns:
	//	bool:	Load successful

	bool CreatePixels( GLuint imgWidth, GLuint imgHeight, GLuint pixelFormat = GL_RGBA );
	//Clears and allocates new data to member pixels
	//Parameters:
	//	GLuint imgWidth : image width
	//	GLuint imgHeight: image height
	//Returns:
	//	bool: Load successful

	bool PadPixels( void );
	//Pads a given non-power-of-two texture to a power of two.
	//Parameters:
	//	N/A
	//Returns:
	//	bool: Load successful

	bool BlitPixels( GLuint x, GLuint y, Texture& destination );
	//Copies pixel data of member texture to coordinates on given texture
	//Parameters:
	//	GLuint x			: X-coordinate to blit
	//	GLuint y			: Y-coordinate to blit
	//	Texture& destination: Texture to blit
	//Returns:
	//	bool: Load successful

	void ColorKey( GLubyte r, GLubyte g, GLubyte b, GLubyte a = 0x00 );

	bool Lock( void );
	//Lock the texture for editting
	//Parameters:
	//	N/A
	//Returns:
	//	bool: Texture data retrieved

	bool Unlock( void );
	//Unlock the texture after edits are complete
	//Parameters:
	//	N/A
	//Returns:
	//	bool: Picture data updated

	bool Render( GLfloat x, GLfloat y, GLfloat w = SCREEN_WIDTH, GLfloat h = SCREEN_HEIGHT, Clip* clip = NULL );
	//Renders the texture to the screen according to given coordinates and bounding clip
	//Parameters:
	//	GLfloat x	  : X-coordinate to begin rendering
	//	GLfloat y	  : Y-coordinate to begin rendering
	//	GLfloat w	  : Width to be rendered to
	//	GLfloat h	  : Height to be rendered to
	//	Clip* clip: Portion of texture to be rendered
	//Returns:
	//	bool: Load successful

	virtual void FreeTexture( void );
	//Free the texture data
	//Parameters:
	//	N/A
	//Returns:
	//	N/A

	/*********** MUTATORS ***********/
	bool SetPixelData( std::string path );
	//Sets the member pixels to data from given file
	//Parameters:
	//	std::string path: path to texture file
	//Returns:
	//	bool: Load successful

	bool SetPixelData( GLubyte* pixels, GLuint imgWidth, GLuint imgHeight, GLuint pixelFormat = GL_RGBA );
	//Sets the member pixels to given pixel data, and updates dimensions
	//Parameters:
	//	GLuint* pixels	: Pixel data
	//	GLuint imgWidth : image width
	//	GLuint imgHeight: image height
	//Returns:
	//	bool: Load successful

	bool SetPixel( GLuint x, GLuint y, GLuint pixel );
	//Sets individual pixel data for a given location
	//Parameters:
	//	GLuint x 	: X-coordinate of pixel to set
	//	GLuint y 	: Y-coordinate of pixel to set
	//	GLuint pixel: Value to set pixel to
	//Returns:
	//	bool: Load successful

	bool SetPixelFormat( GLuint pixelFormat );

	void FlipVert( void );
	//Flips 32-bit texture vertically across X-axis
	//Parameters:
	//	N/A
	//Returns:
	//	N/A

	void FlipHori( void );
	//Flips 32-bit texture horizontally across Y-axis
	//Parameters:
	//	N/A
	//Returns:
	//	N/A

	void ShiftPixelsRight( GLuint cols = 1 );

	void ShiftPixelsLeft( GLuint cols = 1 );

	void ShiftPixelsUp( GLuint rows = 1 );

	void ShiftPixelsDown( GLuint rows = 1 );

	/*********** ACCESSORS ***********/
	GLubyte* GetPixelData( void );
	//Retrieves 8-bit pixel data
	//Parameters:
	//	N/A
	//Returns:
	//	GLubyte*: 8-bit pixel data

	GLubyte GetAlpha( GLuint x, GLuint y );
	//Retrieves 32-bit pixel data
	//Parameters:
	//	GLuint x: X-coordinate of requested pixel
	//	GLuint y: Y-coordinate of requested pixel
	//Returns:
	//	GLuint: Requested pixel data

	GLuint GetPixel( GLuint x, GLuint y );
	//Retrieves 8-bit pixel data
	//Parameters:
	//	GLuint x: X-coordinate of requested pixel
	//	GLuint y: Y-coordinate of requested pixel
	//Returns:
	//	GLubyte: Requested pixel data

	GLuint GetID( void );
	//Retrieves Texture ID
	//Parameters:
	//	N/A
	//Returns:
	//	GLuint: Texture ID

	GLuint GetPixelFormat( void );

	GLuint GetTextureWidth( void );
	//Retrieves Texture width
	//Parameters:
	//	N/A
	//Returns:
	//	GLuint: Texture width

	GLuint GetTextureHeight( void );
	//Retrieves Texture Height
	//Parameters:
	//	N/A
	//Returns:
	//	GLuint: Texture Height

	GLuint GetImageWidth( void );
	//Retrieves Image width
	//Parameters:
	//	N/A
	//Returns:
	//	GLuint: Image width

	GLuint GetImageHeight( void );
	//Retrieves Image height
	//Parameters:
	//	N/A
	//Returns:
	//	GLuint: Image height

};


#endif