#include "../Renderer/ShaderProgram.hpp"
#include "ResourceManager.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

ResourceManager::ResourceManager(const std::string& executablePath)
{
	size_t found = executablePath.find_last_of("/\\");
	m_path = executablePath.substr(0, found);
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexShaderSource = getFileContent(vertexPath);
	if (vertexShaderSource.empty()) {
		std::cerr << "No vertex shader source!" << std::endl;
		return nullptr;
	}

	std::string fragmentShaderSource = getFileContent(fragmentPath);
	if (fragmentShaderSource.empty()) {
		std::cerr << "No fragment shader source!" << std::endl;
		return nullptr;
	}

	auto newShader = m_shaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexShaderSource, fragmentShaderSource)).first->second;
	if (newShader->IsCompiled()) {
		return newShader;
	}

	std::cerr << "Can't load shader program:\n"
		<< "vertex: " << vertexPath
		<< "fragment: " << fragmentPath << std::endl;

	return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shaderName)
{
	ShaderProgramMap::const_iterator it = m_shaderPrograms.find(shaderName);
	if (it != m_shaderPrograms.end()) {
		return it->second;
	}

	std::cerr << "Can't find the shader program: " << shaderName << std::endl;
	return nullptr;
}

std::string ResourceManager::getFileContent(const std::string& path) const
{
	std::ifstream f;
	f.open(m_path + "/" + path.c_str(), std::ios::in | std::ios::binary);
	if (!f.is_open()) {
		std::cerr << "Failed to open file: " << path << std::endl;
		return std::string();
	}

	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}
