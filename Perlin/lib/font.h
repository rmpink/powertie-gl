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

#ifndef FONT_H
#define FONT_H

#include "spriteSheet.h"
#include <ft2build.h>
#include FT_FREETYPE_H


class Font : private SpriteSheet {

private:
	/* Attributes */
	static FT_Library mLibrary;

	GLfloat mSpaceWidth;
	GLfloat mLineHeight;
	GLfloat mNewLine;

	/*   Methods  */
	GLfloat CalcStringWidth( const char* newString );
	//Calculates rendered width of given string
	//Parameters:
	//	const char* newString: String to calculate render width
	//Returns:
	//	GLfloat: String width

	GLfloat CalcStringHeight( const char* newString );
	//Calculates rendered height of given string (for multi-line strings)
	//Parameters:
	//	const char* newString: String to calculate render height
	//Returns:
	//	GLfloat: String height

protected:
	/* Attributes */
	/*   Methods  */

public:
	/* Attributes */
	/*   Methods  */
	static bool InitFreeType( void );
	//Instantiates FreeType library used by Font class
	//Parameters:
	//	N/A
	//Returns:
	//	bool: Initialization success

	Font( void );
	//Default font constructor
	//Parameters:
	//	N/A
	//Returns:
	//	N/A

	~Font( void );
	//Default font destructor
	//Parameters:
	//	N/A
	//Returns:
	//	N/A

	bool LoadFromBitmap( std::string path );
	//Loads a font from a bitmap file
	//Parameters:
	//	std::string path: File path to bitmap
	//Returns:
	//	bool: Load success

	bool LoadFromFile( std::string path, GLuint fontSize = 12 );
	//Loads a font from a font file (using FreeType)
	//Parameters:
	//	std::string path: File path to font
	//	GLuint fontSize : Size of font to load
	//Returns:
	//	bool: Load success

	void FreeFont( void );
	//Deallocates font, sprite sheet, and texture data
	//Parameters:
	//	N/A
	//Returns:
	//	N/A

	bool Render( GLfloat x, GLfloat y, std::string text, Clip* area = NULL, GLuint fontAlign = FONT_ALIGN_LEFT|FONT_ALIGN_TOP );
	//Renders given text inside given area bounding box (if provided)
	//Parameters:
	//	GLfloat x		: X-coordinate to render
	//	GLfloat y		: Y-coordinate to render
	//	std::string text: Text to render to the screen
	//	Clip* area		: Bounding area to render to
	//	GLuint fontAlign: Font alignment to render with
	//Returns:
	//	bool: Render success

	GLfloat GetLineHeight( void );
	//Retrieves member line height
	//Parameters:
	//	N/A
	//Returns:
	//	GLfloat: mLineHeight

	GLfloat GetNewLine( void );
	//Retrieves member newline height
	//Parameters:
	//	N/A
	//Returns:
	//	GLfloat: mNewLine

	GLfloat GetSpaceWidth( void );
	//Retrieves member space width
	//Parameters:
	//	N/A
	//Returns:
	//	GLfloat: mSpaceWidth

	Clip GetStringArea( std::string text );
	//Retrieves minimum bounding area for provided text
	//Parameters:
	//	std::string text: Text to calculate area of
	//Returns:
	//	Clip: Minimum render area for given text

};


#endif