#ifndef GUMIGOTA_DIRECTION_PARTICLE_SYSTEM_H
#define GUMIGOTA_DIRECTION_PARTICLE_SYSTEM_H



/* INCLUDES */
// Normal Includes
#include <vector>

// Header Includes
#include "ParticleSystem.h"



namespace gg
{

	class DirectionParticleSystem : public ParticleSystem
	{
	protected:
		/* Variables */
		vector3 m_direction;
		float m_rotation;
		float m_gravity;
		float m_lifetime;
		float m_scale;

		vector3 m_positionError;
		vector3 m_directionError;
		float m_rotationError;
		float m_gravityError;
		float m_lifetimeError;
		float m_scaleError;

	public:
		/* Constructors */
		DirectionParticleSystem(const vector3& dir, Texture* texture); //dir is direction which particles are going in

		/* Functions */
		ParticleGroup generateParticles(const vector3& center, const unsigned int amount); //center is a position where particles are coming from

		// Setters
		void setDirection(const vector3& dir);
		void setRotation(const float rot);
		void setGravity(const float gravity);
		void setLifetime(const float time);
		void setScale(const float scale);

		void setPositionError(const vector3& error);
		void setDirectionError(const vector3& error);
		void setRotationError(const float error);
		void setGravityError(const float error);
		void setLifetimeError(const float error);
		void setScaleError(const float error);

	private:
		// Private Functions
		Particle m_generateRandomParticle(const vector3& pos);

	};

}



#endif