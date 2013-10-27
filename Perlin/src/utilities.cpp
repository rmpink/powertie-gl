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

#include <string.h>
#include "../lib/utilities.h"
#include "../lib/const.h"

#include "../lib/texture.h"
#include "../lib/perlin.h"

Texture   gPerlin;
Texture*  gPerlinTess;

unsigned char* gWhite;
unsigned char* gOffwhite;

int 	  gSeed   = P_SEED;
int 	  gFactor =    256;
float 	  gZoom   =    1.f;


bool initGL() {
	//Initialize the OpenGL graphics library

	bool success = true;

	GLenum glewError = glewInit();

	if ( glewError != GLEW_OK ) {
		printf( "ERROR: GLEW could not be initialized. %s\n", glewGetErrorString( glewError ) );
		success = false;
	}

	if ( !GLEW_VERSION_2_1 ) {
		printf( "OpenGL 2.1 not supported.\n" );
		success = false;
	}

	glViewport( 0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glClearColor( 0.f, 0.f, 0.f, 1.f );

	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	
	glDisable( GL_DEPTH_TEST );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );

	glEnable( GL_MULTISAMPLE );

	GLenum glError = glGetError();

	if ( glError != GL_NO_ERROR ) {
		printf("Error initializing OpenGL:\n\t%s\n", gluErrorString( glError ) );
		success = false;
	}

	return success;

}


bool initIL() {
	//Initialize DevIL and DevILU

	bool success = true;

	ilInit();
	iluInit();
	ilClearColour( 255, 255, 255, 000 );

	ILenum ilError = ilGetError();

	if ( ilError != IL_NO_ERROR ) {
		printf("Error initializing DevIL:\n\t%s\n", iluErrorString( ilError ) );
		success = false;
	}

	return success;

}


bool initFreeType() {
	//Initialize FreeType library

	bool success = true;

	#ifdef FONT_H

	if ( !Font::InitFreeType() ) {
		printf("Unable to initialize FreeType!\n");
		success = false;
	}

	#endif

	return success;
}


bool initGUI( int argc, char* argv[] ) {
	//Initialize the FreeGLUT window library

	bool success = true;

	glutInit( &argc, argv );
	glutInitContextVersion( 2, 1 );

	glutInitDisplayMode( GLUT_DOUBLE | GLUT_MULTISAMPLE );
	glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	glutCreateWindow( WINDOW_TITLE );

	glutKeyboardFunc( keyPressed );
	glutKeyboardUpFunc( keyReleased );

	glutSpecialFunc( specialPressed );
	glutSpecialUpFunc( specialReleased );

	glutMouseFunc( mouseClicked );

	glutMotionFunc( mouseDragged );
	glutPassiveMotionFunc( mouseMoved );

	glutDisplayFunc( render );
	glutTimerFunc( 1000/SCREEN_FPS, runMainLoop, 0 );

	if ( initGL() ) {

		printf("initGL() is good.\n");
	
		if ( initIL() ) {

			printf("initIL() is good.\n");

			if ( initFreeType() ) {

				printf("initFreeType() is good.\n");

			} else {
				printf("initFreeType() failed!\n");
				success = false;
			}
		} else {
			printf("initIL() failed!\n");
			success = false;
		}
	} else {
		printf("initGL() failed!\n");
		success = false;
	}

	return success;

}


void startGameLoop() {
	//Meant to disconnect GLUT from main implementation

	glutMainLoop();

}


void update() {
	//Update graphic elements before rendering

}


void render() {
	//Render updated graphics to the screen

	//Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );
    glLoadIdentity();

    for ( int x = 0; x < gZoom; ++x ) {

    	for ( int y = 0; y < gZoom; ++y ) {

    		gPerlin.Render( x*(SCREEN_WIDTH/gZoom), y*(SCREEN_HEIGHT/gZoom), gFactor/gZoom*2, gFactor/gZoom*2 );

	   	}
	}
    
    //Update screen
    glutSwapBuffers();

}


void runMainLoop( int val ) {
	//Execute main program loop

	update();
	render();

	glutTimerFunc( 1000/SCREEN_FPS, runMainLoop, val );

}


