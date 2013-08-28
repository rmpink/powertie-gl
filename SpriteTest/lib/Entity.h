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

#ifndef ENTITY_H
#define ENTITY_H

#include "initGL.h"
#include "entitystruct.h"
#include "spriteSheet.h"


class Entity {

private:
	GLuint mID;

	SpriteSheet* mSheet;
	RenderBlock* mRenderSpec;

	// static GLuint TotalEntities;

protected:


public:
	Entity( void );

	~Entity( void );

	/*---------------------------
		Overloaded Operators
	---------------------------*/
	

	/*---------------------------
		Additional Operations
	---------------------------*/
	virtual void FreeEntity( void );

	bool Render( unsigned int index );
	

	/*---------------------------
		  Member Accessors
	---------------------------*/
	GLuint GetID( void ) const;

	SpriteSheet* GetSheet( void ) const;

	RenderBlock* GetRenderSpec( void ) const;
	

	/*---------------------------
		  Member Mutators
	---------------------------*/
	bool SetSheet( SpriteSheet* newSheet );

	bool SetRenderSpec( RenderBlock* newRenderSpec );

	/****** RenderBlock ******/
	bool SetPosition( double pX, double pY );

	bool SetPosition( Vector2 &newPosition );

	bool SetVelocity( double vX, double vY );

	bool SetVelocity( Vector2 &newVelocity );

	bool SetScale( double scX, double scY );

	bool SetScale( Vector2 &newScale );

	bool SetRotation( double rX, double rY );

	bool SetRotation( Vector2 &newRotation );

	bool SetDirection( unsigned char newDir );

	bool SetClip( Clip newClip );

};


#endif