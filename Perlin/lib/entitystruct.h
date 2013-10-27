#ifndef ENTITY_STRUCT_H
#define ENTITY_STRUCT_H

#include "Vector2.h"
#include "clip.h"


const int ANIM_DIRECTION_FORWARD  = 0;
const int ANIM_DIRECTION_BACKWARD = 1;

const int ANIM_FRAMES = 8;


enum AnimState {
	ANIM_STAND = 0,
	ANIM_WALK,
	ANIM_RUN,
	ANIM_CRAWL,
	ANIM_JUMP,
	ANIM_FALL,
	ANIM_STRIKE,
	ANIM_DIE
};


struct StatBlock {

	unsigned int level;

	unsigned int STR;
	unsigned int CON;
	unsigned int DEX;
	unsigned int INT;
	unsigned int WIS;
	unsigned int CHA;

	unsigned int speed;

	unsigned int HP;
	unsigned int AC;

};


struct AnimBlock {

	AnimState animation;
	unsigned int frame;

};


struct RenderBlock {

	Vector2 position;
	Vector2 velocity;
	Vector2 scale;
	Vector2 rotation;

	unsigned char direction;

	Clip sprite;

};


struct StatMod {

	//enum What
	//enum How much
	//enum Lifetime

};


#endif