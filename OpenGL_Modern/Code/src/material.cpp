#include "../include/material.h"

#include "glad.h"

Bwt::Resources::Material::Material() : color(1.f, 0.5f, 0.31f)
{
}

Bwt::Resources::Material::Material(Bwt::Core::Maths::Vector3 vec)
	: color(1.f, 0.5f, 0.31f)
{
}

Bwt::Core::Maths::Vector3 Bwt::Resources::Material::GetColor() const
{
	return color;
}

void Bwt::Resources::Material::SendDataToShaderPrgram(Shader shader)
{
	float *ambient, *diffuse, *specular;
	ambient = Material::ambient.AsList().data();
	diffuse = Material::diffuse.AsList().data();
	specular = Material::specular.AsList().data();

	shader.SetUniform3fv("material.ambient", ambient);
	shader.SetUniform3fv("material.diffuse", diffuse);
	shader.SetUniform3fv("material.specular", specular);
	shader.SetUniform1f("material.shininess", Material::shininess);
}
