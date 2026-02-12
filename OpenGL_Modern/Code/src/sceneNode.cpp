#include "SceneNode.h"

void Bwt::Resources::SceneNode::AddChild(SceneNode* child)
{
    children.push_back(child);
    child->parent = this;
    child->MarkDirty();
}

void Bwt::Resources::SceneNode::SetLocalTransform(const Bwt::Core::Maths::Matrix4& t)
{
    localTransform = t;
    MarkDirty();
}

void Bwt::Resources::SceneNode::MarkDirty()
{
    isGlobalTransformDirty = true;
    for (SceneNode* child : children)
    {
        child->MarkDirty();
    }
}

void Bwt::Resources::SceneNode::UpdateTransform()
{
    if (isGlobalTransformDirty) {
        if (parent) {
            globalTransform = parent->globalTransform * localTransform;
        }
        else {
            globalTransform = localTransform;
        }
        isGlobalTransformDirty = false;
    }

    for (auto* child : children) {
        child->UpdateTransform();
    }
}

void Bwt::Resources::SceneNode::Draw(Shader* shaderProgram, Bwt::LowRenderer::Camera* camera, float angle)
{
    if (model) {
        model->transform.modelMatrix = globalTransform;
        model->RenderMesh(shaderProgram, camera, angle);
    }

    for (auto* child : children) {
        child->Draw(shaderProgram, camera, angle);
    }
}