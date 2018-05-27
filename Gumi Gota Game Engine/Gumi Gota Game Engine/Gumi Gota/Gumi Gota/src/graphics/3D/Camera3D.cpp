
/* INCLUDES */
// Self Include
#include "Camera3D.h"



/* MACROS */
#define CAMERA3D_DEFAULT_UP_VECTOR vector3(0.0f, 1.0f, 0.0f)
#define CAMERA3D_DEFAULT_FOV 1.5f



namespace gg
{

	/* Constructors */
	Camera3D::Camera3D(const vector3& pos, const float aspectRatio)
		: m_position(pos), m_upVector(CAMERA3D_DEFAULT_UP_VECTOR), m_aspectRatio(aspectRatio), m_pitch(0.0f), m_yaw(0.0f), m_fov(CAMERA3D_DEFAULT_FOV)
	{}

	Camera3D::Camera3D(const vector3& pos, const float aspectRatio, const float fov)
		: m_position(pos), m_upVector(CAMERA3D_DEFAULT_UP_VECTOR), m_aspectRatio(aspectRatio), m_pitch(0.0f), m_yaw(0.0f), m_fov(fov)
	{}

	/* Functions */
	void Camera3D::invertPitch()
	{
		m_pitch = -m_pitch;
	}

	// Setters
	void Camera3D::move(const vector3& movement)
	{
		m_position += movement;
	}

	void Camera3D::addPitch(const float movement)
	{
		m_pitch += movement;
	}

	void Camera3D::addYaw(const float movement)
	{
		m_yaw += movement;
	}

	void Camera3D::addAngle(const float pitchMovement, const float yawMovement)
	{
		m_pitch += pitchMovement;
		m_yaw += yawMovement;
	}


	void Camera3D::setPosition(const vector3& pos)
	{
		m_position = pos;
	}

	void Camera3D::setUpVector(const vector3& vec)
	{
		m_upVector = vec;
	}

	void Camera3D::setAspectRatio(const float ratio)
	{
		m_aspectRatio = ratio;
	}

	void Camera3D::updateWindowSize(const Window& window)
	{
		m_aspectRatio = window.getAspectRatio();
	}

	void Camera3D::setPitch(const float value)
	{
		m_pitch = value;
	}

	void Camera3D::setYaw(const float value)
	{
		m_yaw = value;
	}

	void Camera3D::setAngle(const float pitch, const float yaw)
	{
		m_pitch = pitch;
		m_yaw = yaw;
	}

	void Camera3D::setFOV(const float value)
	{
		m_fov = value;
	}


}