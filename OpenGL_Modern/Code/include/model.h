#pragma once

#include "../../Toolbox3D/Include/Matrix4.h"

#include "Mesh.h"
#include <transform.h>
#include <shader.h>
#include <camera.h>

#include "../include/material.h"

using namespace Bwt::Resources;
using namespace Bwt::Physics;

namespace Bwt
{
	namespace LowRenderer
	{
		class Model
		{
		public:

			Mesh* mesh;
			Transform transform;
			Bwt::Resources::Material mat;

			Model(const Bwt::Core::Maths::Vector3& transform);
			~Model();

			void RenderMesh(Bwt::Resources::Shader* shaderProgram, Bwt::LowRenderer::Camera* camera, float angle);
			void SetMesh(Mesh* mesh);
		};
	}
}