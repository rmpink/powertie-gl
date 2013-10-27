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

#ifndef COLLISION_MASK_H
#define COLLISION_MASK_H

#include "mask.h"


class CollisionMask : Mask {

private:
	/* Attributes */
	GLuint mWidth;
	GLuint mHeight;

	GLubyte* mPixels;

	/*   Methods  */

protected:
	/* Attributes */
	/*   Methods  */

public:
	/* Attributes */
	/*   Methods  */
	CollisionMask( void );

	CollisionMask( GLuint w, GLuint h );

	~CollisionMask( void );

	void Add( Clip newclip );

	void Erase( Clip newclip );

	bool Touch( GLuint x, GLuint y, GLuint w = 0, GLuint h = 0 );

	void Clear( void );

	bool SetWidth( GLuint w );

	bool SetHeight( GLuint h );

	GLuint GetWidth( void );

	GLuint GetHeight( void );

	GLubyte* GetPixelData( void ) const;
};


#endif