#include "../Include/Vector4.h"

using namespace Bwt::Core::Maths;
inline Vector4 Vector4::GetOpposed() const
{
	return Vector4(-x, -y, -z, -w);
}

inline Vector4 Vector4::AddVector4(const Vector4& other) const
{
	return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

inline Vector4 Vector4::AddScalar(float scalar) const
{
	return Vector4(x + scalar, y + scalar, z + scalar, w + scalar);
}

inline Vector4 Vector4::ElementWiseProduct(const Vector4& other) const
{
	return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
}

inline Vector4 Vector4::ProductScalar(float scalar) const
{
	return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
}

inline Vector4 Vector4::GetMid(const Vector4& other) const
{
	return AddVector4(other).ProductScalar(1.f / 2.f);
}

inline float Vector4::GetDistance(const Vector4& other) const
{
	return sqrt(GetDistancePow(other));
}

inline float Vector4::GetDistancePow(const Vector4& other) const
{
	return (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y) + (other.z - z) * (other.z - z) + (other.w - w) * (other.w - w);
}

inline float Vector4::GetNorm() const
{
	return sqrt(x * x + y * y + z * z + w * w);
}

float Vector4::GetSquareNorm() const
{
	return x * x + y * y + z * z + w * w;
}

Vector4 Vector4::Normalized() const
{
	Vector4 vec;
	float magnitude = GetNorm();

	if (magnitude == 0)
	{
		return Vector4(0, 0, 0, 0);
	}

	vec.x = x / magnitude;
	vec.y = y / magnitude;
	vec.z = z / magnitude;
	vec.w = w / magnitude;
	return vec;
}

float Vector4::GetPerspective(float t) const
{
	if (t <= 0) return 0;

	return GetSquareNorm() / t;
}


inline float Vector4::DotProductVector4(const Vector4& other) const
{
	return x * other.x + y * other.y + z * other.z + w * other.w;
}

Vector4 Bwt::Core::Maths::Vector4::operator*(const Vector4& vec)
{
	return ElementWiseProduct(vec);
}

float* Bwt::Core::Maths::Vector4::AsList() const
{
	float result[4] = { x, y, z, w };
	return result;
}
