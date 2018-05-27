
/* INCLUDES */
// Self Include
#include "Shader.h"

// OpenGL Includes
#include <GL/glew.h>

// Normal Includes
#include <fstream>
#include <sstream>

// Header Includes
#include "ErrorHandling.h"

#include "../Log.h"



namespace gg
{

	/* Constructors */
	Shader::Shader(const std::string& filepath)
		: m_filepath(filepath)
	{
		ShaderProgramSource source = m_parseShader(filepath);
		m_programID = m_createShader(source.vertexSource, source.fragmentSource);
	}

	/* Destructor */
	Shader::~Shader()
	{
		GLcall(glDeleteProgram(m_programID));
	}

	/* Functions */
	void Shader::start() const
	{
		GLcall(glUseProgram(m_programID));
	}

	void Shader::stop()
	{
		GLcall(glUseProgram(0));
	}

	// Uniform Functions
	void Shader::setUniform1i(const std::string& name, const int value)
	{
		GLcall(glUniform1i(m_getUniformLocation(name), value));
	}


	void Shader::setUniform1f(const std::string& name, const float value)
	{
		GLcall(glUniform1f(m_getUniformLocation(name), value));
	}

	void Shader::setUniform2f(const std::string& name, const float v0, const float v1)
	{
		GLcall(glUniform2f(m_getUniformLocation(name), v0, v1));
	}

	void Shader::setUniform2f(const std::string& name, const vector2& values)
	{
		GLcall(glUniform2f(m_getUniformLocation(name), values.x, values.y));
	}

	void Shader::setUniform3f(const std::string& name, const float v0, const float v1, const float v2)
	{
		GLcall(glUniform3f(m_getUniformLocation(name), v0, v1, v2));
	}

	void Shader::setUniform3f(const std::string& name, const vector3& values)
	{
		GLcall(glUniform3f(m_getUniformLocation(name), values.x, values.y, values.z));
	}

	void Shader::setUniform3f(const std::string& name, const Color& values)
	{
		GLcall(glUniform3f(m_getUniformLocation(name), values.r, values.g, values.b));
	}

	void Shader::setUniform4f(const std::string& name, const float v0, const float v1, const float v2, const float v3)
	{
		GLcall(glUniform4f(m_getUniformLocation(name), v0, v1, v2, v3));
	}

	void Shader::setUniform4f(const std::string& name, const vector4& values)
	{
		GLcall(glUniform4f(m_getUniformLocation(name), values.x, values.y, values.z, values.w));
	}

	void Shader::setUniform4f(const std::string& name, const Color& values)
	{
		GLcall(glUniform4f(m_getUniformLocation(name), values.r, values.g, values.b, values.a));
	}


	void Shader::setUniformMatrix4f(const std::string& name, const matrix4& mat)
	{
		GLcall(glUniformMatrix4fv(m_getUniformLocation(name), 1, GL_FALSE, mat.elements));
	}

	// Private Functions
	int Shader::m_getUniformLocation(const std::string& name)
	{
		if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
			return m_uniformLocationCache[name];

		int location = glGetUniformLocation(m_programID, name.c_str());
		if (location == -1)
			LOG("[Warning] Uniform '" << name << "', in file '" << m_filepath << "' doesn't exist!");

		m_uniformLocationCache[name] = location;


		return location;
	}


	unsigned int Shader::m_compileShader(const unsigned int type, const std::string& source)
	{
		// Compiling Shader
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		GLcall(glShaderSource(id, 1, &src, nullptr));
		GLcall(glCompileShader(id));

		// Error Handling
		int result;
		GLcall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE)
		{
			int length;
			GLcall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
			char* message = (char*)alloca(length * sizeof(char));
			GLcall(glGetShaderInfoLog(id, length, &length, message));
			LOG("[Error] Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!");
			LOG(message);

			GLcall(glDeleteShader(id));
			return 0;
		}

		return id;
	}

	unsigned int Shader::m_createShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		// Compiling Shaders
		unsigned int program = glCreateProgram();
		unsigned int vs = m_compileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = m_compileShader(GL_FRAGMENT_SHADER, fragmentShader);

		// Creating Program
		GLcall(glAttachShader(program, vs));
		GLcall(glAttachShader(program, fs));
		GLcall(glLinkProgram(program));
		GLcall(glValidateProgram(program));

		// Error Handling
		int result = 0;
		GLcall(glGetProgramiv(program, GL_LINK_STATUS, &result));

		if (result == GL_FALSE)
		{
			LOG("[Error] Program failed to link.");

			GLcall(glDeleteProgram(program));

			return 0;
		}

		// Deleting Shaders
		GLcall(glDeleteShader(vs));
		GLcall(glDeleteShader(fs));

		return program;
	}

	ShaderProgramSource Shader::m_parseShader(const std::string& filepath)
	{
		std::ifstream stream(filepath);

		enum class ShaderType
		{
			NONE = -1,
			VERTEX = 0,
			FRAGMENT = 1
		};

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;
		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
			}
			else
			{
				ss[(int)type] << line << '\n';
			}
		}

		return { ss[0].str(), ss[1].str() };
	}

}