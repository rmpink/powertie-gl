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

#ifndef CONST_H
#define CONST_H

#include "clip.h"


const float PART_SIZE =   1.f;
const float WIND      =   0.f;
const float GRAVITY   =   9.81f;

const float MAX_WIND  =   5.f;
const float MAX_GRAV  =  18.f;
const float MIN_GRAV  =   1.f;

const float TERM_VEL  = 16.f;


//Screen Constants
const unsigned int SCREEN_WIDTH  = 1280;
const unsigned int SCREEN_HEIGHT =  800;
const unsigned int SCREEN_FPS	 =   60;

const char WINDOW_TITLE[] = "Some Physics";

const unsigned int SPRITE_ROWS = 8;
const unsigned int SPRITE_COLS = 8;

const unsigned int TEX_RGBA  = 4;
const unsigned int TEX_ALPHA = 1;

//Font Cell Dimension Constants
const unsigned int FONT_CELL_ROWS = 16;
const unsigned int FONT_CELL_COLS = 16;

//Black Pixel Value Constant
const unsigned int FONT_BLACK_PIXEL = 0x00;

//Sprite Origin Constants
enum SpriteOrigin {

	SPRITE_ORIGIN_CENTER,
	SPRITE_ORIGIN_TOP_LEFT,
	SPRITE_ORIGIN_BOTTOM_LEFT,
	SPRITE_ORIGIN_TOP_RIGHT,
	SPRITE_ORIGIN_BOTTOM_RIGHT

};

//Font Alignment Constants
enum FontAlignment {

	FONT_ALIGN_LEFT   =  1,	// BIN 0000 0001
	FONT_ALIGN_CENTER =  2,	// BIN 0000 0010
	FONT_ALIGN_RIGHT  =  4, // BIN 0000 0100
	FONT_ALIGN_TOP	  =  8, // BIN 0000 1000
	FONT_ALIGN_MIDDLE = 16, // BIN 0001 0000
	FONT_ALIGN_BOTTOM = 32  // BIN 0010 0000

};


#endif