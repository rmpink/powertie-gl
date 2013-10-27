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

#include <time.h>
#include <math.h>
#include "../lib/particleEmitter.h"


ParticleEmitter::ParticleEmitter() {

	mBaseStats.x = 0.f;
	mBaseStats.y = 0.f;
	mBaseStats.vX = 0.f;
	mBaseStats.vY = 0.f;

	mBaseStats.size = 8.f;

	Colour newcolour = { 1.f, 1.f, 1.f, 1.f };

	mBaseStats.colour = newcolour;

	mEnabled = false;

	srand( time(NULL) );
}


ParticleEmitter::ParticleEmitter( GLfloat x, GLfloat y, GLfloat vX, GLfloat vY, Colour* colour ) {

	mBaseStats.x = x;
	mBaseStats.y = y;
	mBaseStats.vX = vX;
	mBaseStats.vY = vY;

	mBaseStats.size = 8.f;

	mBaseStats.colour = *colour;

	mEnabled = false;

	srand( time(NULL) );
}


ParticleEmitter::~ParticleEmitter() {

}


void ParticleEmitter::SetPosition( GLfloat x, GLfloat y ) {

	mBaseStats.x = x;
	mBaseStats.y = y;
}


void ParticleEmitter::SetScale( GLfloat size ) {

	mBaseStats.size = size;
}


void ParticleEmitter::SetDensity( GLfloat density ) {

	mDensity = density;
}


void ParticleEmitter::SetVelocity( GLfloat vX, GLfloat vY ) {

	mBaseStats.vX = vX;
	mBaseStats.vY = vY;
}


void ParticleEmitter::SetColour( GLfloat r, GLfloat g, GLfloat b, GLfloat a ) {

	Colour newcolour = { r, g, b, a };
	mBaseStats.colour = newcolour;
}


void ParticleEmitter::SetColour( const Colour c ) {

	mBaseStats.colour.r = c.r;
	mBaseStats.colour.g = c.g;
	mBaseStats.colour.b = c.b;
	mBaseStats.colour.a = c.a;
}


GLfloat ParticleEmitter::GetScale() {

	return mBaseStats.size;
}


bool ParticleEmitter::Enabled() {
	return mEnabled;
}


void ParticleEmitter::BounceVertical( GLuint index ) {

	mParticles[index].vY = -mParticles[index].vY * mDensity;
}


void ParticleEmitter::BounceHorizontal( GLuint index ) {

	mParticles[index].vX = -mParticles[index].vX * mDensity;
}


void ParticleEmitter::Spawn() {

	if ( mEnabled ) {

		Particle newpart = mBaseStats;

		newpart.x += (float)(rand()%1000 - 500) / 100;
		newpart.y += (float)(rand()%1000 - 500) / 100;

		newpart.vX += (float)(rand()%1000 - 500) / 300;
		newpart.vY += (float)(rand()%1000 - 500) / 300;

		newpart.size = mBaseStats.size;

		float clr = (float)(rand()%256 - 128) / 256;

		newpart.colour.r += clr;
		newpart.colour.g += clr;
		newpart.colour.b += clr;

		if ( newpart.colour.r < 0 ) {
			newpart.colour.r = 0;
		} else if ( newpart.colour.r > 255 ) {
			newpart.colour.r = 255;
		}

		if ( newpart.colour.g < 0 ) {
			newpart.colour.g = 0;
		} else if ( newpart.colour.g > 255 ) {
			newpart.colour.g = 255;
		}

		if ( newpart.colour.b < 0 ) {
			newpart.colour.b = 0;
		} else if ( newpart.colour.b > 255 ) {
			newpart.colour.b = 255;
		}

		mParticles.push_back( newpart );
	}
}


void ParticleEmitter::Update( GLfloat gravity, GLfloat wind, CollisionMask* mask ) {
	
	GLuint i = 0;

	for ( std::vector<Particle>::iterator iter = mParticles.begin(); iter != mParticles.end(); iter++ ) {
		
		iter->vX += ( wind * SCREEN_FPS/1000 );
		iter->vY += ( gravity * SCREEN_FPS/1000 );

		iter->x += iter->vX;
		iter->y += iter->vY;

		// Detect window border collision
		if ( iter->y + iter->vY > SCREEN_HEIGHT ) {

			BounceVertical( i );
		}

		if ( iter->x + iter->vX > SCREEN_WIDTH ) {

			BounceHorizontal( i );

		} else if ( iter->x + iter->vX < 0 ) {

			BounceHorizontal( i );
		}

		// Detect dead particles
		if ( iter->y > SCREEN_HEIGHT-0.5 && iter->vY < 0.5 && iter->vY > -0.5 ) {

			Kill( i );
		}

		if ( mask->Touch( iter->x, iter->y ) && mask->Touch( iter->x + iter->vX, iter->y + iter->vY ) ) {

			Kill( i );
		}

		// Detect collisions against "mask" object
		if ( mask->Touch( iter->x + iter->vX, iter->y ) ) {

			BounceHorizontal( i );
		}

		if ( mask->Touch( iter->x, iter->y + iter->vY ) ) {

			BounceVertical( i );
		}

		i++;
	}
}


void ParticleEmitter::Kill( GLuint index ) {

	if ( index != mParticles.size()-1 ) {
		mParticles.erase( mParticles.begin() + index );
	}
}


void ParticleEmitter::Clear() {

	mParticles.clear();
}


void ParticleEmitter::Render() {
	
	for ( std::vector<Particle>::iterator iter = mParticles.begin(); iter != mParticles.end(); iter++ ) {
		
		glColor4f( iter->colour.r, iter->colour.g, iter->colour.b, iter->colour.a );

		glBegin(GL_QUADS);
			glVertex3f( iter->x, iter->y, 0.f );
			glVertex3f( iter->x + iter->size, iter->y, 0.f );
			glVertex3f( iter->x + iter->size, iter->y + iter->size, 0.f );
			glVertex3f( iter->x, iter->y + iter->size, 0.f );
		glEnd();
	}
}


void ParticleEmitter::Enable() {
	mEnabled = true;
}


void ParticleEmitter::Disable() {
	mEnabled = false;
}


GLuint ParticleEmitter::Size() {
	return mParticles.size();
}