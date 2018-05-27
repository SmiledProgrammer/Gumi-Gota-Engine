#ifndef GUMIGOTA_SHADER_H
#define GUMIGOTA_SHADER_H



/* INCLUDES */
// Normal Includes
#include <string>
#include <unordered_map>

// Header Includes
#include "../maths/vectors/vector2.h"
#include "../maths/vectors/vector3.h"
#include "../maths/vectors/vector4.h"
#include "../maths/matrices/matrix4.h"

#include "../graphics/Color.h"



namespace gg
{

	// Additional Classes
	struct ShaderProgramSource
	{
		std::string vertexSource;
		std::string fragmentSource;
	};



	class Shader
	{
	private:
		/* Variables */
		std::string m_filepath;
		unsigned int m_programID;
		std::unordered_map<std::string, int> m_uniformLocationCache;

	public:
		/* Constructors */
		Shader(const std::string& filepath);

		/* Destructor */
		~Shader();

		/* Functions */
		void start() const;
		static void stop();

		// Uniform Functions
		void setUniform1i(const std::string& name, const int value);

		void setUniform1f(const std::string& name, const float value);
		void setUniform2f(const std::string& name, const float v0, const float v1);
		void setUniform2f(const std::string& name, const vector2& values);
		void setUniform3f(const std::string& name, const float v0, const float v1, const float v2);
		void setUniform3f(const std::string& name, const vector3& values);
		void setUniform3f(const std::string& name, const Color& values);
		void setUniform4f(const std::string& name, const float v0, const float v1, const float v2, const float v3);
		void setUniform4f(const std::string& name, const vector4& values);
		void setUniform4f(const std::string& name, const Color& values);

		void setUniformMatrix4f(const std::string& name, const matrix4& mat);

	private:
		// Private Functions
		int m_getUniformLocation(const std::string& name);

		unsigned int m_compileShader(const unsigned int type, const std::string& source);
		unsigned int m_createShader(const std::string& vertexShader, const std::string& fragmentShader);
		ShaderProgramSource m_parseShader(const std::string& filepath);

	};

}



#endif