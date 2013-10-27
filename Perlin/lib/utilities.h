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

#ifndef UTILITIES_H
#define UTILITIES_H

#include <IL/il.h>
#include <IL/ilu.h>
#include "initGL.h"


bool initGL( void );
//Initialize the OpenGL graphics library
//Parameters:
//	N/A
//Returns:
//	bool: Initialization success

bool initIL( void );
//Initialize DevIL and DevILU
//Parameters:
//	N/A
//Returns:
//	bool: Initialization success

bool initFreeType( void );
//Initialize FreeType library
//Parameters:
//	N/A
//Returns:
//	bool: Initialization success

bool initGUI( int argc, char* argv[] );
//Initialize the FreeGLUT window library
//Parameters:
//	int argc	:	Passed from main()
//	char* argv[]:	Passed from main()
//Returns:
//	bool: Initialization success

void startGameLoop( void );
//Makes the call to glutMainLoop();

void update( void );
//Update graphic elements before rendering
//Parameters:
//	N/A
//Returns:
//	N/A

void render( void );
//Render updated graphics to the screen
//Parameters:
//	N/A
//Returns:
//	N/A

void runMainLoop( int val = 0 );
//Execute main program loop
//Parameters:
//	int val	:	Frame counter passed to program loop
//Returns:
//	N/A

bool loadAssets( char filepath[] );
//Load all required assets
//Parameters:
//	N/A
//Returns:
//	bool: Load success

void keyPressed( unsigned char key, int x, int y );
//Keyboard key has been pressed
//Parameters:
//	unsigned char key:	ASCII value for key pressed
//	int x			 :	X-coordinate of mouse at keypress
//	int y			 :	Y-coordinate of mouse at keypress
//Returns:
//	N/A

void keyReleased( unsigned char key, int x, int y );
//Keyboard key has been released
//Parameters:
//	unsigned char key:	ASCII value for key released
//	int x			 :	X-coordinate of mouse at key release
//	int y			 :	Y-coordinate of mouse at key release
//Returns:
//	N/A

void specialPressed( int key, int x, int y );
//Special keyboard key has been pressed
//Parameters:
//	unsigned char key:	ASCII value for special key pressed
//	int x			 :	X-coordinate of mouse at keypress
//	int y			 :	Y-coordinate of mouse at keypress
//Returns:
//	N/A

void specialReleased( int key, int x, int y );
//Special keyboard key has been released
//Parameters:
//	unsigned char key:	ASCII value for special key released
//	int x			 :	X-coordinate of mouse at key release
//	int y			 :	Y-coordinate of mouse at key release
//Returns:
//	N/A

void mouseClicked( int button, int state, int x, int y );
//Mouse button has been pressed/released
//Parameters:
//	int button:	Numerical value of button pressed/released
//	int state :	Numerical value of pressed vs released
//	int x			 :	X-coordinate of mouse at key release
//	int y			 :	Y-coordinate of mouse at key release
//Returns:
//	N/A

void mouseDragged( int x, int y );
//Mouse has been dragged (i.e. mouse button pressed)
//Parameters:
//	int x:	X-coordinate of mouse at drag
//	int y:	Y-coordinate of mouse at drag
//Returns:
//	N/A

void mouseMoved( int x, int y );
//Mouse has been moved (i.e. no mouse button pressed)
//Parameters:
//	int x:	X-coordinate of mouse at move
//	int y:	Y-coordinate of mouse at move
//Returns:
//	N/A


#endif