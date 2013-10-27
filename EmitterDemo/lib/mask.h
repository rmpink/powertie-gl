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

#ifndef MASK_H
#define MASK_H

#include "initGL.h"
#include "clip.h"


class Mask {

private:
	/* Attributes */
	/*   Methods  */

protected:
	/* Attributes */
	/*   Methods  */

public:
	/* Attributes */
	/*   Methods  */
	virtual void Add( Clip newclip ) = 0;

	virtual void Erase( Clip newclip ) = 0;

	virtual bool Touch( GLuint x, GLuint y, GLuint w, GLuint h ) = 0;

	virtual void Clear( void ) = 0;
};


#endif