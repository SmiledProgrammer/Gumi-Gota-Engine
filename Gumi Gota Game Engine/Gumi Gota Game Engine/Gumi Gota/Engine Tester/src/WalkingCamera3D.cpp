
/* INCLUDES */
// Self Include
#include "WalkingCamera3D.h"

#include <iostream> /// remove l8r



/* MACROS */
#define FLYING_CAMERA_3D_DEFAULT_WALKING_SPEED				2000.0f
#define FLYING_CAMERA_3D_DEFAULT_JUMPING_SPEED				4000.0f
#define FLYING_CAMERA_3D_DEFAULT_GRAVITIONAL_ACCELERATION	40.0f
#define FLYING_CAMERA_3D_DEFAULT_SPEED_WHILE_IN_AIR			1.2f * FLYING_CAMERA_3D_DEFAULT_WALKING_SPEED
#define FLYING_CAMERA_3D_DEFAULT_SENSITIVTY					50.0f, 50.0f

#define FLYING_CAMERA_3D_DEFAULT_FORWARD_KEY	GLFW_KEY_W
#define FLYING_CAMERA_3D_DEFAULT_BACKWARD_KEY	GLFW_KEY_S
#define FLYING_CAMERA_3D_DEFAULT_LEFT_KEY		GLFW_KEY_A
#define FLYING_CAMERA_3D_DEFAULT_RIGHT_KEY		GLFW_KEY_D
#define FLYING_CAMERA_3D_DEFAULT_JUMP_KEY		GLFW_KEY_SPACE



namespace rexer
{

	/* Constructors */
	WalkingCamera3D::WalkingCamera3D(const vector3& pos, const float aspectRatio, Window* window)
		: MoveableCamera3D(pos, aspectRatio, window),
		  m_walkingSpeed(FLYING_CAMERA_3D_DEFAULT_WALKING_SPEED),
		  m_jumpingSpeed(FLYING_CAMERA_3D_DEFAULT_JUMPING_SPEED),
		  m_gravitionalAcceleration(FLYING_CAMERA_3D_DEFAULT_GRAVITIONAL_ACCELERATION),
		  m_speedWhileInAir(FLYING_CAMERA_3D_DEFAULT_SPEED_WHILE_IN_AIR),
		  m_sensitivity(FLYING_CAMERA_3D_DEFAULT_SENSITIVTY),
		  m_inAir(true),
		  m_forwardKey(FLYING_CAMERA_3D_DEFAULT_FORWARD_KEY), m_backwardKey(FLYING_CAMERA_3D_DEFAULT_BACKWARD_KEY), m_leftKey(FLYING_CAMERA_3D_DEFAULT_LEFT_KEY), m_rightKey(FLYING_CAMERA_3D_DEFAULT_RIGHT_KEY), m_jumpKey(GLFW_KEY_SPACE)
	{}

