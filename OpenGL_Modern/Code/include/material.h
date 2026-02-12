#pragma once

#include "../../Toolbox3D/Include/Vector3.h"
#include <shader.h>

namespace Bwt
{
	namespace Resources
	{
		class Material
		{
		private:

			Bwt::Core::Maths::Vector3 ambient;
			Bwt::Core::Maths::Vector3 diffuse;
			Bwt::Core::Maths::Vector3 specular;
			float shininess;

			Bwt::Core::Maths::Vector3 color{1.f, 1.f, 0.f};

		public:

			Material();
			Material(Bwt::Core::Maths::Vector3 color);
			~Material() = default;

			Bwt::Core::Maths::Vector3 GetColor() const;
			void SendDataToShaderPrgram(Shader shader);
		};
	}
}