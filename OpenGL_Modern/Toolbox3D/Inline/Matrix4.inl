#include "../Include/Matrix4.h"

using namespace Bwt::Core::Maths;
inline Matrix4::Matrix4(FillAll_t, float init)
{
	std::fill(std::begin(tab), std::end(tab), init);
}
inline Matrix4::Matrix4(const Matrix4& copy)
{
	std::copy(std::begin(copy.tab), std::end(copy.tab), std::begin(tab));
}
inline Matrix4::Matrix4(const float* values)
{
	std::copy(values, values + 16, tab);
}
inline Matrix4 Matrix4::GetIdentity4()
{
	return Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}
inline Vector4 Matrix4::GetDiagonal()
{
	return Vector4(tab[0], tab[5], tab[10], tab[15]);
}
inline float Matrix4::GetTrace()
{
	Vector4 vec = GetDiagonal();
	return vec.x + vec.y + vec.z + vec.w;
}
inline Matrix4 Matrix4::GetOpposed4() const
{
	return	Matrix4(
		-tab[0], -tab[4], -tab[8], -tab[12],
		-tab[1], -tab[5], -tab[9], -tab[13],
		-tab[2], -tab[6], -tab[10], -tab[14],
		-tab[3], -tab[7], -tab[11], -tab[15]);
}
inline Matrix4 Matrix4::GetTransposed4() const
{
	return	Matrix4(
		tab[0], tab[4], tab[8], tab[12],
		tab[1], tab[5], tab[9], tab[13],
		tab[2], tab[6], tab[10], tab[14],
		tab[3], tab[7], tab[11], tab[15]);
}
inline Matrix4 Matrix4::AddMatrix4(const Matrix4& other) const
{
	return	Matrix4(
		tab[0] + other.tab[0], tab[1] + other.tab[1], tab[2] + other.tab[2], tab[3] + other.tab[3],
		tab[4] + other.tab[4], tab[5] + other.tab[5], tab[6] + other.tab[6], tab[7] + other.tab[7],
		tab[8] + other.tab[8], tab[9] + other.tab[9], tab[10] + other.tab[10], tab[11] + other.tab[11],
		tab[12] + other.tab[12], tab[13] + other.tab[13], tab[14] + other.tab[14], tab[15] + other.tab[15]);
}
inline Matrix4 Matrix4::ProductScalar(float n)
{
	return	Matrix4(
		tab[0] * n, tab[4] * n, tab[8] * n, tab[12] * n,
		tab[1] * n, tab[5] * n, tab[9] * n, tab[13] * n,
		tab[2] * n, tab[6] * n, tab[10] * n, tab[14] * n,
		tab[3] * n, tab[7] * n, tab[11] * n, tab[15] * n);
}
inline Matrix4 Matrix4::ProductMatrix4(const Matrix4& other) const
{
	return Matrix4(
		// Ligne 1
		tab[0] * other.tab[0] + tab[1] * other.tab[4] + tab[2] * other.tab[8] + tab[3] * other.tab[12], // row 1
		tab[4] * other.tab[0] + tab[5] * other.tab[4] + tab[6] * other.tab[8] + tab[7] * other.tab[12],// row 5
		tab[8] * other.tab[0] + tab[9] * other.tab[4] + tab[10] * other.tab[8] + tab[11] * other.tab[12],// row 9
		tab[12] * other.tab[0] + tab[13] * other.tab[4] + tab[14] * other.tab[8] + tab[15] * other.tab[12],// row 13

		// Ligne 2
		tab[0] * other.tab[1] + tab[1] * other.tab[5] + tab[2] * other.tab[9] + tab[3] * other.tab[13],// row 2
		tab[4] * other.tab[1] + tab[5] * other.tab[5] + tab[6] * other.tab[9] + tab[7] * other.tab[13],// row 6
		tab[8] * other.tab[1] + tab[9] * other.tab[5] + tab[10] * other.tab[9] + tab[11] * other.tab[13],// row 10
		tab[12] * other.tab[1] + tab[13] * other.tab[5] + tab[14] * other.tab[9] + tab[15] * other.tab[13],// row 14

		// Ligne 3
		tab[0] * other.tab[2] + tab[1] * other.tab[6] + tab[2] * other.tab[10] + tab[3] * other.tab[14],// row 3
		tab[4] * other.tab[2] + tab[5] * other.tab[6] + tab[6] * other.tab[10] + tab[7] * other.tab[14],// row 7
		tab[8] * other.tab[2] + tab[9] * other.tab[6] + tab[10] * other.tab[10] + tab[11] * other.tab[14],// row 11
		tab[12] * other.tab[2] + tab[13] * other.tab[6] + tab[14] * other.tab[10] + tab[15] * other.tab[14],// row 15

		// Ligne 4
		tab[0] * other.tab[3] + tab[1] * other.tab[7] + tab[2] * other.tab[11] + tab[3] * other.tab[15],// row 4
		tab[4] * other.tab[3] + tab[5] * other.tab[7] + tab[6] * other.tab[11] + tab[7] * other.tab[15],// row 8
		tab[8] * other.tab[3] + tab[9] * other.tab[7] + tab[10] * other.tab[11] + tab[11] * other.tab[15],// row 12
		tab[12] * other.tab[3] + tab[13] * other.tab[7] + tab[14] * other.tab[11] + tab[15] * other.tab[15]// row 16
	);
}
inline Matrix4 Matrix4::CreateTranslationMatrix(const Vector3& translation)
{
	return Matrix4(
		1, 0, 0, translation.x,
		0, 1, 0, translation.y,
		0, 0, 1, translation.z,
		0, 0, 0, 1);
}
inline Matrix4 Matrix4::CreateScaleMatrix(const Vector3& scale)
{
	return Matrix4(
		scale.x, 0, 0, 0,
		0, scale.y, 0, 0,
		0, 0, scale.z, 0,
		0, 0, 0, 1);
}
inline Matrix4 Matrix4::CreateXRotationMatrix(float rad)
{
	return Matrix4(
		1, 0, 0, 0,
		0, cos(rad), -sin(rad), 0,
		0, sin(rad), cos(rad), 0,
		0, 0, 0, 1);
}
inline Matrix4 Matrix4::CreateYRotationMatrix(float rad)
{
	return Matrix4(
		cos(rad), 0, sin(rad), 0,
		0, 1, 0, 0,
		-sin(rad), 0, cos(rad), 0,
		0, 0, 0, 1);
}
inline Matrix4 Matrix4::CreateZRotationMatrix(float rad)
{
	return Matrix4(
		cos(rad), -sin(rad), 0, 0,
		sin(rad), cos(rad), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}

inline Matrix4 Matrix4::operator*(const Matrix4& other) const
{
	return ProductMatrix4(other);
}
inline Matrix4 Matrix4::operator/(const Matrix4& other)const
{
	return ProductMatrix4(other.Inverse());
}
inline Matrix4 Matrix4::operator+(const Matrix4& other) const
{
	return AddMatrix4(other);
}
inline Matrix4 Matrix4::operator-(const Matrix4& other) const
{
	return Matrix4();
}
inline Matrix4& Matrix4::operator*=(const Matrix4& other)
{
	tab[0] = tab[0] * other.tab[0] + tab[1] * other.tab[4] + tab[2] * other.tab[8] + tab[3] * other.tab[12]; // row 1
	tab[1] = tab[0] * other.tab[1] + tab[1] * other.tab[5] + tab[2] * other.tab[9] + tab[3] * other.tab[13];// row 2
	tab[2] = tab[0] * other.tab[2] + tab[1] * other.tab[6] + tab[2] * other.tab[10] + tab[3] * other.tab[14];// row 3
	tab[3] = tab[0] * other.tab[3] + tab[1] * other.tab[7] + tab[2] * other.tab[11] + tab[3] * other.tab[15];// row 4
	tab[4] = tab[4] * other.tab[0] + tab[5] * other.tab[4] + tab[6] * other.tab[8] + tab[7] * other.tab[12];// row 5
	tab[5] = tab[4] * other.tab[1] + tab[5] * other.tab[5] + tab[6] * other.tab[9] + tab[7] * other.tab[13];// row 6
	tab[6] = tab[4] * other.tab[2] + tab[5] * other.tab[6] + tab[6] * other.tab[10] + tab[7] * other.tab[14];// row 7
	tab[7] = tab[4] * other.tab[3] + tab[5] * other.tab[7] + tab[6] * other.tab[11] + tab[7] * other.tab[15];// row 8
	tab[8] = tab[8] * other.tab[0] + tab[9] * other.tab[4] + tab[10] * other.tab[8] + tab[11] * other.tab[12];// row 9
	tab[9] = tab[8] * other.tab[1] + tab[9] * other.tab[5] + tab[10] * other.tab[9] + tab[11] * other.tab[13];// row 10
	tab[10] = tab[8] * other.tab[2] + tab[9] * other.tab[6] + tab[10] * other.tab[10] + tab[11] * other.tab[14];// row 11
	tab[11] = tab[8] * other.tab[3] + tab[9] * other.tab[7] + tab[10] * other.tab[11] + tab[11] * other.tab[15];// row 12
	tab[12] = tab[12] * other.tab[0] + tab[13] * other.tab[4] + tab[14] * other.tab[8] + tab[15] * other.tab[12];// row 13
	tab[13] = tab[12] * other.tab[1] + tab[13] * other.tab[5] + tab[14] * other.tab[9] + tab[15] * other.tab[13];// row 14
	tab[14] = tab[12] * other.tab[2] + tab[13] * other.tab[6] + tab[14] * other.tab[10] + tab[15] * other.tab[14];// row 15
	tab[15] = tab[12] * other.tab[3] + tab[13] * other.tab[7] + tab[14] * other.tab[11] + tab[15] * other.tab[15]; // row 16

	return *this;
}
inline Matrix4& Matrix4::operator/=(const Matrix4& other)
{
	*this *= other.Inverse();
	return *this;
}
inline Matrix4& Matrix4::operator+=(const Matrix4& other)
{
	tab[0]  += other.tab[0] ;
	tab[1]  += other.tab[1] ;
	tab[2]  += other.tab[2] ;
	tab[3]  += other.tab[3] ;
	tab[4]  += other.tab[4] ;
	tab[5]  += other.tab[5] ;
	tab[6]  += other.tab[6] ;
	tab[7]  += other.tab[7] ;
	tab[8]  += other.tab[8] ;
	tab[9]  += other.tab[9] ;
	tab[10] += other.tab[10];
	tab[11] += other.tab[11];
	tab[12] += other.tab[12];
	tab[13] += other.tab[13];
	tab[14] += other.tab[14];
	tab[15] += other.tab[15];

	return *this;
}
inline Matrix4& Matrix4::operator-=(const Matrix4& other)
{
	tab[0] -= other.tab[0];
	tab[1] -= other.tab[1];
	tab[2] -= other.tab[2];
	tab[3] -= other.tab[3];
	tab[4] -= other.tab[4];
	tab[5] -= other.tab[5];
	tab[6] -= other.tab[6];
	tab[7] -= other.tab[7];
	tab[8] -= other.tab[8];
	tab[9] -= other.tab[9];
	tab[10] -= other.tab[10];
	tab[11] -= other.tab[11];
	tab[12] -= other.tab[12];
	tab[13] -= other.tab[13];
	tab[14] -= other.tab[14];
	tab[15] -= other.tab[15];

	return *this;
}

inline Matrix4 Matrix4::operator*(float n)
{
	return ProductScalar(n);
}
inline Matrix4 Matrix4::operator*=(float n)
{
	return Matrix4();
}
