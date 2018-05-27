
/* INCLUDES */
// Self Include
#include "Particle.h"

#include <iostream> ///remove l8r



/* MACROS */
#define PARTICLE_DEFAULT_GRAVITY 10.0f
#define PARTICLE_DEFAULT_ROTATION 0.0f
#define PARTICLE_DEFAULT_SCALE 1.0f

#define PARTICLE_DEFAULT_UPDATE_INTERVAL 0.001f



namespace gg
{

	/* Constructors */
	Particle::Particle(const vector3& pos, const vector3& velocity, const float lifetime)
		: m_position(pos), m_velocity(velocity), m_lifetime(lifetime), m_gravity(PARTICLE_DEFAULT_GRAVITY), m_rotation(PARTICLE_DEFAULT_ROTATION), m_scale(PARTICLE_DEFAULT_SCALE),
		  m_updateInterval(PARTICLE_DEFAULT_UPDATE_INTERVAL),
		  m_textureAtlasIndex(0)
	{}

	Particle::Particle(const vector3& pos, const vector3& velocity, const float lifetime, const float gravity, const float rot, const float scale)
		: m_position(pos), m_velocity(velocity), m_lifetime(lifetime), m_gravity(gravity), m_rotation(rot), m_scale(scale),
		  m_updateInterval(PARTICLE_DEFAULT_UPDATE_INTERVAL),
		  m_textureAtlasIndex(0)
	{}

	/* Functions */
	bool Particle::update(const Camera3D& cam)
	{
		// Init
		float deltaTime = m_updateTimer.elapsed();

		bool alive = (m_lifeTimer.elapsed() < m_lifetime); // Checking if Particle is Alive

		m_distanceFromCamera = (m_position - cam.getPosition()).lengthSquared();

		// Updating Particle
		if (deltaTime > m_updateInterval)
		{
			// Moving Particle
			if (alive)
			{
				m_velocity.y -= m_gravity * deltaTime;

				m_position += m_velocity * deltaTime;
			}

			// Resetting Update Timer
			m_updateTimer.reset();
		}

		
		return alive;
	}

	void Particle::updateTransitionStuff(const unsigned int phaseCount, const unsigned int startIndex)
	{
		// Calculations
		float lifeFactor = getTimeAlive() / getLifetime();
		float atlasProgression = lifeFactor * phaseCount;

		// Updating Texture Atlas Index
		m_textureAtlasIndex = startIndex + (unsigned int)floor(atlasProgression);
	}


	void Particle::resetLifeTimer()
	{
		m_lifeTimer.reset();
	}

	// Setters
	void Particle::move(const vector3& movement)
	{
		m_position += movement;
	}

	void Particle::setPosition(const vector3& pos)
	{
		m_position = pos;
	}

	void Particle::rotate(const float rot)
	{
		m_rotation += rot;
	}

	void Particle::setRotation(const float rot)
	{
		m_rotation = rot;
	}

	void Particle::setLifetime(const float time)
	{
		m_lifetime = time;
	}

	void Particle::setGravity(const float value)
	{
		m_gravity = value;
	}

	void Particle::scale(const float value)
	{
		m_scale *= value;
	}

	void Particle::setScale(const float value)
	{
		m_scale = value;
	}

	void Particle::addVelocity(const vector3& vel)
	{
		m_velocity += vel;
	}

	void Particle::setVelocity(const vector3& vel)
	{
		m_velocity = vel;
	}


	void Particle::setUpdateInterval(const float time)
	{
		m_updateInterval = time;
	}

	
	void Particle::setTextureAtlasIndex(const unsigned int index)
	{
		m_textureAtlasIndex = index;
	}

}