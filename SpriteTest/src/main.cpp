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

#include "../lib/utilities.h"



int main( int argc, char* argv[] ) {
	
	bool success = initGUI( argc, argv );

	if ( success ) {
		
		if ( argc == 2 ) {
			success = loadAssets( argv[1] );
		} else {
			printf("No argument found. ");
			success = false;
		}

		if ( success ) {

			printf("Assets loaded!\nStarting game loop...\n");
			startGameLoop();

		} else {
			printf("Asset Load fail\n");
			success = false;
		}
	} else {
		printf("initGUI fail\n");
		success = false;
	}

	return success;
}