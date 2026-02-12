#pragma once

#include <vector>
#include "../../Toolbox3D/Include/Matrix4.h"   
#include <model.h>    
#include "shader.h"
#include "Camera.h"

using namespace Bwt::Core::Maths;

namespace Bwt
{
    namespace Resources
    {
        class SceneNode {
        public:
            SceneNode* parent = nullptr;
            std::vector<SceneNode*> children;

            Bwt::Core::Maths::Matrix4 localTransform = Bwt::Core::Maths::Matrix4::GetIdentity4();
            Bwt::Core::Maths::Matrix4 globalTransform = Bwt::Core::Maths::Matrix4::GetIdentity4();
            bool isGlobalTransformDirty = true;

            Bwt::LowRenderer::Model* model = nullptr;

            void AddChild(SceneNode* child);
            void SetLocalTransform(const Bwt::Core::Maths::Matrix4& t);
            void MarkDirty();
            void UpdateTransform();
            void Draw(Shader* shaderProgram, Bwt::LowRenderer::Camera* camera, float angle);
        };
    }
}