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

#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include <vector>
#include "texture.h"
#include "const.h"
#include "vertexData2D.h"


class SpriteSheet : public Texture {

private:
	/* Attributes */
	std::vector<Clip> mClips;

	GLuint mVBOID;
	GLuint* mIBOIDs;

	/*   Methods  */

protected:
	/* Attributes */
	/*   Methods  */

public:
	/* Attributes */
	/*   Methods  */
	SpriteSheet( void );
	//Default sprite sheet constructor
	//Parameters:
	//	N/A
	//Returns:
	//	N/A

	~SpriteSheet( void );
	//Default sprite sheet destructor
	//Parameters:
	//	N/A
	//Returns:
	//	N/A

	int AddSprite( Clip& newClip );
	//Adds sprite clip to sprite array, and returns the index
	//Parameters:
	//	QuadClip& newClip: The clip bounds of the new sprite
	//Returns:
	//	N/A

	bool GenerateVBO( SpriteOrigin origin = SPRITE_ORIGIN_CENTER );
	//Generates VBO and IBOs for rendering sprites
	//Parameters:
	//	SpriteOrigin origin: Location on the sprite to begin render from
	//Returns:
	//	bool: Generation success

	void FreeSheet( void );
	//Deallocates VBO, IBOs, and sprite array
	//Parameters:
	//	N/A
	//Returns:
	//	N/A

	void FreeTexture( void );
	//Deallocates sprite sheet data and base texture data
	//Parameters:
	//	N/A
	//Returns:
	//	N/A

	bool Render( int index );
	//Renders sprite at given index in sprite array
	//Parameters:
	//	int index: Array index of sprite to be rendered
	//Returns:
	//	bool: Render successful

	bool SetClipX( int index, GLfloat x );
	//Sets the x of clip at given index to the value given
	//Parameters:
	//	int index: index of clip to modify
	//	GLuint x : value to change
	//Returns:
	//	bool: successful

	bool SetClipY( int index, GLfloat y );
	//Sets the y of clip at given index to the value given
	//Parameters:
	//	int index: index of clip to modify
	//	GLuint y : value to change
	//Returns:
	//	bool: successful

	bool SetClipWidth( int index, GLfloat width );
	//Sets the w of clip at given index to the value given
	//Parameters:
	//	int index: index of clip to modify
	//	GLuint w : value to change
	//Returns:
	//	bool: successful

	bool SetClipHeight( int index, GLfloat height );
	//Sets the h of clip at given index to the value given
	//Parameters:
	//	int index: index of clip to modify
	//	GLuint h : value to change
	//Returns:
	//	bool: successful

	// void FlipSpritesHori( void );


	// void FlipSpritesVert( void );


	Clip GetClip( int index );
	//Retrieves Clip struct of clip at given index
	//Parameters:
	//	int index: Array index of clip to be returned
	//Returns:
	//	Clip: clip struct at requested index

	GLuint GetVBOID( void );


	GLuint* GetIBOIDs( void );

};


#endif