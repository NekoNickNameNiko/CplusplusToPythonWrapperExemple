#include "transform.h"

#include <iostream>

Matrix4 Bwt::Physics::Transform::GetTransformMatrix() const
{
    return Matrix4::CreateTransformMatrix(position, rotation, scale);
}

Bwt::Physics::Transform::Transform(Vector3 position)
    : position(position), rotation({0.f, 0.f, 0.f}), scale({1.f, 1.f, 1.f}), forward({0.f, 0.f, 1.f}), up({0.f, 1.f, 0.f}), right({1.f, 0.f, 0.f})
{
}

void Bwt::Physics::Transform::Rotate(const Vector3& rotationAxis)
{
    rotation = rotationAxis;

    forward.Rotation(rotationAxis.x, rotationAxis.y, rotationAxis.z);
    right.Rotation(rotationAxis.x, rotationAxis.y, rotationAxis.z);
    up.Rotation(rotationAxis.x, rotationAxis.y, rotationAxis.z);
}

void Bwt::Physics::Transform::Move(const Bwt::Core::Maths::Vector3& motion)
{
    position += motion;
}
