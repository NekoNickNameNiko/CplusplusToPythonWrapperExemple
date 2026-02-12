#include "../include/Light.h"

using namespace Bwt::LowRenderer;

void LightManager::AddDirectionalLight(const DirectionalLight& light) {
    directionalLights.push_back(light);
}

void LightManager::AddPointLight(const PointLight& light) {
    pointLights.push_back(light);
}

void LightManager::AddSpotLight(const SpotLight& light) {
    spotLights.push_back(light);
}

const std::vector<DirectionalLight>& LightManager::GetDirectionalLights() const {
    return directionalLights;
}

const std::vector<PointLight>& LightManager::GetPointLights() const {
    return pointLights;
}

const std::vector<SpotLight>& LightManager::GetSpotLights() const {
    return spotLights;
}

Bwt::Core::Maths::Vector3 LightManager::CalculDirectionalLight(DirectionalLight& light, Bwt::Core::Maths::Vector3& normal, Bwt::Core::Maths::Vector3& viewDir)
{
	Bwt::Core::Maths::Vector3 lightDir = -light.direction.Normalized();

	// diffuse shading
	float diff = std::fmax(normal.DotProductVector3(lightDir), 0.0f);

	// specular shading
	Bwt::Core::Maths::Vector3 reflectDir = Bwt::Core::Maths::Vector3::Reflect(-lightDir, normal);
	float spec = std::pow(std::fmax(viewDir.DotProductVector3(reflectDir), 0.0f), light.shininess);

	// combine results
	Bwt::Core::Maths::Vector3 ambient = light.ambient;
	Bwt::Core::Maths::Vector3 diffuse = light.diffuse * diff;
	Bwt::Core::Maths::Vector3 specular = light.specular * spec;
	return (ambient + diffuse + specular);
}

Bwt::Core::Maths::Vector3 LightManager::CalculPointLight(PointLight light, Bwt::Core::Maths::Vector3 normal, Bwt::Core::Maths::Vector3 fragPos, Bwt::Core::Maths::Vector3 viewDir)
{
	Bwt::Core::Maths::Vector3 lightDir = (light.position - fragPos).Normalized();

	// diffuse shading
	float diff = std::fmax(normal.DotProductVector3(lightDir), 0.0f);

	// specular shading
	Bwt::Core::Maths::Vector3 reflectDir = Bwt::Core::Maths::Vector3::Reflect(-lightDir, normal);
	float spec = std::pow(std::fmax(viewDir.DotProductVector3(reflectDir), 0.0f), light.shininess);

	// attenuation
	float distance = (light.position - fragPos).GetDistance(Bwt::Core::Maths::Vector3());
	float attenuation = 1.0 / (light.constantAttenuation + light.linearAttenuation * distance + light.quadraticAttenuation * (distance * distance));

	// combine results
	Bwt::Core::Maths::Vector3 ambient = light.ambient * attenuation;
	Bwt::Core::Maths::Vector3 diffuse = light.diffuse * diff * attenuation;
	Bwt::Core::Maths::Vector3 specular = light.specular * spec * attenuation;
	return (ambient + diffuse + specular);
}

Bwt::Core::Maths::Vector3 LightManager::CalculSpotLight(SpotLight light, Bwt::Core::Maths::Vector3 normal, Bwt::Core::Maths::Vector3 fragPos, Bwt::Core::Maths::Vector3 viewDir)
{
	Bwt::Core::Maths::Vector3 lightDir = (light.position - fragPos).Normalized();

	// diffuse shading
	float diff = std::fmax(normal.DotProductVector3(lightDir), 0.0f);

	// specular shading
	Bwt::Core::Maths::Vector3 reflectDir = Bwt::Core::Maths::Vector3::Reflect(-lightDir, normal);
	float spec = std::pow(std::fmax(viewDir.DotProductVector3(reflectDir), 0.0f), light.shininess);

	// attenuation
	float distance = (light.position - fragPos).GetDistance(Bwt::Core::Maths::Vector3());
	float attenuation = 1.0 / (light.constantAttenuation + light.linearAttenuation * distance + light.quadraticAttenuation * (distance * distance));

	// spotlight intensity
	float theta = lightDir.DotProductVector3((-light.direction).Normalized());
	float epsilon = light.innerCutoff - light.outerCutoff;
	float intensity = std::clamp((theta - light.outerCutoff) / epsilon, 0.0f, 1.0f);

	// combine results
	Bwt::Core::Maths::Vector3 ambient = light.ambient * attenuation;
	Bwt::Core::Maths::Vector3 diffuse = light.diffuse * diff * attenuation;
	Bwt::Core::Maths::Vector3 specular = light.specular * spec * attenuation;
	return (ambient + diffuse + specular);
}

void Bwt::LowRenderer::PointLight::SendDataToShader(Bwt::Resources::Shader* shader) const
{
	float* ambient, * diffuse, * specular, * position;
	ambient = PointLight::ambient.AsList();
	diffuse = PointLight::diffuse.AsList();
	specular = PointLight::specular.AsList();
	position = PointLight::position.AsList();

	shader->SetUniform4fv("pointLight.ambient", ambient);
	shader->SetUniform4fv("pointLight.diffuse", diffuse);
	shader->SetUniform4fv("pointLight.specular", specular);
	shader->SetUniform4fv("pointLight.position", position);
}

void Bwt::LowRenderer::Light::SendDataToShader(Bwt::Resources::Shader* shader) const
{
}
