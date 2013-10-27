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

#include "../lib/Actor.h"


////////////////////////////////////
//			   PUBLIC			  //
////////////////////////////////////
Actor::Actor() {
	//Default sprite sheet constructor

	printf("Actor::Actor()\n");

	this->mAnimSpec = new AnimBlock;
	this->mStatSpec = new StatBlock;

	mModifiers.clear();

}


Actor::Actor( SpriteSheet* newSheet, RenderBlock* newRenderSpec, AnimBlock* newAnimSpec, StatBlock* newStatSpec ) {

	if ( newSheet ) {
		SetSheet( newSheet );
	} else {
		SetSheet( NULL );
	}

	if ( newRenderSpec ) {
		SetRenderSpec( newRenderSpec );
	} else {
		SetRenderSpec( NULL );
	}

	mAnimSpec = newAnimSpec;
	mStatSpec = newStatSpec;

	mModifiers.clear();

}


Actor::~Actor() {
	//Default sprite sheet destructor

	printf("Actor::~Actor()\n");

	FreeActor();

}


/*---------------------------
	Overloaded Operators
---------------------------*/


/*---------------------------
	Additional Operations
---------------------------*/
void Actor::FreeActor() {
	//Deallocates VBO, IBOs, and sprite array

	printf("Actor::FreeActor()\n");

	delete mAnimSpec;
	delete mStatSpec;

	mModifiers.clear();

}


bool Actor::IsExpired( const StatMod &modifier ) const {

	bool success = true;

	//======================================
	//	Method Stub
	//	This section needs to be expanded!
	//======================================

	return success;

}


bool Actor::Render( unsigned int index ) {
	//Renders sprite at given index in sprite array

	bool success = true;

	printf("Actor::Render()\n");

	//======================================
	//	Method Stub
	//	This section needs to be expanded!
	//======================================

	return success;

}


/*---------------------------
	  Member Accessors
---------------------------*/
AnimBlock* Actor::GetAnimSpec() const {

	return this->mAnimSpec;

}

StatBlock* Actor::GetStatSpec() const {

	return this->mStatSpec;

}


StatMod Actor::GetModifier( unsigned int index ) const {

	return this->mModifiers[index];

}


/*---------------------------
	  Member Mutators
---------------------------*/
bool Actor::SetAnimSpec( const AnimBlock newAnimSpec ) {

	bool success = true;

	//======================================
	//	Method Stub
	//	This section needs to be expanded!
	//======================================

	return success;

}


bool Actor::SetStatSpec( const StatBlock newStatSpec ) {

	bool success = true;

	//======================================
	//	Method Stub
	//	This section needs to be expanded!
	//======================================

	return success;

}


bool Actor::AddModifier( const StatMod newModifier ) {

	bool success = true;

	this->mModifiers.push_back( newModifier );

	return success;

}


bool Actor::DelModifier( unsigned int index ) {

	bool success = true;

	if ( index >= 0 && index < mModifiers.size() ) {

		//delete the thing at the index

	} else {
		success = false;
	}

	return success;

}