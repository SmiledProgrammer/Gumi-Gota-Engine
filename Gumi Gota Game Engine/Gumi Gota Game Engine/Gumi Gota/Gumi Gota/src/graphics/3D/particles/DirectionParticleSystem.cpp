
/* INCLUDES */
// Self Include
#include "DirectionParticleSystem.h"

// Normal Includes
#include <stdlib.h>



/* MACROS */
#define DIRECTION_PARTICLE_SYSTEM_DEFAULT_ROTATION 0.0f
#define DIRECTION_PARTICLE_SYSTEM_DEFAULT_GRAVITY 10.0f
#define DIRECTION_PARTICLE_SYSTEM_DEFAULT_LIFETIME 1.0f
#define DIRECTION_PARTICLE_SYSTEM_DEFAULT_SCALE 1.0f

#define DIRECTION_PARTICLE_SYSTEM_DEFAULT_POSITION_ERROR vector3(0.0f)
#define DIRECTION_PARTICLE_SYSTEM_DEFAULT_DIRECTION_ERROR vector3(0.25f)
#define DIRECTION_PARTICLE_SYSTEM_DEFAULT_ROTATION_ERROR 0.0f
#define DIRECTION_PARTICLE_SYSTEM_DEFAULT_GRAVITY_ERROR 0.0f
#define DIRECTION_PARTICLE_SYSTEM_DEFAULT_LIFETIME_ERROR 0.0f
#define DIRECTION_PARTICLE_SYSTEM_DEFAULT_SCALE_ERROR 0.0f

#define DIRECTION_PARTICLE_SYSTEM_ACCURACY_DIVIDER 1000.0f



namespace gg
{

	/* ADDITIONAL FUNCTIONS */
	static float s_randomSign() //generates float with value 1.0 or -1.0 (50/50 chance)
	{
		return (rand() % 2 == 0) ? -1.0f : 1.0f;
	}



	/* Constructors */
	DirectionParticleSystem::DirectionParticleSystem(const vector3& dir, Texture* texture)
		: ParticleSystem(texture),
		  m_direction(dir),
		  m_rotation(DIRECTION_PARTICLE_SYSTEM_DEFAULT_ROTATION),
		  m_gravity(DIRECTION_PARTICLE_SYSTEM_DEFAULT_GRAVITY),
		  m_lifetime(DIRECTION_PARTICLE_SYSTEM_DEFAULT_LIFETIME),
		  m_scale(DIRECTION_PARTICLE_SYSTEM_DEFAULT_SCALE),
		  m_positionError(DIRECTION_PARTICLE_SYSTEM_DEFAULT_POSITION_ERROR),
		  m_directionError(DIRECTION_PARTICLE_SYSTEM_DEFAULT_DIRECTION_ERROR),
		  m_rotationError(DIRECTION_PARTICLE_SYSTEM_DEFAULT_ROTATION_ERROR),
		  m_gravityError(DIRECTION_PARTICLE_SYSTEM_DEFAULT_GRAVITY_ERROR),
		  m_lifetimeError(DIRECTION_PARTICLE_SYSTEM_DEFAULT_LIFETIME_ERROR),
		  m_scaleError(DIRECTION_PARTICLE_SYSTEM_DEFAULT_SCALE_ERROR)
	{}

	/* Functions */
	ParticleGroup DirectionParticleSystem::generateParticles(const vector3& center, const unsigned int amount)
	{
		// Init
		ParticleGroup result(m_texture, m_startingTextureAtlasIndex, m_endingTextureAtlasIndex);
		result.setUsingAdditiveBlending(m_usingAdditiveBlending);
		result.reserve(amount);
		
		// Generating Particles
		for (unsigned int i = 0; i < amount; i++)
		{
			Particle particle = m_generateRandomParticle(center);

			result.add(particle);
		}


		// Finishing
		return result;
	}


	// Setters
	void DirectionParticleSystem::setDirection(const vector3& dir)
	{
		m_direction = dir;
	}

	void DirectionParticleSystem::setRotation(const float rot)
	{
		m_rotation = rot;
	}

	void DirectionParticleSystem::setGravity(const float gravity)
	{
		m_gravity = gravity;
	}

	void DirectionParticleSystem::setLifetime(const float time)
	{
		m_lifetime = time;
	}

	void DirectionParticleSystem::setScale(const float scale)
	{
		m_scale = scale;
	}


	void DirectionParticleSystem::setPositionError(const vector3& error)
	{
		m_positionError = error;
	}

	void DirectionParticleSystem::setDirectionError(const vector3& error)
	{
		m_directionError = error;
	}

	void DirectionParticleSystem::setRotationError(const float error)
	{
		m_rotationError = error;
	}

