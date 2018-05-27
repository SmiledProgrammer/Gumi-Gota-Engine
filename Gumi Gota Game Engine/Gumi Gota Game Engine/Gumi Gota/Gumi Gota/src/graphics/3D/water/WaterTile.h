#ifndef GUMIGOTA_WATER_TILE_H
#define GUMIGOTA_WATER_TILE_H



/* INCLUDES */
// Header Includes
#include "../../../maths/vectors/vector3.h"



namespace gg
{

	class WaterTile
	{
	protected:
		/* Variables */
		vector3 m_position;
		float m_rotation; //stored in radians
		float m_scale;

		float m_movementFactor;
		float m_tilingFactor;
		float m_waveStrength;

	public:
		/* Constructors */
		WaterTile(const vector3& pos);
		WaterTile(const vector3& pos, const float scale);

		/* Functions */
		// Setters
		void move(const vector3& movement);
		void rotate(const float rot);
		void scale(const float scale);
		void addMovementFactor(const float value);

		void setPosition(const vector3& pos);
		void setRotation(const float rot);
		void setScale(const float scale);
		void setMovementFector(const float value);
		void setTilingFactor(const float value);
		void setWaveStrength(const float value);

		// Getters
		inline const vector3& getPosition() const { return m_position; }
		inline const float    getRotation() const { return m_rotation; }
		inline       float    getScale()    const { return m_scale;    }

		inline float getMovementFactor() const { return m_movementFactor; }
		inline float getTilingFactor()   const { return m_tilingFactor;   }
		inline float getWaveStrength()   const { return m_waveStrength;   }

	};

}



#endif