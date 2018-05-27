#ifndef GUMIGOTA_CAMERA3D_H
#define GUMIGOTA_CAMERA3D_H



/* INCLUDES */
// Header Includes
#include "../../maths/vectors/vector3.h"

#include "../Window.h"



namespace gg
{

	class Camera3D
	{
	protected:
		/* Variables */
		vector3 m_position;
		vector3 m_upVector;
		float m_aspectRatio;
		float m_pitch, m_yaw; //stored in radians
		float m_fov; //stored in radians

	public:
		/* Constructors */
		Camera3D(const vector3& pos, const float aspectRatio);
		Camera3D(const vector3& pos, const float aspectRatio, const float fov);

		/* Functions */
		void invertPitch();

		// Setters
		void move(const vector3& movement);
		void addPitch(const float movement);
		void addYaw(const float movement);
		void addAngle(const float pitchMovement, const float yawMovement);

		void setPosition(const vector3& pos);
		void setUpVector(const vector3& vec);
		void setAspectRatio(const float ratio);
		void updateWindowSize(const Window& window);
		void setPitch(const float value);
		void setYaw(const float value);
		void setAngle(const float pitch, const float yaw);
		void setFOV(const float value);

		// Getters
		inline const vector3& getPosition()    const { return m_position;    }
		inline const vector3& getUpVector()    const { return m_upVector;    }
		inline       float    getAspectRatio() const { return m_aspectRatio; }
		inline       float    getPitch()       const { return m_pitch;       }
		inline       float    getYaw()         const { return m_yaw;         }
		inline       float    getFOV()         const { return m_fov;         }
		

	};

}



#endif