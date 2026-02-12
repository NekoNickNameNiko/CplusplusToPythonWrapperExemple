#include "scene.h"


Bwt::Resources::Scene::~Scene()
{
    for (int i = 0; i < meshes.size(); i++)
        meshes[i]->~Model();
}

std::vector<Model*> Bwt::Resources::Scene::GetMeshes()
{
    return meshes;
}

void Bwt::Resources::Scene::Add(Model* model)
{
    meshes.push_back(model);
}

void Bwt::Resources::Scene::AddLight(PointLight light)
{
    lightManager.AddPointLight(light);
}

void Bwt::Resources::Scene::renderScene(Shader* shaderProgram, Bwt::LowRenderer::Camera* camera, float angle)
{

    PointLight p = lightManager.GetPointLights().at(0);
    p.SendDataToShader(shaderProgram);

    float* colorTab = lightManager.GetPointLights().at(0).colorLight.AsList();
    glUniform3fv(glGetUniformLocation(shaderProgram->id, "lightColor"), 1, colorTab);

    float* tabulation = lightManager.GetPointLights().at(0).position.AsList();
    glUniform3fv(glGetUniformLocation(shaderProgram->id, "lightPosition"), 1, tabulation);

    float* camvtab = camera->transform.position.AsList();
    glUniform3fv(glGetUniformLocation(shaderProgram->id, "viewPos"), 1, camvtab);

    for (int i = 0; i < meshes.size(); i++)
        meshes[i]->RenderMesh(shaderProgram, camera, angle);
}
