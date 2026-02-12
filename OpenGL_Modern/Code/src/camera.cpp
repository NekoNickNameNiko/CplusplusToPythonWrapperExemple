#include "camera.h"
#include <NoProjectionMatrixException.h>

using namespace Bwt::LowRenderer;

void Camera::Update() 
{
	if (projection.tab == Matrix4::GetIdentity4().tab)
		throw Bwt::Core::Debug::Exceptions::NoProjectionMatrixException::NoProjectionMatrixException();

	SoftUpdate();
	vpMatrix = GetVPMatrix(true);
}

void Camera::SoftUpdate()
{
	viewMatrix = LookAt(transform.position, center, transform.up);
}

Bwt::LowRenderer::Camera::Camera()
	:transform({ 0.f, 0.f, 0.f }), projection(Matrix4::GetPerspectiveMatrix(
		1920.f, 1080.f, 0.0001f, 10000.f, 90.f
	))
{
	viewMatrix = LookAt(transform.position, center, transform.up);
	vpMatrix = projection * viewMatrix;
}

Camera::Camera(Vector3 position, Matrix4 projection)
	: transform(position), projection(projection)
{
	Update();
}

Camera::~Camera()
{
}

void Camera::SetProjectionMatrix(const Matrix4& proj)
{
	projection = proj;
}

Matrix4 Bwt::LowRenderer::Camera::GetVPMatrix(bool b)
{
	if (b)
	{
		return projection * LookAt({ transform.position.x, transform.position.y, transform.position.z },
			{ center.x, center.y, center.z }, transform.up);
	}
	else {
		return vpMatrix;
	}
}

void Camera::Move(Vector3 motion)
{
	transform.position += motion;
	center += motion;
	Update();
}

void Bwt::LowRenderer::Camera::Rotate(const Vector3& rotation)
{
	transform.Rotate(rotation);

	Vector3 oc = transform.position.GetOpposed();
	center += oc;
	center.Rotation(rotation.x, rotation.y, rotation.z);
	center += oc.GetOpposed();

	vpMatrix = projection * LookAt({ transform.position.x, transform.position.y, transform.position.z },
		{ center.x, center.y, center.z }, transform.up);
}

Matrix4 Camera::LookAt(const Vector3& eye, const Vector3& center, const Vector3& Up) {

	transform.forward.x = center.x - eye.x;
	transform.forward.y = center.y - eye.y;
	transform.forward.z = center.z - eye.z;

	transform.forward = transform.forward.Normalized();
	Vector3 side = transform.forward.CrossProductVector3(Up).Normalized();
	Vector3 up = side.CrossProductVector3(transform.forward);
	Matrix4 result = Matrix4::GetIdentity4();

	result.tab[0] = side.x;
	result.tab[1] = side.y;
	result.tab[2] = side.z;
	result.tab[3] = -side.DotProductVector3(eye);

	result.tab[4] = up.x;
	result.tab[5] = up.y;
	result.tab[6] = up.z;
	result.tab[7] = -up.DotProductVector3(eye);

	result.tab[8] = -transform.forward.x;
	result.tab[9] = -transform.forward.y;
	result.tab[10] = -transform.forward.z;
	result.tab[11] = transform.forward.DotProductVector3(eye);

	result.tab[12] = 0.0f;
	result.tab[13] = 0.0f;
	result.tab[14] = 0.0f;
	result.tab[15] = 1.0f;

	return result;
}