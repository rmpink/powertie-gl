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
#include "../lib/entitystruct.h"

#include "../lib/texture.h"

Texture   gDude;
Texture   gBG;
GLint     gFrame;
AnimState gState;
char	  gFile[64];
bool	  gForward;
bool	  gUpright;
bool	  gZoomIn, gZoomOut;
GLfloat	  gRenderWidth, gRenderHeight;
GLfloat	  gAdjWidth, gAdjHeight;


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

	if ( gForward ) {
		
		gFrame++;
	
		if ( gFrame >= (int)SPRITE_ROWS*4 ) {
			gFrame = 0;
		}
	} else {
		
		gFrame--;
	
		if ( gFrame < 0 ) {
			gFrame = (SPRITE_ROWS-1)*4;
		}
	}

	if ( gZoomIn ) {
		gAdjWidth *= ZOOM_FACTOR;
		gAdjHeight *= ZOOM_FACTOR;
	} else if ( gZoomOut ) {
		gAdjWidth /= ZOOM_FACTOR;
		gAdjHeight /= ZOOM_FACTOR;
	}

}



void render() {
	//Render updated graphics to the screen

	//Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );
    glLoadIdentity();
    
    Clip gClip = { (gFrame/4) * 32.f, 0.f, 32.f, 48.f };

    if ( gUpright ) {
    	gClip.y = gState * 48.f;
    } else {
    	gClip.y = ( SPRITE_ROWS - gState-1 ) * 48.f;
    }

    gBG.Render( 0.f, 0.f, gBG.GetImageWidth(), gBG.GetImageHeight() );
    gDude.Render( (SCREEN_WIDTH-gAdjWidth)/2.f, (SCREEN_HEIGHT-gAdjHeight)/2.f, gAdjWidth, gAdjHeight, &gClip );

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

	strcpy( gFile, filepath );
	gDude.LoadFromFile( gFile );
	gBG.LoadFromFile( "img/bg.jpg" );
	gState = ANIM_STAND;
	gFrame = 0;
	gForward = true;
	gUpright = true;
	gZoomIn  = false;
	gZoomOut = false;
	gRenderWidth = 86.1f;
	gRenderHeight = 129.2f;
	gAdjWidth = gRenderWidth;
	gAdjHeight = gRenderHeight;

	glBindTexture( GL_TEXTURE_2D, gDude.GetID() );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glBindTexture( GL_TEXTURE_2D, gBG.GetID() );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glBindTexture( GL_TEXTURE_2D, (GLuint)NULL );

    return success;

}



void keyPressed( unsigned char key, int x, int y ) {
	//Keyboard key has been pressed

	if ( '1' <= key && '8' >= key ) {
		
		switch( key ) {
			case '1':
				if ( ANIM_STAND != gState ) {
					gState = ANIM_STAND;
					gFrame = 31;
				}

				break;
			case '2':
				if ( ANIM_WALK != gState ) {
					gState = ANIM_WALK;
					gFrame = 31;
				}

				break;
			case '3':
				if ( ANIM_RUN != gState ) {
					gState = ANIM_RUN;
					gFrame = 31;
				}

				break;
			case '4':
				if ( ANIM_CRAWL != gState ) {
					gState = ANIM_CRAWL;
					gFrame = 31;
				}

				break;
			case '5':
				if ( ANIM_JUMP != gState ) {
					gState = ANIM_JUMP;
					gFrame = 31;
				}

				break;
			case '6':
				if ( ANIM_FALL != gState ) {
					gState = ANIM_FALL;
					gFrame = 31;
				}

				break;
			case '7':
				if ( ANIM_STRIKE != gState ) {
					gState = ANIM_STRIKE;
					gFrame = 31;
				}

				break;
			case '8':
				if ( ANIM_DIE != gState ) {
					gState = ANIM_DIE;
					gFrame = 31;
				}

				break;
		}	//end switch

	} else if ( 'h' == key ) {

		gDude.FlipHori();

		if ( true == gForward ) {
			gForward = false;
			gFrame = (SPRITE_ROWS-1)*4;
		} else {
			gForward = true;
			gFrame = 0;
		}

	} else if ( 'v' == key ) {

		gDude.FlipVert();

		if ( true == gUpright ) {
			gUpright = false;
		} else {
			gUpright = true;
		}

	} else if ( 0x1B == key ) {

		exit(2);

	} else if ( '=' == key ) {
		gZoomIn = true;
		gZoomOut = false;
	} else if ( '-' == key ) {
		gZoomOut = true;
		gZoomIn = false;
	} else if ( ' ' == key ) {
		printf("Load saved position . . .\n");
		gAdjWidth = gRenderWidth;
		gAdjHeight = gRenderHeight;
	} else if ( '\r' == key ) {
		printf("Saved position. Load with SPACE . . .\n");
		gRenderWidth = gAdjWidth;
		gRenderHeight = gAdjHeight;
	}

}



void keyReleased( unsigned char key, int x, int y ) {
	//Keyboard key has been released

	if ( '=' == key ) {
		gZoomIn = false;
	} else if ( '-' == key ) {
		gZoomOut = false;
	}

}



void specialPressed( int key, int x, int y ) {
	//Special keyboard key has been pressed



}



void specialReleased( int key, int x, int y ) {
	//Special keyboard key has been released



}



void mouseClicked( int button, int state, int x, int y ) {
	//Mouse button has been pressed/released

	if ( state == GLUT_DOWN ) {
		printf("Sprite texture refreshed . . .\n");

		gDude.LoadFromFile( gFile );

		glBindTexture( GL_TEXTURE_2D, gDude.GetID() );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    	glBindTexture( GL_TEXTURE_2D, (GLuint)NULL );
	}

}



void mouseDragged( int x, int y ) {
	//Mouse has been dragged (i.e. mouse button pressed)

}



void mouseMoved( int x, int y ) {
	//Mouse has been moved (i.e. no mouse button pressed)

}