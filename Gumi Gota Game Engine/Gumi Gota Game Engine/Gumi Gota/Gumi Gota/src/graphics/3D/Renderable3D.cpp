
/* INCLUDES */
// Self Include
#include "Renderable3D.h"



/* MACROS */
#define RENDERABLE3D_DEFAULT_ROTATION vector3(0.0f)
#define RENDERABLE3D_DEFAULT_SCALE 1.0f



namespace gg
{

	/* Constructors */
	Renderable3D::Renderable3D(Model* model, const vector3& pos)
		: m_position(pos), m_rotation(RENDERABLE3D_DEFAULT_ROTATION), m_scale(RENDERABLE3D_DEFAULT_SCALE),
		  m_model(model), m_textureAtlasIndex(0)
	{}

	Renderable3D::Renderable3D(Model* model, const vector3& pos, const unsigned int atlasIndex)
		: m_position(pos), m_rotation(RENDERABLE3D_DEFAULT_ROTATION), m_scale(RENDERABLE3D_DEFAULT_SCALE),
		  m_model(model), m_textureAtlasIndex(atlasIndex)
	{}

	/* Functions */
	// Setters
	void Renderable3D::move(const vector3& movement)
	{
		m_position += movement;
	}

	void Renderable3D::rotate(const vector3& rot)
	{
		m_rotation += rot;
	}

	void Renderable3D::scale(const float scale)
	{
		m_scale *= scale;
	}


	void Renderable3D::setPosition(const vector3& pos)
	{
		m_position = pos;
	}

	void Renderable3D::setRotation(const vector3& rot)
	{
		m_rotation = rot;
	}

	void Renderable3D::setScale(const float scale)
	{
		m_scale = scale;
	}


	void Renderable3D::setTextureAtlasIndex(const unsigned int index)
	{
		m_textureAtlasIndex = index;
	}

	// Getters
	vector2 Renderable3D::getTextureOffset()
	{
		unsigned int column = m_textureAtlasIndex % m_model->getTextureRows();
		unsigned int row = m_model->getTextureRows() - 1 - m_textureAtlasIndex / m_model->getTextureRows(); // Transforming Row so It Starts from Top Right and Goes to Left/Bottom

		return vector2((float)column / (float)m_model->getTextureRows(), (float)row / (float)m_model->getTextureRows());
	}

}