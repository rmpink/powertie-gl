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
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "../lib/utilities.h"
#include "../lib/const.h"
#include "../lib/clip.h"

bool    gButtonDown;
bool    gButtonHeld;
bool    gColorShiftBlue;
GLuint  gDownTime;
GLfloat gG, gB;
GLuint  gX, gY;

Clip    gNewRect = {0};

std::vector<Clip>   gRects;
std::vector<GLfloat> gRectColours;


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

	glutMainLoop();

}


void update() {
	//Update graphic elements before rendering

	GLfloat seconds = gDownTime*FRAME_MILLI;

	if ( gButtonDown ) {
		gDownTime++;

		if ( gButtonHeld && ( gDownTime*FRAME_MILLI > TIME_DELAY ) ) {
			printf("Button Held!\n");

			gButtonDown = false;
		}

		gNewRect.w = 100*seconds;
		gNewRect.h = 100*seconds;

	}

	gNewRect.x = gX-(50*seconds);
	gNewRect.y = gY-(50*seconds);

	if ( gColorShiftBlue ) {
		gG -= 0.001f;
		gB += 0.001f;
	} else {
		gG += 0.001f;
		gB -= 0.001f;
	}

	if ( gG >= 1.f || gB >= 1.f ) {
		gColorShiftBlue = !gColorShiftBlue;
	}

	for ( unsigned int i = 0; i < gRects.size(); ++i ) {
		gRects[i].y += ( gRects[i].h/16 );

		if ( SCREEN_HEIGHT < gRects[i].y ) {
			gRects[i].y = -gRects[i].h;
			gRects[i].x = (GLuint)( gRects[i].x + 320 ) % SCREEN_WIDTH;
		}

		if ( (GLuint)(gRects[i].w) > 100 ) {
			gRects.erase( gRects.begin()+i );
			gRectColours.erase( gRectColours.begin()+i );
		}
	}

}


void render() {
	//Render updated graphics to the screen

	//Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );
    glLoadIdentity();

    for ( unsigned int i = 0; i < gRects.size(); ++i ) {
    	glColor4f( gRectColours[i], gG, gB, 1-(gRects[i].y/SCREEN_HEIGHT) );

    	glBegin( GL_QUADS );
    		glVertex3f( gRects[i].x, gRects[i].y, 0.f );
    		glVertex3f( gRects[i].x + gRects[i].w, gRects[i].y, 0.f );
    		glVertex3f( gRects[i].x + gRects[i].w, gRects[i].y + gRects[i].h, 0.f );
    		glVertex3f( gRects[i].x, gRects[i].y + gRects[i].h, 0.f );
    	glEnd();
    }

    if ( gButtonDown || gButtonHeld ) {
    	glColor4f( 0xff, gG, gB, 1-(gNewRect.y/SCREEN_HEIGHT) );

    	glBegin( GL_QUADS );
    		glVertex3f( gNewRect.x, gNewRect.y, 0.f );
    		glVertex3f( gNewRect.x + gNewRect.w, gNewRect.y, 0.f );
    		glVertex3f( gNewRect.x + gNewRect.w, gNewRect.y + gNewRect.h, 0.f );
    		glVertex3f( gNewRect.x, gNewRect.y + gNewRect.h, 0.f );
    	glEnd();
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


bool loadAssets() {
	//Load all required assets

	bool success = true;

	gButtonDown = false;
	gButtonHeld = false;
	gDownTime   = 0;

	gG = 1.f;
	gB = 0.f;
	gColorShiftBlue = true;

    return success;

}


void keyPressed( unsigned char key, int x, int y ) {
	//Keyboard key has been pressed

	 if ( 0x1B == key ) {

		exit(2);

	} else if ( ' ' == key ) {

		gRects.clear();

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

	if ( GLUT_LEFT_BUTTON == button && GLUT_DOWN == state ) {

		gX = x;
		gY = y;

		gButtonDown = true;
		gButtonHeld = true;

	} else if ( GLUT_LEFT_BUTTON == button && GLUT_UP == state ) {

		GLfloat seconds = gDownTime*FRAME_MILLI;

		if ( seconds ) {
			// printf("RELEASED @ (%d, %d) \t(%0.3f seconds)\n", x, y, seconds );

			gNewRect.x = x-(50*seconds);
			gNewRect.y = y-(50*seconds);
			gNewRect.w = 100*seconds;
			gNewRect.h = 100*seconds;
			
			gRects.push_back( gNewRect );

			srand( time(NULL) );
			GLfloat colour = (GLfloat)( rand() ) / RAND_MAX;

			gRectColours.push_back( colour );

		} else {
			printf("DOUBLE-CLICKED!\n");
		}

		gDownTime = 0;
		gButtonDown = false;
		gButtonHeld = false;

	}

}


void mouseDragged( int x, int y ) {
	//Mouse has been dragged (i.e. mouse button pressed)

	if ( gButtonHeld ) {
		gButtonHeld = false;
		gButtonDown = false;

		gX = x;
		gY = y;
	}

}


void mouseMoved( int x, int y ) {
	//Mouse has been moved (i.e. no mouse button pressed)

	if ( gButtonHeld ) {
		gButtonHeld = false;
		gButtonDown = false;

		gX = x;
		gY = y;
	}

}