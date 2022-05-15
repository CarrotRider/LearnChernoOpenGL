#ifndef SHADER_H
#define SHADER_H

#include <string>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader(const std::string& filePath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	void SetUniform(const std::string& name,
		float v0, float v1, float v2, float v3);
	void SetUniform(const std::string& name, int num);
private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexShader,
		const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type,
		const std::string& source);

	int GetUniformLocation(const std::string& name);
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
};



#endif // !SHADER_H

