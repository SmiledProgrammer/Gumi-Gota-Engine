#ifndef GUMIGOTA_MATRIX4_H
#define GUMIGOTA_MATRIX4_H



/* INCLUDES */
// Header Includes
#include "../vectors/vector3.h"



namespace gg
{

	struct matrix4
	{
		/* Variables */
		float elements[4 * 4];

		/* Constructors */
		matrix4();
		matrix4(const float& diagonal);
		matrix4(const float values[4 * 4]);

		/* Functions */
		matrix4& multiply(const matrix4 other);

		float determinant() const;

		// Matrices Functions
		static matrix4 identity();


		static matrix4 invert(const matrix4& mat);


		static matrix4 translation(const vector3& position);
		static matrix4 rotation(const float radians, const vector3& axis);
		static matrix4 scale(const float scale);
		static matrix4 scale(const vector3& scale);

		static matrix4 model(const vector3& position, const float rotX, const float rotY, const float rotZ, const float scale); // rotations are given in radians
		static matrix4 model(const vector3& position, const float rotX, const float rotY, const float rotZ, const vector3& scale); // rotations are given in radians
		static matrix4 model(const vector3& position, const float rot, const vector3& rotAxis, const float scale); // rotations are given in radians
		static matrix4 model(const vector3& position, const float rot, const vector3& rotAxis, const vector3& scale); // rotations are given in radians


		static matrix4 fpsView(const vector3& position, const float pitch, const float yaw); // pitch and yaw are given in radians
		static matrix4 lookAtView(const vector3& cameraPosition, const vector3& lookAtPosition, const vector3& upVector);

		static matrix4 orthographic(const float left, const float right, const float bottom, const float top, const float near, const float far);
		static matrix4 projection(const float aspectRatio, const float fov, const float zNear, const float zFar); // fov is given in radians

		/* Operator Overloads */
		friend matrix4 operator*(matrix4 left, const matrix4& right);

		matrix4& operator*=(const matrix4& other);

	};

}



#endif