	void DirectionParticleSystem::setGravityError(const float error)
	{
		m_gravityError = error;
	}

	void DirectionParticleSystem::setLifetimeError(const float error)
	{
		m_lifetimeError = error;
	}

	void DirectionParticleSystem::setScaleError(const float error)
	{
		m_scaleError = error;
	}

	// Private Functions
	Particle DirectionParticleSystem::m_generateRandomParticle(const vector3& pos)
	{
		// Start Position Randomizing
		vector3 randomizedPosition;

		if (m_positionError.x != 0.0f && m_positionError.y != 0.0f && m_positionError.z != 0.0f)
		{
			randomizedPosition =
				vector3
				(
					s_randomSign() * (float)(rand() % (int)(m_positionError.x * DIRECTION_PARTICLE_SYSTEM_ACCURACY_DIVIDER)) / DIRECTION_PARTICLE_SYSTEM_ACCURACY_DIVIDER,
					s_randomSign() * (float)(rand() % (int)(m_positionError.y * DIRECTION_PARTICLE_SYSTEM_ACCURACY_DIVIDER)) / DIRECTION_PARTICLE_SYSTEM_ACCURACY_DIVIDER,
					s_randomSign() * (float)(rand() % (int)(m_positionError.z * DIRECTION_PARTICLE_SYSTEM_ACCURACY_DIVIDER)) / DIRECTION_PARTICLE_SYSTEM_ACCURACY_DIVIDER
				)
				+ pos;
		}
		else
		{
			randomizedPosition = pos;
		}
		
		// Direction Randomizing
		vector3 randomizedDirection;

		if (m_directionError.x != 0.0f && m_directionError.y != 0.0f && m_directionError.z != 0.0f)
		{
			randomizedDirection =
				vector3
				(
					s_randomSign() * (float)(rand() % (int)(m_directionError.x * DIRECTION_PARTICLE_SYSTEM_ACCURACY_DIVIDER)) / DIRECTION_PARTICLE_SYSTEM_ACCURACY_DIVIDER,
					s_randomSign() * (float)(rand() % (int)(m_directionError.y * DIRECTION_PARTICLE_SYSTEM_ACCURACY_DIVIDER)) / DIRECTION_PARTICLE_SYSTEM_ACCURACY_DIVIDER,
					s_randomSign() * (float)(rand() % (int)(m_directionError.z * DIRECTION_PARTICLE_SYSTEM_ACCURACY_DIVIDER)) / DIRECTION_PARTICLE_SYSTEM_ACCURACY_DIVIDER
				)
				+ m_direction;
		}
		else
		{
			randomizedDirection = m_direction;
		}

		// Rotation Randomizing
		float randomizedRotation;

		if (m_rotationError != 0.0f)
		{
			randomizedRotation = s_randomSign() * (float)(rand() % (int)(m_rotationError * DIRECTION_PARTICLE_SYSTEM_ACCURACY_DIVIDER)) / DIRECTION_PARTICLE_SYSTEM_ACCURACY_DIVIDER + m_rotation;
		}
		else
		{
			randomizedRotation = m_rotation;
		}
		
		// Gravity Randomizing
		float randomizedGravity;

		if (m_gravityError != 0.0f)
		{
			randomizedGravity = s_randomSign() * (float)(rand() % (int)(m_gravityError * DIRECTION_PARTICLE_SYSTEM_ACCURACY_DIVIDER)) / DIRECTION_PARTICLE_SYSTEM_ACCURACY_DIVIDER + m_gravity;
		}
		else
		{
			randomizedGravity = m_gravity;
		}

		// Lifetime Randomizing
		float randomizedLifetime;

		if (m_lifetimeError != 0.0f)
		{
			randomizedLifetime = s_randomSign() * (float)(rand() % (int)(m_lifetimeError * DIRECTION_PARTICLE_SYSTEM_ACCURACY_DIVIDER)) / DIRECTION_PARTICLE_SYSTEM_ACCURACY_DIVIDER + m_lifetime;
		}
		else
		{
			randomizedLifetime = m_lifetime;
		}

		// Scale Randomizing
		float randomizedScale;

		if (m_scaleError != 0.0f)
		{
			randomizedScale = s_randomSign() * (float)(rand() % (int)(m_scaleError * DIRECTION_PARTICLE_SYSTEM_ACCURACY_DIVIDER)) / DIRECTION_PARTICLE_SYSTEM_ACCURACY_DIVIDER + m_scale;
		}
		else
		{
			randomizedScale = m_scale;
		}

		// Finishing
		Particle result(randomizedPosition, randomizedDirection, randomizedLifetime);
		result.setGravity(randomizedGravity);
		result.setRotation(randomizedRotation);
		result.setScale(randomizedScale);


		return result;
	}

}