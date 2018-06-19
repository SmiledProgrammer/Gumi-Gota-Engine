#ifndef REXER_WALKING_CAMERA_3D_H
#define REXER_WALKING_CAMERA_3D_H



/* INCLUDES */
// Header Includes
#include "../../Gumi Gota/src/GumiGota.h"



namespace rexer
{
	
	using namespace gg;


	class WalkingCamera3D : public MoveableCamera3D
	{
	protected:
		/* Variables */
		float m_walkingSpeed; // speed per second that camera is getting when moving; stored in units per second
		float m_jumpingSpeed; // speed that camera is getting (in +Y direction) when it jumps; stored in units per second
		float m_gravitionalAcceleration; // speed per second that camera has falling with; stored in units per second^2
		float m_speedWhileInAir; // speed per second that camera is getting when moving in air; stored in units per second

		bool m_inAir;
		vector2 m_lastMousePosition;

		int m_forwardKey, m_backwardKey, m_leftKey, m_rightKey, m_jumpKey;
		vector2 m_sensitivity;

	public:
		/* Constructors */
		WalkingCamera3D(const vector3& pos, const float aspectRatio, Window* window);

		/* Functions */
		void update(const float deltaTime);

		// Setters
		void setWalkingSpeed(const float speed); // speed per second that camera is getting when moving; stored in units per second
		void setJumpingSpeed(const float speed); // speed that camera is getting (in +Y direction) when it jumps; stored in units per second
		void setGravitionalAcceleration(const float accel); // speed per second that camera has falling with; stored in units per second^2
		void setSpeedWhileInAir(const float speed); // speed per second that camera is getting when moving in air; stored in units per second

		void setForwardKey(const int key);
		void setBackwardKey(const int key);
		void setLeftKey(const int key);
		void setRightKey(const int key);
		void setJumpKey(const int key);
		void setKeyControls(const int forwardKey, const int backwardKey, const int leftKey, const int rightKey, const int jumpKey);
		void setSensitivity(const vector2& sens);

	};

}



#endif