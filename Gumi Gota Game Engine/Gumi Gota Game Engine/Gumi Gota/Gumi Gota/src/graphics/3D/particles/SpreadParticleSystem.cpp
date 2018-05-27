
/* INCLUDES */
// Self Include
#include "SpreadParticleSystem.h"

// Normal Includes
#include <stdlib.h>



/* MACROS */
#define SPREAD_PARTICLE_SYSTEM_DEFAULT_SPEED 3.0f
#define SPREAD_PARTICLE_SYSTEM_DEFAULT_ROTATION 0.0f
#define SPREAD_PARTICLE_SYSTEM_DEFAULT_GRAVITY 0.0f
#define SPREAD_PARTICLE_SYSTEM_DEFAULT_LIFETIME 1.0f
#define SPREAD_PARTICLE_SYSTEM_DEFAULT_SCALE 1.0f

#define SPREAD_PARTICLE_SYSTEM_DEFAULT_POSITION_ERROR vector3(0.0f)
#define SPREAD_PARTICLE_SYSTEM_DEFAULT_SPEED_ERROR 0.5f
#define SPREAD_PARTICLE_SYSTEM_DEFAULT_ROTATION_ERROR 0.0f
#define SPREAD_PARTICLE_SYSTEM_DEFAULT_GRAVITY_ERROR 0.0f
#define SPREAD_PARTICLE_SYSTEM_DEFAULT_LIFETIME_ERROR 0.0f
#define SPREAD_PARTICLE_SYSTEM_DEFAULT_SCALE_ERROR 0.0f

#define SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER 1000.0f



namespace gg
{

	/* ADDITIONAL FUNCTIONS */
	static float s_randomSign() //generates float with value 1.0 or -1.0 (50/50 chance)
	{
		return (rand() % 2 == 0) ? -1.0f : 1.0f;
	}



	/* Constructors */
	SpreadParticleSystem::SpreadParticleSystem(Texture* texture)
		: ParticleSystem(texture),
		  m_speed(SPREAD_PARTICLE_SYSTEM_DEFAULT_SPEED),
		  m_rotation(SPREAD_PARTICLE_SYSTEM_DEFAULT_ROTATION),
		  m_gravity(SPREAD_PARTICLE_SYSTEM_DEFAULT_GRAVITY),
		  m_lifetime(SPREAD_PARTICLE_SYSTEM_DEFAULT_LIFETIME),
		  m_scale(SPREAD_PARTICLE_SYSTEM_DEFAULT_SCALE),
		  m_positionError(SPREAD_PARTICLE_SYSTEM_DEFAULT_POSITION_ERROR),
		  m_speedError(SPREAD_PARTICLE_SYSTEM_DEFAULT_SPEED_ERROR),
		  m_rotationError(SPREAD_PARTICLE_SYSTEM_DEFAULT_ROTATION_ERROR),
		  m_gravityError(SPREAD_PARTICLE_SYSTEM_DEFAULT_GRAVITY_ERROR),
		  m_lifetimeError(SPREAD_PARTICLE_SYSTEM_DEFAULT_LIFETIME_ERROR),
		  m_scaleError(SPREAD_PARTICLE_SYSTEM_DEFAULT_SCALE_ERROR)
	{}

	/* Functions */
	ParticleGroup SpreadParticleSystem::generateParticles(const vector3& center, const unsigned int amount)
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
	void SpreadParticleSystem::setSpeed(const float speed)
	{
		m_speed = speed;
	}

	void SpreadParticleSystem::setRotation(const float rot)
	{
		m_rotation = rot;
	}

	void SpreadParticleSystem::setGravity(const float gravity)
	{
		m_gravity = gravity;
	}

	void SpreadParticleSystem::setLifetime(const float time)
	{
		m_lifetime = time;
	}

	void SpreadParticleSystem::setScale(const float scale)
	{
		m_scale = scale;
	}


	void SpreadParticleSystem::setPositionError(const vector3& error)
	{
		m_positionError = error;
	}

	void SpreadParticleSystem::setSpeedError(const float error)
	{
		m_speedError = error;
	}

	void SpreadParticleSystem::setRotationError(const float error)
	{
		m_rotationError = error;
	}

	void SpreadParticleSystem::setGravityError(const float error)
	{
		m_gravityError = error;
	}

	void SpreadParticleSystem::setLifetimeError(const float error)
	{
		m_lifetimeError = error;
	}

	void SpreadParticleSystem::setScaleError(const float error)
	{
		m_scaleError = error;
	}

	// Private Functions
	Particle SpreadParticleSystem::m_generateRandomParticle(const vector3& pos)
	{
		// Start Position Randomizing
		vector3 randomizedPosition;

		if (m_positionError.x != 0.0f && m_positionError.y != 0.0f && m_positionError.z != 0.0f)
		{
			randomizedPosition =
				vector3
				(
					s_randomSign() * (float)(rand() % (int)(m_positionError.x * SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER)) / SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER,
					s_randomSign() * (float)(rand() % (int)(m_positionError.y * SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER)) / SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER,
					s_randomSign() * (float)(rand() % (int)(m_positionError.z * SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER)) / SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER
				)
				+ pos;
		}
		else
		{
			randomizedPosition = pos;
		}

		// Speed Randomizing
		float randomizedSpeed;

		if (m_rotationError != 0.0f)
		{
			randomizedSpeed = s_randomSign() * (float)(rand() % (int)(m_speedError * SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER)) / SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER + m_speed;
		}
		else
		{
			randomizedSpeed = m_speed;
		}

		// Rotation Randomizing
		float randomizedRotation;

		if (m_rotationError != 0.0f)
		{
			randomizedRotation = s_randomSign() * (float)(rand() % (int)(m_rotationError * SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER)) / SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER + m_rotation;
		}
		else
		{
			randomizedRotation = m_rotation;
		}

		// Gravity Randomizing
		float randomizedGravity;

		if (m_gravityError != 0.0f)
		{
			randomizedGravity = s_randomSign() * (float)(rand() % (int)(m_gravityError * SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER)) / SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER + m_gravity;
		}
		else
		{
			randomizedGravity = m_gravity;
		}

		// Lifetime Randomizing
		float randomizedLifetime;

		if (m_lifetimeError != 0.0f)
		{
			randomizedLifetime = s_randomSign() * (float)(rand() % (int)(m_lifetimeError * SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER)) / SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER + m_lifetime;
		}
		else
		{
			randomizedLifetime = m_lifetime;
		}

		// Scale Randomizing
		float randomizedScale;

		if (m_scaleError != 0.0f)
		{
			randomizedScale = s_randomSign() * (float)(rand() % (int)(m_scaleError * SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER)) / SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER + m_scale;
		}
		else
		{
			randomizedScale = m_scale;
		}

		// Direction Randomizings
		vector3 randomizedDirection(
			((float)(rand() % (int)(SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER) * 2) / SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER - 1.0f) * randomizedSpeed,
			((float)(rand() % (int)(SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER) * 2) / SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER - 1.0f) * randomizedSpeed,
			((float)(rand() % (int)(SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER) * 2) / SPREAD_PARTICLE_SYSTEM_ACCURACY_DIVIDER - 1.0f) * randomizedSpeed
		);

		// Finishing
		Particle result(randomizedPosition, randomizedDirection, randomizedLifetime);
		result.setGravity(randomizedGravity);
		result.setRotation(randomizedRotation);
		result.setScale(randomizedScale);


		return result;
	}

}