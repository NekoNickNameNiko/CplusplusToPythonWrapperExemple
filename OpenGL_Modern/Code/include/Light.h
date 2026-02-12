#pragma once

#include "CommonInclude.h"

#include <shader.h>

namespace Bwt
{
	namespace LowRenderer
	{
		struct alignas(16) Light {
			Bwt::Core::Maths::Vector4 ambient;
			Bwt::Core::Maths::Vector4 diffuse;
			Bwt::Core::Maths::Vector4 specular;
			Bwt::Core::Maths::Vector4 outFragColor = Bwt::Core::Maths::Vector4();
			Bwt::Core::Maths::Vector3 colorLight{ 1.f, 1.f, 1.f };
			float shininess;

			virtual void SendDataToShader(Bwt::Resources::Shader* shader) const;

		};

		struct alignas(16) DirectionalLight : public Light {
			Bwt::Core::Maths::Vector3 direction;
			Bwt::Core::Maths::Matrix4 normal;
		};

		struct alignas(16) PointLight : public Light {
			Bwt::Core::Maths::Vector3 position;
			float constantAttenuation = 1.0f;
			float linearAttenuation = 0.09f;
			float quadraticAttenuation = 0.032f;

			void SendDataToShader(Bwt::Resources::Shader* shader) const override;
		};

		struct alignas(16) SpotLight : public Light {
			Bwt::Core::Maths::Vector3 position;
			Bwt::Core::Maths::Vector3 direction;
			Bwt::Core::Maths::Matrix4 normal;
			float constantAttenuation = 1.0f;
			float linearAttenuation = 0.09f;
			float quadraticAttenuation = 0.032f;
			float innerCutoff;
			float outerCutoff;
		};

		class LightManager {
		public:
			void AddDirectionalLight(const DirectionalLight& light);
			void AddPointLight(const PointLight& light);
			void AddSpotLight(const SpotLight& light);

			const std::vector<DirectionalLight>& GetDirectionalLights() const;
			const std::vector<PointLight>& GetPointLights() const;
			const std::vector<SpotLight>& GetSpotLights() const;

			Bwt::Core::Maths::Vector3 CalculDirectionalLight(DirectionalLight& light, Bwt::Core::Maths::Vector3& normal, Bwt::Core::Maths::Vector3& viewDir);
			Bwt::Core::Maths::Vector3 CalculPointLight(PointLight light, Bwt::Core::Maths::Vector3 normal, Bwt::Core::Maths::Vector3 fragPos, Bwt::Core::Maths::Vector3 viewDir);
			Bwt::Core::Maths::Vector3 CalculSpotLight(SpotLight light, Bwt::Core::Maths::Vector3 normal, Bwt::Core::Maths::Vector3 fragPos, Bwt::Core::Maths::Vector3 viewDir);
		private:
			std::vector<DirectionalLight> directionalLights;
			std::vector<PointLight> pointLights;
			std::vector<SpotLight> spotLights;
		};
	}
}