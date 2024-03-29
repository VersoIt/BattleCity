#include "ShaderProgram.hpp"

namespace Renderer {

	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) : m_isCompiled{ false }
	{
		GLuint vertexShaderId;
		if (!CreateShader(vertexShader, GL_VERTEX_SHADER, vertexShaderId)) {
			return;
		}

		GLuint fragmentShaderId;
		if (!CreateShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderId)) {
			glDeleteShader(vertexShaderId);
			return;
		}

		m_id = glCreateProgram();
		glAttachShader(m_id, vertexShaderId);
		glAttachShader(m_id, fragmentShaderId);
		glLinkProgram(m_id);

		GLint success;
		glGetProgramiv(m_id, GL_LINK_STATUS, &success);
		if (!success) {
			LogError(m_id, "Shader link error");
		}
		else {
			m_isCompiled = true;
		}

		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);
	}

	void ShaderProgram::LogError(GLint id, const char* message) 
	{
		GLchar logMessage[1024];
		glGetShaderInfoLog(m_id, 1024, nullptr, logMessage);
		std::cerr << "ERROR: " << message;
	}

	bool ShaderProgram::IsCompiled() const 
	{
		return m_isCompiled;
	}

	bool ShaderProgram::CreateShader(const std::string& shaderSource, const GLenum shaderType, GLuint& shaderId) 
	{
		shaderId = glCreateShader(shaderType);
		const char* sourceCode = shaderSource.c_str();
		glShaderSource(shaderId, 1, &sourceCode, nullptr);
		glCompileShader(shaderId);

		GLint success;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
		if (!success) {
			LogError(shaderId, "Shader compile time error");
		}
		return true;
	}

	ShaderProgram::~ShaderProgram() 
	{
		glDeleteProgram(m_id);
	}

	void ShaderProgram::use() const 
	{
		glUseProgram(m_id);
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept 
	{
		glDeleteProgram(m_id);
		m_id = other.m_id;
		m_isCompiled = other.m_isCompiled;

		other.m_isCompiled = false;
		other.m_id = 0;

		return *this;
	}

	ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
	{
		m_id = other.m_id;
		m_isCompiled = other.m_isCompiled;

		other.m_isCompiled = false;
		other.m_id = 0;
	}
}