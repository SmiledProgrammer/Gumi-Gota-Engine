#ifndef GUMIGOTA_LIGHT2D_H
#define GUMIGOTA_LIGHT2D_H



/* INCLUDES */
// Header Includes
#include "../../maths/vectors/vector2.h"
#include "../../maths/vectors/vector3.h"

#include "../Color.h"



namespace gg
{

	class Light2D
	{
	protected:
		/* Variables */
		vector2 m_position;
		Color m_color;
		vector3 m_attenuation;

	public:
		/* Constructors */
		Light2D(const vector2& pos);
		Light2D(const vector2& pos, const Color& color);
		Light2D(const vector2& pos, const Color& color, const vector3& attenuation);

		/* Functions */
		// Setters
		void move(const vector2& movement);
		void setPosition(const vector2& pos);

		void setColor(const Color& color);

		void increaseAttenuation(const vector3& value);
		void setAttenuation(const vector3& value);

		// Getters
		inline const vector2& getPosition()    const { return m_position;    }
		inline const Color&   getColor()       const { return m_color;       }
		inline const vector3& getAttenuation() const { return m_attenuation; }

	};

}



#endif