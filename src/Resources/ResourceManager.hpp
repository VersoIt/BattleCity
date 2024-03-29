#pragma once
#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include <string>
#include <memory>
#include<map>

namespace Renderer
{
	class ShaderProgram;
}

class ResourceManager {
public:

	ResourceManager(const std::string& executablePath);
	~ResourceManager() = default;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shaderName);

private:

	std::string getFileContent(const std::string& path) const;

	typedef std::map<std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramMap;

	ShaderProgramMap m_shaderPrograms;

	std::string m_path;
};

#endif