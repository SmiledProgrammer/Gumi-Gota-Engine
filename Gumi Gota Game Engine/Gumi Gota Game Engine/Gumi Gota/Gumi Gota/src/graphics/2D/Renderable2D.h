#ifndef GUMIGOTA_RENDERABLE2D_H
#define GUMIGOTA_RENDERABLE2D_H



/* INCLUDES */
// Header Includes
#include "../../maths/vectors/vector2.h"

#include "../buffers/VertexArray.h"
#include "../buffers/IndexBuffer.h"



namespace gg
{

	class Renderable2D
	{
	protected:
		/* Variables */
		vector2 m_position;
		vector2 m_size;
		float m_rotation; //stored in radians
		vector2 m_origin; //used for different rotation points

	public:
		/* Constructors */
		Renderable2D(const vector2& pos, const vector2& size); //default constructor
		Renderable2D(const vector2& pos, const vector2& size, const float rot); //all parameters constructor

		/* Functions */
		// Setters
		void move(const vector2& movement); //changing position relatively to current position
		void addSize(const vector2& size); //changing size relatively to current size
		void rotate(const float rot); //changing rotation relatively to current rotation
		void moveOrigin(const vector2& movement); //changing origin relatively to current origin position

		void setPosition(const vector2& pos); //changing position ignoring current position
		void setSize(const vector2& size); //changing size ignoring current size
		void setRotation(const float rot); //changing rotation ignoring current rotation
		void setOrigin(const vector2& origin); //changing origin ignoring current origin

		// Getters
		inline const vector2& getPosition() const { return m_position; }
		inline const vector2& getSize()     const { return m_size;     }
		inline       float    getRotation() const { return m_rotation; }
		inline const vector2& getOrigin()   const { return m_origin;   }

	};

}



#endif