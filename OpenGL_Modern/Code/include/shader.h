#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "Interface.h"


namespace Bwt
{
	namespace Resources
	{
		enum ShaderType
		{
			WIREFRAME,
			FILL,
		};

		class Shader : public IResource
		{

		public:

			unsigned int id;

			ShaderType type = FILL;
			std::vector<int> shaders;

			Shader(const char* vertex, const char* fragment);
			~Shader();

			void SetType(ShaderType type = FILL);
			void Use() const;


			void UniformMatrix4(std::string name,bool transpose, float* tab) const;
			void SetUniform1f(const std::string name, float value) const;
			void SetUniform3fv(const std::string name, float* data) const;
			void SetUniform4fv(const std::string name, float* data) const;

		private:

			std::string ExtractCode(const char* filePath);
			void Success(unsigned int shader);
		};
	}
}