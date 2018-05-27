#ifndef GUMIGOTA_PARTICLE_H
#define GUMIGOTA_PARTICLE_H



/* INCLUDES */
// Header Includes
#include "../Camera3D.h"

#include "../../../maths/vectors/vector3.h"

#include "../../../utils/Timer.h"

#include "../../buffers/VertexArray.h"
#include "../../buffers/IndexBuffer.h"

#include "../../Texture.h"



namespace gg
{

	class Particle
	{
	protected:
		/* Variables */
		vector3 m_position;
		vector3 m_velocity;
		float m_lifetime; //stored in seconds
		float m_gravity;
		float m_rotation; //stored in radians
		float m_scale;

		Timer m_lifeTimer;
		Timer m_updateTimer;
		float m_updateInterval;

		unsigned int m_textureAtlasIndex;
		
		float m_distanceFromCamera;

	public:
		/* Constructors */
		Particle(const vector3& pos, const vector3& velocity, const float lifetime);
		Particle(const vector3& pos, const vector3& velocity, const float lifetime, const float gravity, const float rot, const float scale);

		/* Functions */
		bool update(const Camera3D& cam); //returns true if particle is still alive
		void updateTransitionStuff(const unsigned int phaseCount, const unsigned int startIndex);

		void resetLifeTimer(); //particle's lifetime timer is getting back to 0

		// Setters
		void move(const vector3& movement);
		void setPosition(const vector3& pos);
		void rotate(const float rot); //rotation is given in radians
		void setRotation(const float rot); //rotation is given in radians
		void setLifetime(const float time); //time is given in seconds
		void setGravity(const float value);
		void scale(const float value);
		void setScale(const float value);
		void addVelocity(const vector3& vel);
		void setVelocity(const vector3& vel);

		void setUpdateInterval(const float time); //time between updates is stored in seconds

		void setTextureAtlasIndex(const unsigned int index);

		// Getters
		inline const vector3& getPosition() const { return m_position; }
		inline       float    getRotation() const { return m_rotation; } //rotation is stored in radians
		inline       float    getScale()    const { return m_scale;    }
		inline       float    getLifetime() const { return m_lifetime; } //returns time in seconds which particle will be living for

		inline float getTimeAlive() const { return m_lifeTimer.elapsed(); } //returns time in seconds since particle is alive (since last lifetime reset)

		inline unsigned int getTextureAtlasIndex() const { return m_textureAtlasIndex; }

		inline float getDistanceFromCamera() const { return m_distanceFromCamera; }

	};

}



#endif