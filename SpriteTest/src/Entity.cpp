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

#include "../lib/Entity.h"


////////////////////////////////////
//			   PUBLIC			  //
////////////////////////////////////
Entity::Entity() {
	//Default sprite sheet constructor

	printf("Entity::Entity()\n");

	this->mID = 0;

	this->mSheet = new SpriteSheet();
	this->mRenderSpec = new RenderBlock;

}


Entity::~Entity() {
	//Default sprite sheet destructor

	printf("Entity::~Entity()\n");

	FreeEntity();

}


/*---------------------------
	Overloaded Operators
---------------------------*/


/*---------------------------
	Additional Operations
---------------------------*/
void Entity::FreeEntity() {
	//Deallocates VBO, IBOs, and sprite array

	printf("Entity::FreeEntity()\n");

	delete this->mRenderSpec;

}


bool Entity::Render( unsigned int index ) {
	//Renders sprite at given index in sprite array

	bool success = true;

	printf("Entity::Render()\n");

	//======================================
	//	Method Stub
	//	This section needs to be expanded!
	//======================================

	return success;

}


/*---------------------------
	  Member Accessors
---------------------------*/
GLuint Entity::GetID() const {

	return this->mID;

}


SpriteSheet* Entity::GetSheet() const {

	return this->mSheet;

}


RenderBlock* Entity::GetRenderSpec() const {

	return this->mRenderSpec;

}


/*---------------------------
	  Member Mutators
---------------------------*/
bool Entity::SetSheet( SpriteSheet* newSheet ) {

	bool success = true;

	if ( true ) {

		this->mSheet = newSheet;

	} else {
		success = false;
	}

	return success;

}


bool Entity::SetRenderSpec( RenderBlock* newRenderSpec ) {

	bool success = true;

	if ( newRenderSpec ) {

		this->mRenderSpec = newRenderSpec;

	} else {
		success = false;
	}

	return success;

}


/****** RenderBlock ******/
bool Entity::SetPosition( double pX, double pY ) {

	bool success = true;

	if ( ( pX >= 0 && pY >= 0 ) &&
		 ( !this->mRenderSpec->position.equals( pX, pY ) ) ) {

		this->mRenderSpec->position.set( pX, pY );

	} else {
		success = false;
	}

	return success;

}


bool Entity::SetPosition( Vector2 &newPosition ) {

	bool success = true;

	if ( ( newPosition.x() >= 0 && newPosition.y() >= 0 ) &&
		 ( !this->mRenderSpec->position.equals( newPosition ) ) ) {

		this->mRenderSpec->position.set( newPosition );
	
	} else {
		success = false;
	}

	return success;

}


bool Entity::SetVelocity( double vX, double vY ) {

	bool success = true;

	if ( !this->mRenderSpec->velocity.equals( vX, vY ) ) {

		this->mRenderSpec->velocity.set( vX, vY );

	} else {
		success = false;
	}

	return success;

}


bool Entity::SetVelocity( Vector2 &newVelocity ) {

	bool success = true;

	if ( !this->mRenderSpec->velocity.equals( newVelocity ) ) {

		this->mRenderSpec->velocity.set( newVelocity );

	} else {
		success = false;
	}

	return success;

}


bool Entity::SetScale( double scX, double scY ) {

	bool success = true;

	if ( ( scX >= 0 && scY >= 0 ) &&
		 ( !this->mRenderSpec->scale.equals( scX, scY ) ) ) {

		this->mRenderSpec->scale.set( scX, scY );

	} else {
		success = false;
	}

	return success;

}


bool Entity::SetScale( Vector2 &newScale ) {

	bool success = true;

	if ( ( newScale.x() >= 0 && newScale.y() >= 0 ) &&
		 ( !this->mRenderSpec->scale.equals( newScale ) ) ) {

		this->mRenderSpec->scale.set( newScale );

	} else {
		success = false;
	}

	return success;

}


bool Entity::SetRotation( double rX, double rY ) {

	bool success = true;

	if ( !this->mRenderSpec->rotation.equals( rX, rY ) ) {

		this->mRenderSpec->rotation.set( rX, rY );

	} else {
		success = false;
	}

	return success;

}


bool Entity::SetRotation( Vector2 &newRotation ) {

	bool success = true;

	if ( !this->mRenderSpec->rotation.equals( newRotation ) ) {

		this->mRenderSpec->rotation.set( newRotation );

	} else {
		success = false;
	}

	return success;

}


bool Entity::SetDirection( unsigned char newDir ) {

	bool success = true;

	if ( ( newDir != this->mRenderSpec->direction ) &&
		 ( newDir == ANIM_DIRECTION_FORWARD || newDir == ANIM_DIRECTION_BACKWARD ) ) {

		this->mRenderSpec->direction = newDir;

	} else {
		success = false;
	}

	return success;

}


bool Entity::SetClip( Clip newClip ) {

	bool success = true;

	if ( ( newClip.x >= 0 && newClip.x != this->mRenderSpec->sprite.x ) &&
		 ( newClip.y >= 0 && newClip.y != this->mRenderSpec->sprite.y ) &&
		 ( newClip.w >  0 && newClip.w != this->mRenderSpec->sprite.w ) &&
		 ( newClip.h >  0 && newClip.h != this->mRenderSpec->sprite.h ) ) {

		this->mRenderSpec->sprite = newClip;

	} else {
		success = false;
	}

	return success;

}