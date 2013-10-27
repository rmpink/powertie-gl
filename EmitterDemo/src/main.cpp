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
		
		success = loadAssets();
		
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