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
#include <math.h>

#include "../lib/utilities.h"
#include "../lib/const.h"

#include "../lib/particleEmitter.h"
#include "../lib/collisionMask.h"
#include "../lib/texture.h"


ParticleEmitter* gEmitter;
ParticleEmitter* gEmitter2;
CollisionMask* gCollisionMask;

GLfloat gGravOffset;
GLfloat gWind;

GLuint gSpray;
GLfloat gParticleAvg;

bool gRenderCages;

// Texture* gTex;

std::vector<Clip> gClips;


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
	
	// Adjust the wind parameter
	gWind += (float)(rand()%1000 - 500) / 1000;

	if ( gWind < -MAX_WIND ) {

		gWind = -MAX_WIND;
	} else if ( gWind > MAX_WIND ) {

		gWind = MAX_WIND;
	}

	// Update the emitter
	gEmitter->Update( gGravOffset, gWind, gCollisionMask );
	
	for ( GLuint i = 0; i < gSpray; ++i ) {
		gEmitter->Spawn();
	}

	gEmitter2->Update( gGravOffset, gWind, gCollisionMask );
	
	for ( GLuint i = 0; i < gSpray; ++i ) {
		gEmitter2->Spawn();
	}

	if ( gEmitter->Enabled() && gEmitter2->Enabled() ) {
		gParticleAvg = ( gParticleAvg + gEmitter->Size() + gEmitter2->Size() ) / 2;
	}

	// Check for collisions
}


void render() {
	//Render updated graphics to the screen

	//Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );
    glLoadIdentity();

    if ( gRenderCages ) {
	    glColor4f( 1.0f, 0.0f, 0.0f, 0.1f );

	    for ( std::vector<Clip>::iterator iter = gClips.begin(); iter != gClips.end(); iter++ ) {

	    	glBegin(GL_QUADS);
	    		glVertex3f( iter->x, iter->y, 0.f );
	    		glVertex3f( iter->x + iter->w, iter->y, 0.f );
	    		glVertex3f( iter->x + iter->w, iter->y + iter->h, 0.f );
	    		glVertex3f( iter->x, iter->y + iter->h, 0.f );
	    	glEnd();

	    }

	    // gTex->Render( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
	}

    gEmitter->Render();
    gEmitter2->Render();

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

	gWind = WIND;
	gGravOffset = GRAVITY;

	gParticleAvg = 0;

	gRenderCages = false;

	srand( time(NULL) );

	gEmitter = new ParticleEmitter();
	gEmitter2 = new ParticleEmitter();

	gSpray = rand() % 32 + 1;

	gEmitter->SetColour(  PT_INDIGO );
	gEmitter2->SetColour( PT_ORANGE );

	gEmitter->SetPosition( rand()%SCREEN_WIDTH/2, rand()%SCREEN_HEIGHT/2 );
	gEmitter2->SetPosition( rand()%SCREEN_WIDTH/2, rand()%SCREEN_HEIGHT/2 );

	gEmitter->SetVelocity( rand()%16 - 8, rand()%16 - 8 );
	gEmitter2->SetVelocity( rand()%16 - 8, rand()%16 - 8 );

	gEmitter->SetDensity( (float)(rand()%1000) / 1000 );
	gEmitter2->SetDensity( (float)(rand()%1000) / 1000 );

	gEmitter->SetScale( PART_SIZE );
	gEmitter2->SetScale( PART_SIZE );

	gEmitter->Enable();
	gEmitter2->Enable();

	gCollisionMask = new CollisionMask( SCREEN_WIDTH, SCREEN_HEIGHT );

	return true;
}


