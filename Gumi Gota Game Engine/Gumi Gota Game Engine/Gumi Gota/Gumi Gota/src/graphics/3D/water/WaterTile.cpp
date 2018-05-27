
/* INCLUDES */
// Self Include
#include "WaterTile.h"



/* MACROS */
#define WATER_TILE_DEFAULT_SCALE 1.0f
#define WATER_TILE_DEFAULT_ROTATION 0.0f

#define WATER_TILE_DEFAULT_MOVEMENT_FACTOR 3.0f
#define WATER_TILE_DEFAULT_TILING_FACTOR 6.0f
#define WATER_TILE_DEFAULT_WAVE_STRENGTH 0.02f



namespace gg
{

	/* Constructors */
	WaterTile::WaterTile(const vector3& pos)
		: m_position(pos), m_rotation(WATER_TILE_DEFAULT_ROTATION), m_scale(WATER_TILE_DEFAULT_SCALE),
		  m_movementFactor(WATER_TILE_DEFAULT_MOVEMENT_FACTOR),
		  m_tilingFactor(WATER_TILE_DEFAULT_TILING_FACTOR),
		  m_waveStrength(WATER_TILE_DEFAULT_WAVE_STRENGTH)
	{}

	WaterTile::WaterTile(const vector3& pos, const float scale)
		: m_position(pos), m_rotation(WATER_TILE_DEFAULT_ROTATION), m_scale(scale),
		  m_movementFactor(WATER_TILE_DEFAULT_MOVEMENT_FACTOR),
		  m_tilingFactor(WATER_TILE_DEFAULT_TILING_FACTOR),
		  m_waveStrength(WATER_TILE_DEFAULT_WAVE_STRENGTH)
	{}

	/* Functions */
	// Setters
	void WaterTile::move(const vector3& movement)
	{
		m_position += movement;
	}

	void WaterTile::rotate(const float rot)
	{
		m_rotation += rot;
	}

	void WaterTile::scale(const float scale)
	{
		m_scale *= scale;
	}

	void WaterTile::addMovementFactor(const float value)
	{
		m_movementFactor += value;
	}


	void WaterTile::setPosition(const vector3& pos)
	{
		m_position = pos;
	}

	void WaterTile::setRotation(const float rot)
	{
		m_rotation = rot;
	}

	void WaterTile::setScale(const float scale)
	{
		m_scale = scale;
	}

	void WaterTile::setMovementFector(const float value)
	{
		m_movementFactor = value;
	}

	void WaterTile::setTilingFactor(const float value)
	{
		m_tilingFactor = value;
	}

	void WaterTile::setWaveStrength(const float value)
	{
		m_waveStrength = value;
	}

}