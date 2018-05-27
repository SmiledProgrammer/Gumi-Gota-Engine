#pragma once



/* INCLUDES */
// Gumi Gota Engine Includes
#include "../../Gumi Gota/src/GumiGota.h"



namespace gg
{

	class MoveableCamera : public Camera3D
	{
	private:
		Timer m_updateTimer;

		float m_movementSpeed;
		vector2 m_sensitivity;
		vector2 m_lastMousePosition;

	public:
		MoveableCamera(const vector3& pos, const float aspectRatio);

		void update(Window& window);

		void setSpeed(const float speed);
		void setSensitivity(const vector2& sens);

	};

}