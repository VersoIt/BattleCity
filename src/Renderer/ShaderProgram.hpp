#pragma once
#ifndef _SHADER_PROGRAM_
#define _SHADER_PROGRAM_

#include <glad/glad.h>
#include <string>
#include <iostream>

namespace Renderer {
	class ShaderProgram {
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);

		ShaderProgram() = delete;

		ShaderProgram(ShaderProgram&) = delete;
		
		ShaderProgram& operator=(const ShaderProgram&) = delete;

		ShaderProgram& operator=(ShaderProgram&&) noexcept;

		ShaderProgram(ShaderProgram&& other) noexcept;

		bool IsCompiled() const;

		void use() const;

		~ShaderProgram();

	private:

		void LogError(GLint id, const char* message);

		bool CreateShader(const std::string& shaderSource, const GLenum shaderType, GLuint& shaderId);

		bool m_isCompiled;

		GLuint m_id = 0;

	};
}

#endif // ShaderProgram