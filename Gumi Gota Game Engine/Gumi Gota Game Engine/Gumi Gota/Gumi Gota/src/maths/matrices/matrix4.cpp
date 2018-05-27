
/* INCLUDES */
// Self Include
#include "matrix4.h"

// Header Includes
#include "../trigonometry/Trigonometry.h"

#include "../geometry/VectorTransformations.h"



namespace gg
{

	/* Constructors */
	matrix4::matrix4()
	{
		for (int i = 0; i < 4 * 4; i++)
			elements[i] = 0.0f;
	}

	matrix4::matrix4(const float& diagonal)
	{
		for (int i = 0; i < 4 * 4; i++)
			elements[i] = 0.0f;

		elements[0 + 0 * 4] = diagonal;
		elements[1 + 1 * 4] = diagonal;
		elements[2 + 2 * 4] = diagonal;
		elements[3 + 3 * 4] = diagonal;
	}

	matrix4::matrix4(const float values[4 * 4])
	{
		for (int i = 0; i < 4 * 4; i++)
			elements[i] = values[i];
	}

	/* Functions */
	matrix4& matrix4::multiply(const matrix4 other)
	{
		matrix4 result;

		for (int i = 0; i < 4 * 4; i++)
			result.elements[i] = elements[i];


		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				float sum = 0.0f;

				for (int i = 0; i < 4; i++)
				{
					sum += elements[x + i * 4] * other.elements[i + y * 4];
				}

				result.elements[x + y * 4] = sum;
			}
		}


		for (int i = 0; i < 4 * 4; i++)
			elements[i] = result.elements[i];


		return *this;
	}

	float matrix4::determinant() const
	{
		float a = elements[0 + 0 * 4];
		float b = elements[0 + 1 * 4];
		float c = elements[0 + 2 * 4];
		float d = elements[0 + 3 * 4];

		float e = elements[1 + 0 * 4];
		float f = elements[1 + 1 * 4];
		float g = elements[1 + 2 * 4];
		float h = elements[1 + 3 * 4];

		float i = elements[2 + 0 * 4];
		float j = elements[2 + 1 * 4];
		float k = elements[2 + 2 * 4];
		float l = elements[2 + 3 * 4];

		float m = elements[3 + 0 * 4];
		float n = elements[3 + 1 * 4];
		float o = elements[3 + 2 * 4];
		float p = elements[3 + 3 * 4];


		return m * j * g * d   -   i * n * g * d   -
			   m * f * k * d   +   e * n * k * d   +
			   i * f * o * d   -   e * j * o * d   -
			   m * j * c * h   +   i * n * c * h   +
			   m * b * k * h   -   a * n * k * h   -
			   i * b * o * h   +   a * j * o * h   +
			   m * f * c * l   -   e * n * c * l   -
			   m * b * g * l   +   a * n * g * l   +
			   e * b * o * l   -   a * f * o * l   -
			   i * f * c * p   +   e * j * c * p   +
			   i * b * g * p   -   a * j * g * p   -
			   e * b * k * p   +   a * f * k * p;
	}

	// Matrices Functions
	matrix4 matrix4::identity()
	{
		return matrix4(1.0f);
	}


	matrix4 matrix4::invert(const matrix4& mat)
	{
		// Init
		matrix4 result;
		float det = mat.determinant();


		if (det == 0.0f)
			return matrix4();


		float a11 = mat.elements[0 + 0 * 4];
		float a12 = mat.elements[0 + 1 * 4];
		float a13 = mat.elements[0 + 2 * 4];
		float a14 = mat.elements[0 + 3 * 4];

		float a21 = mat.elements[1 + 0 * 4];
		float a22 = mat.elements[1 + 1 * 4];
		float a23 = mat.elements[1 + 2 * 4];
		float a24 = mat.elements[1 + 3 * 4];

		float a31 = mat.elements[2 + 0 * 4];
		float a32 = mat.elements[2 + 1 * 4];
		float a33 = mat.elements[2 + 2 * 4];
		float a34 = mat.elements[2 + 3 * 4];

		float a41 = mat.elements[3 + 0 * 4];
		float a42 = mat.elements[3 + 1 * 4];
		float a43 = mat.elements[3 + 2 * 4];
		float a44 = mat.elements[3 + 3 * 4];

		// Calculating
		float b11 = a22 * a33 * a44 + a23 * a34 * a42 + a24 * a32 * a43 - a22 * a34 * a43 - a23 * a32 * a44 - a24 * a33 * a42;
		float b12 = a12 * a34 * a43 + a13 * a32 * a44 + a14 * a33 * a42 - a12 * a33 * a44 - a13 * a34 * a42 - a14 * a32 * a43;
		float b13 = a12 * a23 * a44 + a13 * a24 * a42 + a14 * a22 * a43 - a12 * a24 * a43 - a13 * a22 * a44 - a14 * a23 * a42;
		float b14 = a12 * a24 * a33 + a13 * a22 * a34 + a14 * a23 * a32 - a12 * a23 * a34 - a13 * a24 * a32 - a14 * a22 * a33;

		float b21 = a21 * a34 * a43 + a23 * a31 * a44 + a24 * a33 * a41 - a21 * a33 * a44 - a23 * a34 * a41 - a24 * a31 * a43;
		float b22 = a11 * a33 * a44 + a13 * a34 * a41 + a14 * a31 * a43 - a11 * a34 * a43 - a13 * a31 * a44 - a14 * a33 * a41;
		float b23 = a11 * a24 * a43 + a13 * a21 * a44 + a14 * a23 * a41 - a11 * a23 * a44 - a13 * a24 * a41 - a14 * a21 * a43;
		float b24 = a11 * a23 * a34 + a13 * a24 * a31 + a14 * a21 * a33 - a11 * a24 * a33 - a13 * a21 * a34 - a14 * a23 * a31;

		float b31 = a21 * a32 * a44 + a22 * a34 * a41 + a24 * a31 * a42 - a21 * a34 * a42 - a22 * a31 * a44 - a24 * a32 * a41;
		float b32 = a11 * a34 * a42 + a12 * a31 * a44 + a14 * a32 * a41 - a11 * a32 * a44 - a12 * a34 * a41 - a14 * a31 * a42;
		float b33 = a11 * a22 * a44 + a12 * a24 * a41 + a14 * a21 * a42 - a11 * a24 * a42 - a12 * a21 * a44 - a14 * a22 * a41;
		float b34 = a11 * a24 * a32 + a12 * a21 + a34 + a14 * a22 * a31 - a11 * a22 * a34 - a12 * a24 * a31 - a14 * a21 * a32;

		float b41 = a21 * a33 * a42 + a22 * a31 * a43 + a23 * a32 * a41 - a21 * a32 * a43 - a22 * a33 * a41 - a23 * a31 * a42;
		float b42 = a11 * a32 * a43 + a12 * a33 * a41 + a13 * a31 * a42 - a11 * a33 * a42 - a12 * a31 * a43 - a13 * a32 * a41;
		float b43 = a11 * a23 * a42 + a12 * a21 * a43 + a13 * a22 * a41 - a11 * a22 * a43 - a12 * a23 * a41 - a13 * a21 * a42;
		float b44 = a11 * a22 * a33 + a12 * a23 * a31 + a13 * a21 * a32 - a11 * a23 * a32 - a12 * a21 * a33 - a13 * a22 * a31;

		// Writing
		result.elements[0 + 0 * 4] = b11 / det;
		result.elements[0 + 1 * 4] = b12 / det;
		result.elements[0 + 2 * 4] = b13 / det;
		result.elements[0 + 3 * 4] = b14 / det;

		result.elements[1 + 0 * 4] = b21 / det;
		result.elements[1 + 1 * 4] = b22 / det;
		result.elements[1 + 2 * 4] = b23 / det;
		result.elements[1 + 3 * 4] = b24 / det;

		result.elements[2 + 0 * 4] = b31 / det;
		result.elements[2 + 1 * 4] = b32 / det;
		result.elements[2 + 2 * 4] = b33 / det;
		result.elements[2 + 3 * 4] = b34 / det;

		result.elements[3 + 0 * 4] = b41 / det;
		result.elements[3 + 1 * 4] = b42 / det;
		result.elements[3 + 2 * 4] = b43 / det;
		result.elements[3 + 3 * 4] = b44 / det;


		return true;
	}


	matrix4 matrix4::translation(const vector3& position)
	{
		matrix4 result(1.0f);

		result.elements[0 + 3 * 4] = position.x;
		result.elements[1 + 3 * 4] = position.y;
		result.elements[2 + 3 * 4] = position.z;


		return result;
	}

	matrix4 matrix4::rotation(const float radians, const vector3& axis)
	{
		matrix4 result(1.0f);

		float s = sine(radians);
		float c = cosine(radians);
		float oc = 1.0f - c;

		result.elements[0 + 0 * 4] = axis.x * oc + c;
		result.elements[1 + 0 * 4] = axis.y * axis.x * oc + axis.z * s;
		result.elements[2 + 0 * 4] = axis.x * axis.z * oc - axis.y * s;

		result.elements[0 + 1 * 4] = axis.x * axis.y * oc - axis.z * s;
		result.elements[1 + 1 * 4] = axis.y * oc + c;
		result.elements[2 + 1 * 4] = axis.y * axis.z * oc + axis.x * s;

		result.elements[0 + 2 * 4] = axis.x * axis.z * oc + axis.y * s;
		result.elements[1 + 2 * 4] = axis.y * axis.z * oc - axis.x * s;
		result.elements[2 + 2 * 4] = axis.z * oc + c;


		return result;
	}

	matrix4 matrix4::scale(const float scale)
	{
		matrix4 result(1.0f);

		result.elements[0 + 0 * 4] = scale;
		result.elements[1 + 1 * 4] = scale;
		result.elements[2 + 2 * 4] = scale;


		return result;
	}

	matrix4 matrix4::scale(const vector3& scale)
	{
		matrix4 result(1.0f);

		result.elements[0 + 0 * 4] = scale.x;
		result.elements[1 + 1 * 4] = scale.y;
		result.elements[2 + 2 * 4] = scale.z;


		return result;
	}


	matrix4 matrix4::model(const vector3& position, const float rotX, const float rotY, const float rotZ, const float scale)
	{
		matrix4 result = matrix4::translation(position) *
			matrix4::rotation(rotX, vector3(1.0f, 0.0f, 0.0f)) *
			matrix4::rotation(rotY, vector3(0.0f, 1.0f, 0.0f)) *
			matrix4::rotation(rotZ, vector3(0.0f, 0.0f, 1.0f)) *
			matrix4::scale(vector3(scale, scale, scale));


		return result;
	}

	matrix4 matrix4::model(const vector3& position, const float rotX, const float rotY, const float rotZ, const vector3& scale)
	{
		matrix4 result = matrix4::translation(position) *
			matrix4::rotation(rotX, vector3(1.0f, 0.0f, 0.0f)) *
			matrix4::rotation(rotY, vector3(0.0f, 1.0f, 0.0f)) *
			matrix4::rotation(rotZ, vector3(0.0f, 0.0f, 1.0f)) *
			matrix4::scale(scale);


		return result;
	}

	matrix4 matrix4::model(const vector3& position, const float rot, const vector3& rotAxis, const float scale)
	{
		matrix4 result = matrix4::translation(position) *
			matrix4::rotation(rot, rotAxis) *
			matrix4::scale(vector3(scale, scale, scale));


		return result;
	}

	matrix4 matrix4::model(const vector3& position, const float rot, const vector3& rotAxis, const vector3& scale)
	{
		matrix4 result = matrix4::translation(position) *
			matrix4::rotation(rot, rotAxis) *
			matrix4::scale(scale);


		return result;
	}


	matrix4 matrix4::fpsView(const vector3& position, const float pitch, const float yaw)
	{
		matrix4 result(1.0f);

		float cp = cosine(pitch);
		float sp = sine(pitch);
		float cy = cosine(yaw);
		float sy = sine(yaw);

		vector3 xAxis(cy, 0.0f, -sy);
		vector3 yAxis(sy * sp, cp, cy * sp);
		vector3 zAxis(sy * cp, -sp, cp * cy);

		result.elements[0 + 0 * 4] = xAxis.x;
		result.elements[1 + 0 * 4] = yAxis.x;
		result.elements[2 + 0 * 4] = zAxis.x;

		result.elements[0 + 1 * 4] = xAxis.y;
		result.elements[1 + 1 * 4] = yAxis.y;
		result.elements[2 + 1 * 4] = zAxis.y;

		result.elements[0 + 2 * 4] = xAxis.z;
		result.elements[1 + 2 * 4] = yAxis.z;
		result.elements[2 + 2 * 4] = zAxis.z;

		result.elements[0 + 3 * 4] = -dotProduct(xAxis, position);
		result.elements[1 + 3 * 4] = -dotProduct(yAxis, position);
		result.elements[2 + 3 * 4] = -dotProduct(zAxis, position);


		return result;
	}

	matrix4 matrix4::lookAtView(const vector3& cameraPosition, const vector3& lookAtPosition, const vector3& upVector)
	{
		matrix4 result(1.0f);

		vector3 zAxis = normal(cameraPosition - lookAtPosition);
		vector3 xAxis = normal(crossProduct(upVector, zAxis));
		vector3 yAxis = crossProduct(zAxis, xAxis);

		result.elements[0 + 0 * 4] = xAxis.x;
		result.elements[1 + 0 * 4] = yAxis.x;
		result.elements[2 + 0 * 4] = zAxis.x;

		result.elements[0 + 1 * 4] = xAxis.y;
		result.elements[1 + 1 * 4] = yAxis.y;
		result.elements[2 + 1 * 4] = zAxis.y;

		result.elements[0 + 2 * 4] = xAxis.z;
		result.elements[1 + 2 * 4] = yAxis.z;
		result.elements[2 + 2 * 4] = zAxis.z;

		result.elements[0 + 3 * 4] = -dotProduct(xAxis, cameraPosition);
		result.elements[1 + 3 * 4] = -dotProduct(yAxis, cameraPosition);
		result.elements[2 + 3 * 4] = -dotProduct(zAxis, cameraPosition);


		return result;
	}


	matrix4 matrix4::orthographic(const float left, const float right, const float bottom, const float top, const float near, const float far)
	{
		matrix4 result(1.0f);

		result.elements[0 + 0 * 4] = 2.0f / (right - left);
		result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
		result.elements[2 + 2 * 4] = 2.0f / (near - far);

		result.elements[0 + 3 * 4] = (left + right) / (left - right);
		result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.elements[2 + 3 * 4] = (far + near) / (far - near);


		return result;
	}

	matrix4 matrix4::projection(const float aspectRatio, const float fov, const float zNear, const float zFar)
	{
		matrix4 result;

		float zm = zNear - zFar;
		float a = 1.0f / tangent(fov / 2.0f);

		result.elements[0 + 0 * 4] = a / aspectRatio;
		result.elements[1 + 1 * 4] = a;
		result.elements[2 + 2 * 4] = (zNear + zFar) / zm;
		result.elements[3 + 2 * 4] = -1.0f;
		result.elements[2 + 3 * 4] = (2.0f * zNear * zFar) / zm;


		return result;
	}

	/* Operator Overloads */
	matrix4 operator*(matrix4 left, const matrix4& right)
	{
		return left.multiply(right);
	}

	matrix4& matrix4::operator*=(const matrix4& other)
	{
		return multiply(other);
	}

}