#pragma once

#include <vector>

#include "Mesh.h"
#include <model.h>
#include <shader.h>

#include <Light.h>

namespace Bwt
{
	namespace Resources
	{

		using namespace Bwt::LowRenderer;

		class Scene
		{
		private:
			std::vector<Model*> meshes;
			LightManager lightManager;

		public:

			~Scene();

			std::vector<Model*> GetMeshes();
			void Add(Model* model);
			void AddLight(PointLight light);

			void renderScene(Shader* shaderProgram, Bwt::LowRenderer::Camera* camera, float angle);

		};
	}
}