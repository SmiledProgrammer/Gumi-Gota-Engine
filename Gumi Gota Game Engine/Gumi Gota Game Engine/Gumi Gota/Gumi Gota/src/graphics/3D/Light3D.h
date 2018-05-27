#ifndef GUMIGOTA_LIGHT3D_H
#define GUMIGOTA_LIGHT3D_H



/* INCLUDES */
// Header Includes
#include "../../maths/vectors/vector3.h"

#include "../Color.h"



namespace gg
{

	class Light3D
	{
	protected:
		/* Variables */
		vector3 m_position;
		Color m_color;
		vector3 m_attenuation;

	public:
		/* Constructors */
		Light3D(const vector3& pos);
		Light3D(const vector3& pos, const Color& color);
		Light3D(const vector3& pos, const Color& color, const vector3& attenuation);

		/* Functions */
		// Setters
		void move(const vector3& movement);
		void setPosition(const vector3& pos);

		void setColor(const Color& color);

		void increaseAttenuation(const vector3& value);
		void setAttenuation(const vector3& value);

		// Getters
		inline const vector3& getPosition()    const { return m_position;    }
		inline const Color&   getColor()       const { return m_color;       }
		inline const vector3& getAttenuation() const { return m_attenuation; }

	};

}



#endif