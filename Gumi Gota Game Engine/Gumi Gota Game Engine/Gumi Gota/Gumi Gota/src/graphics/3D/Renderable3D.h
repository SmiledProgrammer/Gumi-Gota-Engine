#ifndef GUMIGOTA_RENDERABLE3D_H
#define GUMIGOTA_RENDERABLE3D_H



/* INCLUDES */
// Header Includes
#include "Model.h"

#include "../../maths/vectors/vector3.h"



namespace gg
{

	class Renderable3D
	{
	protected:
		/* Variables */
		vector3 m_position;
		vector3 m_rotation; //stored in radians
		float m_scale;

		Model* m_model;

		unsigned int m_textureAtlasIndex;

	public:
		/* Constructors */
		Renderable3D(Model* model, const vector3& pos);
		Renderable3D(Model* model, const vector3& pos, const unsigned int atlasIndex);

		/* Functions */
		// Setters
		void move(const vector3& movement); //moves entity relatively to its current position
		void rotate(const vector3& rot); //rotates entity relatively to its current rotation
		void scale(const float scale); //scales entity relatively to its current scale

		void setPosition(const vector3& pos); //moves entity ignoring its current position
		void setRotation(const vector3& rot); //rotates entity ignoring its current rotation
		void setScale(const float scale); //scales entity ignoring its current scale

		void setTextureAtlasIndex(const unsigned int index);

		// Getters
		vector2 getTextureOffset();

		inline const vector3& getPosition() const { return m_position; }
		inline const vector3& getRotation() const { return m_rotation; }
		inline       float    getScale()    const { return m_scale;    }

		inline Model* getModel() const { return m_model; }

		inline unsigned int getTextureAtlasIndex() const { return m_textureAtlasIndex; }

	};

}



#endif