void keyPressed( unsigned char key, int x, int y ) {
	//Keyboard key has been pressed

	if ( 0x1B == key ) {			//ESC key

		gEmitter->Clear();
		gEmitter2->Clear();

		delete gEmitter;
		delete gEmitter2;

		gCollisionMask->Clear();

		// gTex->FreeTexture();

		gClips.clear();

		printf("Average Particle Population: %.2f\n", gParticleAvg );
		
		exit(2);

	} else if ( 0x7F == key ) {		//DELETE key

		gEmitter->Clear();
		gEmitter2->Clear();

		gEmitter->Enable();
		gEmitter2->Enable();

		gClips.clear();

		gCollisionMask->Clear();
		gCollisionMask = new CollisionMask( SCREEN_WIDTH, SCREEN_HEIGHT );

		// gTex->FreeTexture();

	} else if ( 0x0D == key ) {		//ENTER key

		gRenderCages = !gRenderCages;

		if ( gRenderCages ) {

			// gTex = new Texture();

			// gTex->LoadFromPixels( gCollisionMask->GetPixelData(), SCREEN_WIDTH, SCREEN_HEIGHT, 2048, 1024, GL_ALPHA );
		} else {

			// gTex->FreeTexture();
		}

	}else if ( '=' == key ) {

		if ( gSpray < 48 ) {

			gSpray++;
		}

	} else if ( '-' == key ) {

		if ( gSpray > 1 ) {
			gSpray--;
		}

	} else if ( ' ' == key ) {

		Clip newcage;

		newcage.x = rand() % SCREEN_WIDTH;
		newcage.y = rand() % SCREEN_HEIGHT;
		newcage.w = rand() % 200 + 16;
		newcage.h = rand() % 200 + 16;

		gCollisionMask->Add( newcage );

		gClips.push_back( newcage );

	} else if ( '1' == key ) {

		gEmitter->SetColour( PT_RED );
		
	} else if ( '2' == key ) {

		gEmitter->SetColour( PT_ORANGE );
		
	} else if ( '3' == key ) {

		gEmitter->SetColour( PT_YELLOW );
		
	} else if ( '4' == key ) {

		gEmitter->SetColour( PT_GREEN );
		
	} else if ( '5' == key ) {

		gEmitter->SetColour( PT_CYAN );
		
	} else if ( '6' == key ) {

		gEmitter->SetColour( PT_BLUE );
		
	} else if ( '7' == key ) {

		gEmitter->SetColour( PT_INDIGO );
		
	} else if ( '8' == key ) {

		gEmitter->SetColour( PT_MAGENTA );
		
	} else if ( '9' == key ) {

		gEmitter->SetColour( PT_BLACK );
		
	} else if ( '0' == key ) {

		gEmitter->SetColour( PT_WHITE );
		
	} else if ( 'q' == key ) {

		gEmitter2->SetColour( PT_MAGENTA );

	} else if ( 'w' == key ) {

		gEmitter2->SetColour( PT_INDIGO );

	} else if ( 'e' == key ) {

		gEmitter2->SetColour( PT_BLUE );

	} else if ( 'r' == key ) {

		gEmitter2->SetColour( PT_CYAN );

	} else if ( 't' == key ) {

		gEmitter2->SetColour( PT_GREEN );

	} else if ( 'y' == key ) {

		gEmitter2->SetColour( PT_YELLOW );

	} else if ( 'u' == key ) {

		gEmitter2->SetColour( PT_ORANGE );

	} else if ( 'i' == key ) {

		gEmitter2->SetColour( PT_RED );

	} else if ( 'o' == key ) {

		gEmitter2->SetColour( PT_WHITE );

	} else if ( 'p' == key ) {

		gEmitter2->SetColour( PT_BLACK );

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
		gEmitter->SetPosition( (float)x, (float)y );
	
		// if ( gEmitter->Enabled() ) {

		// 	gEmitter->Disable();
		// } else {

		// 	gEmitter->Enable();
		// }
	} else if ( GLUT_RIGHT_BUTTON == button && GLUT_DOWN == state ) {
		gEmitter2->SetPosition( (float)x, (float)y );
	
		// if ( gEmitter2->Enabled() ) {

		// 	gEmitter2->Disable();
		// } else {

		// 	gEmitter2->Enable();
		// }
	}
}


void mouseDragged( int x, int y ) {
	//Mouse has been dragged (i.e. mouse button pressed)
	// gEmitter->SetPosition( (float)x, (float)y );
}


void mouseMoved( int x, int y ) {
	//Mouse has been moved (i.e. no mouse button pressed)
}