	/* Functions */
	void WalkingCamera3D::update(const float deltaTime)
	{
		// Init
		float walkingSpeedX = 0.0f;
		float walkingSpeedZ = 0.0f;

		// X/Z Position Movement
		if (!m_inAir)
		{
			if (m_window->isKeyPressed(m_forwardKey))
			{
				walkingSpeedX += -sine(m_yaw);
				walkingSpeedZ += -cosine(m_yaw);
			}

			if (m_window->isKeyPressed(m_backwardKey))
			{
				walkingSpeedX += sine(m_yaw);
				walkingSpeedZ += cosine(m_yaw);
			}

			if (m_window->isKeyPressed(m_leftKey))
			{
				float perpendicularAngle = m_yaw - GUMIGOTA_PI_DIVIDED_BY_2;

				walkingSpeedX += sine(perpendicularAngle);
				walkingSpeedZ += cosine(perpendicularAngle);
			}

			if (m_window->isKeyPressed(m_rightKey))
			{
				float perpendicularAngle = m_yaw - GUMIGOTA_PI_DIVIDED_BY_2;

				walkingSpeedX += -sine(perpendicularAngle);
				walkingSpeedZ += -cosine(perpendicularAngle);
			}

			if (m_window->isKeyPressed(m_forwardKey) || m_window->isKeyPressed(m_backwardKey) || m_window->isKeyPressed(m_leftKey) || m_window->isKeyPressed(m_rightKey))
			{
				// Normalizing Destination Speed Vector
				float walkingSpeedMagnitudeXZ = squareRoot(walkingSpeedX * walkingSpeedX + walkingSpeedZ * walkingSpeedZ);

				if (walkingSpeedMagnitudeXZ != 0.0f)
				{
					walkingSpeedX /= walkingSpeedMagnitudeXZ;
					walkingSpeedZ /= walkingSpeedMagnitudeXZ;
				}
			}

			if (m_window->isKeyPressed(m_jumpKey))
			{
				m_velocity.x += walkingSpeedX * m_speedWhileInAir;
				m_velocity.z += walkingSpeedZ * m_speedWhileInAir;
			}
			else
			{
				// Getting Final Walking Speed
				walkingSpeedX *= m_walkingSpeed;
				walkingSpeedZ *= m_walkingSpeed;
			}
		}

		// Jump Movement
		if (m_window->isKeyPressed(m_jumpKey) && !m_inAir)
		{
			m_inAir = true;
			m_velocity.y = m_jumpingSpeed;
		}

		if (m_inAir)
		{
			m_velocity.y -= m_gravitionalAcceleration;
		}

		// Moving Camera
		move(vector3(m_velocity.x + walkingSpeedX, m_velocity.y, m_velocity.z + walkingSpeedZ) * deltaTime);

		// Angle Movement
		vector2 currentMousePosition = m_window->getMousePosition();
		vector2 mouseDifference = m_lastMousePosition - currentMousePosition;

		addYaw(mouseDifference.x * m_sensitivity.x * deltaTime);
		addPitch(mouseDifference.y * m_sensitivity.y * deltaTime);

		m_pitch = clamp(m_pitch, -GUMIGOTA_PI_DIVIDED_BY_2, GUMIGOTA_PI_DIVIDED_BY_2);

		// Centering Cursor
		m_window->setMousePosition(vector2((float)(m_window->getWidth() / 2.0f), (float)(m_window->getHeight() / 2.0f)));
		m_lastMousePosition = vector2((float)(m_window->getWidth() / 2.0f), (float)(m_window->getHeight() / 2.0f));


		
		/// To remove l8r
		if (m_position.y < 1.5f)
		{
			m_position.y = 1.5f;
			m_velocity.y = 0.0f;
			m_velocity.x = 0.0f;
			m_velocity.z = 0.0f;
			m_inAir = false;
		}
	}

	// Setters
	void WalkingCamera3D::setWalkingSpeed(const float speed)
	{
		m_walkingSpeed = speed;
	}

	void WalkingCamera3D::setJumpingSpeed(const float speed)
	{
		m_jumpingSpeed = speed;
	}

	void WalkingCamera3D::setGravitionalAcceleration(const float accel)
	{
		m_gravitionalAcceleration = accel;
	}

	void WalkingCamera3D::setSpeedWhileInAir(const float speed)
	{
		m_speedWhileInAir = speed;
	}


	void WalkingCamera3D::setForwardKey(const int key)
	{
		m_forwardKey = key;
	}

	void WalkingCamera3D::setBackwardKey(const int key)
	{
		m_backwardKey = key;
	}

	void WalkingCamera3D::setLeftKey(const int key)
	{
		m_leftKey = key;
	}

	void WalkingCamera3D::setRightKey(const int key)
	{
		m_rightKey = key;
	}

	void WalkingCamera3D::setJumpKey(const int key)
	{
		m_jumpKey = key;
	}

	void WalkingCamera3D::setKeyControls(const int forwardKey, const int backwardKey, const int leftKey, const int rightKey, const int jumpKey)
	{
		m_forwardKey = forwardKey;
		m_backwardKey = backwardKey;
		m_leftKey = leftKey;
		m_rightKey = rightKey;
		m_jumpKey = jumpKey;
	}

	void WalkingCamera3D::setSensitivity(const vector2& sens)
	{
		m_sensitivity = sens;
	}

}