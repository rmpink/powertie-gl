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

#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

#include <vector>

#include "initGL.h"
#include "colour.h"
#include "collisionMask.h"
#include "const.h"


struct Particle {
	GLfloat  x,  y;
	GLfloat vX, vY;

	GLfloat size;

	Colour colour;
};


class ParticleEmitter {

private:
	/* Attributes */
	Particle mBaseStats;
	std::vector<Particle> mParticles;

	GLfloat mDensity;

	bool mEnabled;

	/*   Methods  */

protected:
	/* Attributes */
	/*   Methods  */

public:
	/* Attributes */
	/*   Methods  */
	ParticleEmitter( void );

	ParticleEmitter( GLfloat x, GLfloat y, GLfloat vX = 0.f, GLfloat vY = 0.f, Colour* colour = (Colour*)NULL );

	~ParticleEmitter( void );

	void SetPosition( GLfloat x, GLfloat y );

	void SetScale( GLfloat size );

	void SetDensity( GLfloat density );

	void SetVelocity( GLfloat vX, GLfloat vY );

	void SetColour( GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.f );

	void SetColour( const Colour c );

	GLfloat GetScale( void );

	bool Enabled( void );

	void BounceVertical( GLuint index );

	void BounceHorizontal( GLuint index );

	void Spawn( void );

	void Update( GLfloat gravity, GLfloat wind, CollisionMask* mask = (CollisionMask*)NULL );

	void Kill( GLuint index );

	void Clear( void );

	void Render( void );

	void Enable( void );

	void Disable( void );

	GLuint Size( void );

};



#endif