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

#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include "Entity.h"


class Actor : public Entity {

private:
	AnimBlock* mAnimSpec;
	StatBlock* mStatSpec;
	std::vector<StatMod> mModifiers;

protected:


public:
	Actor( void );

	Actor( SpriteSheet* newSheet, RenderBlock* newRenderSpec, AnimBlock* newAnimSpec = NULL, StatBlock* newStatBlock = NULL );

	~Actor( void );

	/*---------------------------
		Overloaded Operators
	---------------------------*/
	

	/*---------------------------
		Additional Operations
	---------------------------*/
	virtual void FreeActor( void );

	bool IsExpired( const StatMod &modifier ) const;

	bool Render( unsigned int index );
	

	/*---------------------------
		  Member Accessors
	---------------------------*/
	AnimBlock* GetAnimSpec( void ) const;

	StatBlock* GetStatSpec( void ) const;

	StatMod    GetModifier( unsigned int index ) const;	

	/*---------------------------
		  Member Mutators
	---------------------------*/
	bool SetAnimSpec( const AnimBlock newAnimSpec );

	bool SetStatSpec( const StatBlock newStatSpec );

	bool AddModifier( const StatMod newModifier );

	bool DelModifier( unsigned int index );

};


#endif