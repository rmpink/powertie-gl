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

#ifndef VERTEX_DATA_2D_H
#define VERTEX_DATA_2D_H

#include "initGL.h"



struct VertexCoord {

	GLfloat x, y;

};



struct TextureCoord {

	GLfloat s, t;

};



struct VertexData2D {

	VertexCoord vPos;
	TextureCoord tPos;

};



#endif