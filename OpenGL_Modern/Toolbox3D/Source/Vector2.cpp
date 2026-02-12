#include "../Include/Vector2.h"

using namespace Bwt::Core::Maths;
Vector2 Vector2::GetOpposed() const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::AddVector2(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::AddScalar(float scalar) const
{
	return Vector2(x + scalar, y + scalar);
}

Vector2 Vector2::ElementWiseProduct(const Vector2& other) const
{
	return Vector2(x * other.x, y * other.y);
}

Vector2 Vector2::ProductScalar(float scalar) const
{
	return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::GetMid(const Vector2& other) const
{
	return AddVector2(other).ProductScalar(1.f / 2.f);
}

float Vector2::GetDistance(const Vector2& other) const
{
	return sqrt(GetDistancePow(other));
}

float Vector2::GetDistancePow(const Vector2& other) const
{
	return (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y);
}

float Vector2::GetNorm() const
{
	return sqrt(x * x + y * y);
}

float Vector2::GetSquareNorm() const
{
	return x * x + y * y;
}

Vector2 Vector2::Normalized() const
{
	Vector2 vec;
	float magnitude = GetNorm();

	if (magnitude == 0)
	{
		return Vector2(0, 0);
	}

	vec.x = x / magnitude;
	vec.y = y / magnitude;
	return vec;
}

float Vector2::GetPerspective(float t) const
{
	if (t <= 0) return 0;

	return GetSquareNorm() / t;
}

float Vector2::DotProductVector2(const Vector2& other) const
{
	return x * other.x + y * other.y;
}

float Vector2::CrossProductVector2(const Vector2& other) const
{
	return x * other.y - y * other.x;
}

float Vector2::GetAngle(const Vector2& v2) const
{
	float denom = GetNorm() * v2.GetNorm();
	if (denom == 0.0f) return 0.0f;

	return acosf(DotProductVector2(v2) / denom) * (180.f / PI);
}

void Vector2::Rotation(float angle)
{
	float rad = ToRad(angle);
	float cosA = cosf(rad);
	float sinA = sinf(rad);

	float px = x * cosA - y * sinA;
	float py = x * sinA + y * cosA;

	x = px;
	y = py;
}

