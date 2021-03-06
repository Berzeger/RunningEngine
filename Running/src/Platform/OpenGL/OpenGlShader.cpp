#include "pch.h"
#include "OpenGlShader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Running
{
	OpenGlShader::OpenGlShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			RUNNING_CORE_ERROR("{0}", infoLog.data());
			RUNNING_CORE_ASSERT(false, "Vertex shader compilation failure!");
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			RUNNING_CORE_ERROR("{0}", infoLog.data());
			RUNNING_CORE_ASSERT(false, "Fragment shader compilation failure!");
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		_rendererId = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(_rendererId, vertexShader);
		glAttachShader(_rendererId, fragmentShader);

		// Link our program
		glLinkProgram(_rendererId);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(_rendererId, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_rendererId, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(_rendererId, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(_rendererId);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			RUNNING_CORE_ERROR("{0}", infoLog.data());
			RUNNING_CORE_ASSERT(false, "Shader link failure!");
		}

		// Always detach shaders after a successful link.
		glDetachShader(_rendererId, vertexShader);
		glDetachShader(_rendererId, fragmentShader);
	}

	OpenGlShader::~OpenGlShader()
	{
		glDeleteProgram(_rendererId);
	}

	void OpenGlShader::Bind() const
	{
		glUseProgram(_rendererId);
	}

	void OpenGlShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGlShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(_rendererId, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGlShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(_rendererId, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGlShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(_rendererId, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void OpenGlShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(_rendererId, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGlShader::UploadUniformFloat2(const std::string& name, const glm::vec2 vec)
	{
		GLint location = glGetUniformLocation(_rendererId, name.c_str());
		glUniform2f(location, vec.x, vec.y);
	}

	void OpenGlShader::UploadUniformFloat3(const std::string& name, const glm::vec3 vec)
	{
		GLint location = glGetUniformLocation(_rendererId, name.c_str());
		glUniform3f(location, vec.x, vec.y, vec.z);
	}

	void OpenGlShader::UploadUniformFloat4(const std::string& name, const glm::vec4 vec)
	{
		GLint location = glGetUniformLocation(_rendererId, name.c_str());
		glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
	}
}