bool loadAssets( char filepath[] ) {
	//Load all required assets

	bool success = true;

	gZoom = 1.f;

	printf("Still good..\n");

	gWhite = whiteNoise( gFactor, gFactor, gSeed );
	gOffwhite = perlinNoise( gWhite, gFactor, gFactor, 6, gSeed );
	delete[] gWhite;

	gPerlin.LoadFromPixels( gOffwhite, gFactor, gFactor, gFactor, gFactor, GL_ALPHA );

	glBindTexture( GL_TEXTURE_2D, gPerlin.GetID() );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

	glBindTexture( GL_TEXTURE_2D, (GLuint)NULL );

	printf("New Seed: %.8X\n", gSeed );

    return success;

}


void keyPressed( unsigned char key, int x, int y ) {
	//Keyboard key has been pressed

	if ( key == 0x1B ) {

		gPerlin.FreeTexture();

		for ( int i = 0; i < gFactor*gFactor; ++i ) {
			// gWhite[i]	 = 0x00;
			gOffwhite[i] = 0x00;
		}

		// delete[] gWhite;
		delete[] gOffwhite;

		exit(2);

	} else if ( key == ' ' ) {

		gSeed = rand() % 0xFFFFFFFF;

		gWhite = whiteNoise( gFactor, gFactor, gSeed );
		gOffwhite = perlinNoise( gWhite, gFactor, gFactor, 6, gSeed );
		delete[] gWhite;

		gPerlin.LoadFromPixels( gOffwhite, gFactor, gFactor, gFactor, gFactor, GL_ALPHA );
	
		glBindTexture( GL_TEXTURE_2D, gPerlin.GetID() );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		
		glBindTexture( GL_TEXTURE_2D, (GLuint)NULL );

		printf("New Seed: %.8X\n", gSeed );

	} else if ( key == '=' ) {
		//Increase contrast

		for ( int i = 0; i < gFactor*gFactor; ++i ) {

			int pixel = (char)(gOffwhite[i] - 128);
			pixel *= 1.1;

			if ( pixel >= 128 ) {
				pixel = 127;
			} else if ( pixel <= -129) {
				pixel = -128;
			}

			gOffwhite[i] = (unsigned char)(pixel + 128);

		}

		gPerlin.LoadFromPixels( gOffwhite, gFactor, gFactor, gFactor, gFactor, GL_ALPHA );

	} else if ( key == '-' ) {
		//Decrease constrast

		for ( int i = 0; i < gFactor*gFactor; ++i ) {

			int pixel = (char)(gOffwhite[i] - 128);
			pixel *= 0.9;

			if ( pixel == 0 ) {
				int rnum = ( rand() % 3 ) - 1;
				pixel = rnum*4;
			}

			gOffwhite[i] = (unsigned char)(pixel + 128);

		}

		gPerlin.LoadFromPixels( gOffwhite, gFactor, gFactor, gFactor, gFactor, GL_ALPHA );

	} else if ( key == '1' ) {

		gZoom = 1.f;

	} else if ( key == '2' ) {

		gZoom = 2.f;

	} else if ( key == '3' ) {

		gZoom = 3.f;

	} else if ( key == '4' ) {

		gZoom = 4.f;

	} else if ( key == '5' ) {

		gZoom = 5.f;

	} else if ( key == '6' ) {

		gZoom = 6.f;

	} else if ( key == '7' ) {

		gZoom = 7.f;

	} else if ( key == '8' ) {

		gZoom = 8.f;

	} else if ( key == '9' ) {

		gZoom = 9.f;

	} else if ( key == '0' ) {

		gZoom = 0.f;

	}
}


void keyReleased( unsigned char key, int x, int y ) {
	//Keyboard key has been released

	

}


void specialPressed( int key, int x, int y ) {
	//Special keyboard key has been pressed

}


void specialReleased( int key, int x, int y ) {
	//Special keyboard key has been released

}


void mouseClicked( int button, int state, int x, int y ) {
	//Mouse button has been pressed/released

	

}


void mouseDragged( int x, int y ) {
	//Mouse has been dragged (i.e. mouse button pressed)



}


void mouseMoved( int x, int y ) {
	//Mouse has been moved (i.e. no mouse button pressed)



}