#ifndef GUMIGOTA_CAMERA2D_H
#define GUMIGOTA_CAMERA2D_H



/* INCLUDES */
// Header Includes
#include "../../maths/vectors/vector2.h"



namespace gg
{

	class Camera2D
	{
	protected:
		/* Variables */
		vector2 m_position;
		vector2 m_halfOfDisplaySize;

	public:
		/* Constructors */
		Camera2D(const vector2& pos, const vector2& displaySize);

		/* Functions */
		void move(const vector2& movement);
		void setPosition(const vector2& pos);

		// Getters
		inline const vector2& getPosition()          const { return m_position;          }
		inline const vector2& getHalfOfDisplaySize() const { return m_halfOfDisplaySize; }

	};

}



#endif