
/* INCLUDES */
// Self Include
#include "MoveableCamera.h"



/* MACROS */
#define DEFAULT_CAMERA_SPEED 30.0f
#define DEFAULT_CAMERA_SENSITIVTY 1.0f, 1.0f



namespace gg
{

	MoveableCamera::MoveableCamera(const vector3& pos, const float aspectRatio)
		: Camera3D(pos, aspectRatio),
		  m_movementSpeed(DEFAULT_CAMERA_SPEED), m_sensitivity(DEFAULT_CAMERA_SENSITIVTY)
	{}



	void MoveableCamera::update(Window& window)
	{
		float deltaTime = m_updateTimer.elapsed();

		
		if (window.isKeyPressed(GLFW_KEY_W))
		{
			vector3 movement;

			float yHelper = (90.0f - absolute(m_pitch)) / 90.0f;

			movement.y = sine(m_pitch);
			movement.x = -sine(m_yaw) * yHelper;
			movement.z = -cosine(m_yaw) * yHelper;

			movement = normal(movement) * deltaTime;

			move(movement * m_movementSpeed);
		}

		if (window.isKeyPressed(GLFW_KEY_S))
		{
			vector3 movement;

			float yHelper = (90.0f - absolute(m_pitch)) / 90.0f;

			movement.y = -sine(m_pitch);
			movement.x = sine(m_yaw) * yHelper;
			movement.z = cosine(m_yaw) * yHelper;

			movement = normal(movement) * deltaTime;

			move(movement * m_movementSpeed);
		}

		if (window.isKeyPressed(GLFW_KEY_A))
		{
			vector3 movement;

			movement.y = 0.0f;
			movement.x = sine(toRadians(toDegrees(m_yaw) - 90.0f));
			movement.z = cosine(toRadians(toDegrees(m_yaw) - 90.0f));

			movement = normal(movement) * deltaTime;

			move(movement * m_movementSpeed);
		}

		if (window.isKeyPressed(GLFW_KEY_D))
		{
			vector3 movement;

			movement.y = 0.0f;
			movement.x = -sine(toRadians(toDegrees(m_yaw) - 90.0f));
			movement.z = -cosine(toRadians(toDegrees(m_yaw) - 90.0f));

			movement = normal(movement) * deltaTime;

			move(movement * m_movementSpeed);
		}


		

		// Pitch and Yaw Update
		vector2 currentMousePosition = window.getMousePosition();
		vector2 mouseDifference = m_lastMousePosition - currentMousePosition;

		addYaw(mouseDifference.x * m_sensitivity.x * deltaTime);
		addPitch(mouseDifference.y * m_sensitivity.y * deltaTime);

		// Clamping Pitch
		m_pitch = clamp(m_pitch, toRadians(-90.0f), toRadians(90.0f));

		// Centering Cursor
		window.setMousePosition(vector2((float)(window.getWidth() / 2.0f), (float)(window.getHeight() / 2.0f)));
		m_lastMousePosition = vector2((float)(window.getWidth() / 2.0f), (float)(window.getHeight() / 2.0f));

		// Resetting Update Timer
		m_updateTimer.reset();
	}


	void MoveableCamera::setSpeed(const float speed)
	{

	}

	void MoveableCamera::setSensitivity(const vector2& sens)
	{

	}

}