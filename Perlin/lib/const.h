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


//Screen Constants
const unsigned int SCREEN_WIDTH  = 512;
const unsigned int SCREEN_HEIGHT = 512;
const unsigned int SCREEN_FPS	 =  32;

const char WINDOW_TITLE[] = "Perlin Noise";

//Sprite Origin Constants
enum SpriteOrigin {

	SPRITE_ORIGIN_CENTER,
	SPRITE_ORIGIN_TOP_LEFT,
	SPRITE_ORIGIN_BOTTOM_LEFT,
	SPRITE_ORIGIN_TOP_RIGHT,
	SPRITE_ORIGIN_BOTTOM_RIGHT

};

const unsigned int SPRITE_ROWS = 8;
const unsigned int SPRITE_COLS = 8;

//Font Alignment Constants
enum FontAlignment {

	FONT_ALIGN_LEFT   =  1,	// BIN 0000 0001
	FONT_ALIGN_CENTER =  2,	// BIN 0000 0010
	FONT_ALIGN_RIGHT  =  4, // BIN 0000 0100
	FONT_ALIGN_TOP	  =  8, // BIN 0000 1000
	FONT_ALIGN_MIDDLE = 16, // BIN 0001 0000
	FONT_ALIGN_BOTTOM = 32  // BIN 0010 0000

};

//Font Cell Dimension Constants
const unsigned int FONT_CELL_ROWS = 16;
const unsigned int FONT_CELL_COLS = 16;

//Black Pixel Value Constant
const unsigned int FONT_BLACK_PIXEL = 0x00;


#endif