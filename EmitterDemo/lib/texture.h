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

public:
	/***********   Methods  ***********/
	Texture( GLuint pixelFormat = TEX_RGBA );
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

	virtual void FreeTexture( void );
	//Free the texture data
	//Parameters:
	//	N/A
	//Returns:
	//	N/A

	bool LoadFromFile( std::string path, GLuint pixelFormat = TEX_RGBA );
	//Load texture data from a file
	//Parameters:
	//	std::string path:	texture file path
	//Returns:
	//	bool:	Load successful

	bool LoadFromPixels( GLubyte* pixels, GLuint imgWidth, GLuint imgHeight, GLuint pixelFormat = TEX_RGBA );
	//Load texture data from given pixel array
	//Parameters:
	//	GLubyte* pixels	: Pixel data
	//	GLuint imgWidth : image width
	//	GLuint imgHeight: image height
	//Returns:
	//	bool:	Load successful

	bool CreatePixels( GLuint imgWidth, GLuint imgHeight, GLuint pixelFormat = TEX_RGBA );
	//Clears and allocates new data to member pixels
	//Parameters:
	//	GLuint imgWidth : image width
	//	GLuint imgHeight: image height
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

	bool PadPixels( void );

	bool Render( GLfloat x, GLfloat y, GLfloat w = SCREEN_WIDTH, GLfloat h = SCREEN_HEIGHT, Clip* clip = NULL );
	//Renders the texture to the screen according to given coordinates and bounding clip
	//Parameters:
	//	GLfloat x : X-coordinate to begin rendering
	//	GLfloat y : Y-coordinate to begin rendering
	//	GLfloat w : Width to be rendered to
	//	GLfloat h : Height to be rendered to
	//	Clip* clip: Portion of texture to be rendered
	//Returns:
	//	bool: Load successful

	/*********** MUTATORS ***********/
	void SetColorKey( GLubyte r, GLubyte g, GLubyte b, GLubyte a = 0xFF );
	//Sets the colour key for the given texture
	//Parameters:
	//	GLubyte r: Red component of colour key
	//	GLubyte g: Green component of colour key
	//	GLubyte b: Blue component of colour key
	//Returns:
	//	bool: Load successful

	bool SetPixelData( GLubyte* pixels, GLuint imgWidth, GLuint imgHeight, GLuint pixelFormat = TEX_RGBA );
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
	//Sets the pixel format for the texture
	//Parameters:
	//	GLuint pixelFormat: The pixel format of the texture
	//Returns:
	//	bool: Load successful

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
	//Shifts pixel data right by the number of columns specified
	//Parameters:
	//	GLuint cols: The number of columns to shift
	//Returns:
	//	N/A

	void ShiftPixelsLeft( GLuint cols = 1 );
	//Shifts pixel data left by the number of columns specified
	//Parameters:
	//	GLuint cols: The number of columns to shift
	//Returns:
	//	N/A

	void ShiftPixelsUp( GLuint rows = 1 );
	//Shifts pixel data up by the number of rows specified
	//Parameters:
	//	GLuint rows: The number of rows to shift
	//Returns:
	//	N/A

	void ShiftPixelsDown( GLuint rows = 1 );
	//Shifts pixel data down by the number of rows specified
	//Parameters:
	//	GLuint rows: The number of rows to shift
	//Returns:
	//	N/A

	/*********** ACCESSORS ***********/
	const GLubyte* GetPixelData( void ) const;
	//Retrieves 8-bit pixel data
	//Parameters:
	//	N/A
	//Returns:
	//	GLubyte*: 8-bit pixel data

	const GLubyte GetAlpha( GLuint x, GLuint y );
	//Retrieves 8-bit pixel data
	//Parameters:
	//	GLuint x: X-coordinate of requested pixel
	//	GLuint y: Y-coordinate of requested pixel
	//Returns:
	//	GLuint: Requested pixel data

	const GLuint GetPixel( GLuint x, GLuint y );
	//Retrieves 32-bit pixel data
	//Parameters:
	//	GLuint x: X-coordinate of requested pixel
	//	GLuint y: Y-coordinate of requested pixel
	//Returns:
	//	GLubyte: Requested pixel data

	const GLuint GetID( void ) const;
	//Retrieves Texture ID
	//Parameters:
	//	N/A
	//Returns:
	//	GLuint: Texture ID

	const GLuint GetPixelFormat( void ) const;
	//Retrieves pixel format for the given texture
	//Parameters:
	//	N/A
	//Returns:
	//	GLuint: Pixel format

	const GLuint GetTextureWidth( void ) const;
	//Retrieves Texture width
	//Parameters:
	//	N/A
	//Returns:
	//	GLuint: Texture width

	const GLuint GetTextureHeight( void ) const;
	//Retrieves Texture Height
	//Parameters:
	//	N/A
	//Returns:
	//	GLuint: Texture Height

	const GLuint GetImageWidth( void ) const;
	//Retrieves Image width
	//Parameters:
	//	N/A
	//Returns:
	//	GLuint: Image width

	const GLuint GetImageHeight( void ) const;
	//Retrieves Image height
	//Parameters:
	//	N/A
	//Returns:
	//	GLuint: Image height

};


#endif