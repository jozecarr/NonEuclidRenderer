#pragma once
#include <string>
#include <unordered_map>

#include "gtc/type_ptr.hpp"
#include "glm.hpp"

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {
private:
	std::string filePath;
	unsigned int rendererId;
	std::unordered_map<std::string, int> uniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v4);
	void SetUniformMat4(const std::string& name, glm::mat4 value);
private:
	ShaderProgramSource ParseShader(const std::string& filepath); 
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name);
}; 

Shader* GetBasicShader(glm::vec3 colour);
Shader* GetInvisibleShader();