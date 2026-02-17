#include "model.h"
#include <shader.h>
#include <glad.h>
#include <camera.h>



Bwt::LowRenderer::Model::Model(const Bwt::Core::Maths::Vector3& position)
	: transform(position), mesh(nullptr), mat({ 1.f, 1.f, 0.f })
{
}

Bwt::LowRenderer::Model::~Model()
{
	mesh->~Mesh();
}

void Bwt::LowRenderer::Model::RenderMesh(Bwt::Resources::Shader* shaderProgram, Bwt::LowRenderer::Camera* camera, float angle)
{
	if (camera == nullptr)
		return;

	Matrix4 model = transform.GetTransformMatrix();
	float dis = 10.f;

	Matrix4 vp = camera->GetVPMatrix(false);
	Matrix4 mvp = vp * model;

	float* colTab = mat.GetColor().AsList().data();
	glUniform3fv(glGetUniformLocation(shaderProgram->id, "objectColor"), 1, colTab);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->id, "mvp"), 1, true, mvp.tab);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->id, "model"), 1, true, model.tab);

	shaderProgram->Use();

	mesh->Draw();
}

void Bwt::LowRenderer::Model::SetMesh(Mesh* mesh)
{
	Model::mesh = mesh;
}
