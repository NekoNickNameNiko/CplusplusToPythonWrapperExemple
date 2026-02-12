#include "shader.h"

#include <sstream>
#include <iostream>
#include <NoShaderFoundException.h>
#include <CompileShaderFailException.h>

#include <glad.h>

Bwt::Resources::Shader::Shader(const char* vertex, const char* fragment)
{
	std::string vertexCode;
	std::string fragmentCode;

	try {
		vertexCode = ExtractCode(vertex);
		fragmentCode = ExtractCode(fragment);
	}
	catch (Bwt::Core::Debug::Exception::NoShaderFoundException e)
	{
		std::cerr << e.message << std::endl;
	}

	const char* v = vertexCode.c_str();
	const char* f = fragmentCode.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &v, NULL);
	glShaderSource(fragmentShader, 1, &f, NULL);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	try {
		Success(vertexShader);
		Success(fragmentShader);
	}
	catch (Bwt::Core::Debug::Exception::CompileShaderFailException e)
	{
		std::cerr << e.message << std::endl;
	}

	id = glCreateProgram();

	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);

	shaders.push_back(vertexShader); 
	shaders.push_back(fragmentShader);

}

Bwt::Resources::Shader::~Shader()
{
	for (int i = 0; i < shaders.size(); i++)
		glDeleteShader(shaders[i]);

	shaders.clear();
}

std::string Bwt::Resources::Shader::ExtractCode(const char* filePath)
{
	std::fstream shaderFile;
	shaderFile.open(filePath);

	if (!shaderFile.is_open())
	{
		shaderFile.close();
		const char* msg = "No Shader was found";
		throw Bwt::Core::Debug::Exception::NoShaderFoundException{ msg };
	}

	std::stringstream shaderStream;
	shaderStream << shaderFile.rdbuf();
	shaderFile.close();

	std::string returnString = shaderStream.str();
	shaderStream.clear();

	return returnString;
}

void Bwt::Resources::Shader::Success(unsigned int shader)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::stringstream msg;
		msg << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
		throw Bwt::Core::Debug::Exception::CompileShaderFailException{ msg.str() };
	}

}

void Bwt::Resources::Shader::SetType(ShaderType type)
{
	this->type = type;

	switch (type)
	{
	case FILL:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case WIREFRAME:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	}
}

void Bwt::Resources::Shader::Use() const
{
	glUseProgram(id);
}

void Bwt::Resources::Shader::UniformMatrix4(std::string name, bool transpose, float* tab) const
{
	int location = glGetUniformLocation(id, name.c_str());
	glUniformMatrix4fv(location, 1, transpose, tab);
}

void Bwt::Resources::Shader::SetUniform1f(const std::string name, float value) const
{
	int location = glGetUniformLocation(id, name.c_str());
	if (location != -1)
		glUniform1f(location, value);
}

void Bwt::Resources::Shader::SetUniform3fv(const std::string name, float* data) const
{
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, data);
}

void Bwt::Resources::Shader::SetUniform4fv(const std::string name, float* data) const
{
	glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, data);
}
