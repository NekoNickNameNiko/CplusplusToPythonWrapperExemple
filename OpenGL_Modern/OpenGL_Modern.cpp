// OpenGL_Modern.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <shader.h>
#include <application.h>
#include "../include/buffer.h"
#include "Code/include/Mesh.h"

#include "Code/include/ResourceManager.h"

#include <glad.h>
#include <scene.h>
#include <Light.h>


int main(void)
{
    Bwt::Core::Application app{ 1920, 1080, "Scene Modern OpenGL" };   
    Bwt::Resources::Shader s{"Assets/Shaders/Shader.vert", "Assets/Shaders/Shader.frag"};
    //s.SetType(Bwt::Resources::ShaderType::WIREFRAME);
    app.AddShaderProgram(&s);


    Bwt::Resources::ResourceManager resourcemanager;


    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);
    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
     -1,0,-1   ,1.f, 0.f, 0.f,
     1,0,-1   ,0.f, 1.f, 0.f, 
     1,0,1    ,0.f, 0.f, 1.f,      
     -1,0,1   ,1.f, 1.f, 0.f,
     0,2,0   ,0.f, 1.f, 1.f
    };
    unsigned int indices[] = {
       0,4,1,1,4,2,2,4,3,3,4,0,
       3,0,2,2,0,1
    };  

    Mesh smash{};
    if (!smash.LoadFromOBJ("Assets/Obj/cubeTriangulate.obj"))
    {
        std::cerr << "Assets/Obj/cubeTriangulate.obj" << " does not exist " << std::endl;
    };
    smash.CreateBufferForShader();

    // Texture
    std::string name = "TestTexture";
    std::filesystem::path pathTexture = "Assets/2017-12-10_Feui1le_939863029570723844_DQsQYsIVAAAE6a4.jpg";
    Bwt::Resources::TextureParams params;
    params.wrapMode = GL_CLAMP_TO_EDGE;

    // Create texture
    Bwt::Resources::Texture* texture = resourcemanager.CreateTexture<Bwt::Resources::Texture>(name, pathTexture, params);

    // Getting uniform
    smash.gSamplerLocation = glGetUniformLocation(s.id, "gSampler");
    if (smash.gSamplerLocation == -1)
    {
        printf("Error getting uniform location of 'gSampler'");
        exit(1);
    }

    // Bind
    texture->Bind(GL_TEXTURE0);
    glUniform1i(smash.gSamplerLocation, 0);
    smash.pTexture = texture;

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); 
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
    // End texture

    Model model{ {0.f, 0.f, 0.f} };
    model.transform.scale = { 1.f, 1.f, 1.f };
    model.SetMesh(&smash);

    PointLight light{};
    light.position = { 1.5f, 2.0f, 0.f };
    light.colorLight = { 1.f, 1.f, 1.f };
    light.ambient = { 0.2f,0.f,0.2f };
    light.diffuse = { 0.5f, 0.5f, 0.5f };
    light.specular = { 1.0f, 1.0f, 1.0f };

    Scene myScene{  };
    myScene.Add(&model);
    myScene.AddLight(light);

    app.Run(&myScene);
    return 0;
}