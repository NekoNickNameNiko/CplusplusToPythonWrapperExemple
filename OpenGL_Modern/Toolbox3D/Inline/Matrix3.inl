#include "../Include/Matrix3.h"

using namespace Bwt::Core::Maths;
inline Matrix3::Matrix3(FillAll_t, float init)
{
	std::fill(std::begin(tab), std::end(tab), init);
};
inline Matrix3::Matrix3(const Matrix3& copy)
{
	std::copy(std::begin(copy.tab), std::end(copy.tab), std::begin(tab));
};
inline Matrix3 Matrix3::GetIdentity3()
{
	return Matrix3(1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f);
}
inline Vector3 Matrix3::GetDiagonal() const
{
	return Vector3(tab[0], tab[4], tab[8]);
}
inline float Matrix3::GetTrace() const
{
	return tab[0] + tab[4] + tab[8];
}
inline Matrix3 Matrix3::GetOpposed3() const
{
	return Matrix3(
		-tab[0], -tab[3], -tab[6],
		-tab[1], -tab[4], -tab[7],
		-tab[2], -tab[5], -tab[8]);
}
inline Matrix3 Matrix3::GetTransposed3() const
{
	return Matrix3(
		tab[0], tab[1], tab[2],
		tab[3], tab[4], tab[5],
		tab[6], tab[7], tab[8]);
}
inline Matrix3 Matrix3::AddMatrix3(const Matrix3& other) const
{
	return Matrix3(
		tab[0] + other.tab[0], 
		tab[3] + other.tab[3], 
		tab[6] + other.tab[6], 
		tab[1] + other.tab[1], 
		tab[4] + other.tab[4], 
		tab[7] + other.tab[7], 
		tab[2] + other.tab[2],
		tab[5] + other.tab[5],
		tab[8] + other.tab[8]);
}
inline Matrix3 Matrix3::ProductScalar(float n) const
{
	return Matrix3(
		tab[0] * n, tab[3] * n, tab[6] * n,
		tab[1] * n, tab[4] * n, tab[7] * n,
		tab[2] * n, tab[5] * n, tab[8] * n);
}
inline Matrix3 Matrix3::ProductMatrix3(const Matrix3& other) const
{
	return Matrix3(
		// Colonne 1
		tab[0] * other.tab[0] + tab[3] * other.tab[1] + tab[6] * other.tab[2],  // row 0
		tab[0] * other.tab[3] + tab[3] * other.tab[4] + tab[6] * other.tab[5],  // row 3
		tab[0] * other.tab[6] + tab[3] * other.tab[7] + tab[6] * other.tab[8],  // row 6

		// Colonne 2
		tab[1] * other.tab[0] + tab[4] * other.tab[1] + tab[7] * other.tab[2],  // row 1
		tab[1] * other.tab[3] + tab[4] * other.tab[4] + tab[7] * other.tab[5],  // row 4
		tab[1] * other.tab[6] + tab[4] * other.tab[7] + tab[7] * other.tab[8],  // row 7

		// Colonne 3
		tab[2] * other.tab[0] + tab[5] * other.tab[1] + tab[8] * other.tab[2],  // row 2
		tab[2] * other.tab[3] + tab[5] * other.tab[4] + tab[8] * other.tab[5],  // row 5
		tab[2] * other.tab[6] + tab[5] * other.tab[7] + tab[8] * other.tab[8]   // row 8
	);
}
inline float Matrix3::GetDeterminant() const
{
	return tab[0] * (tab[4] * tab[8] - tab[5] * tab[7])
		- tab[1] * (tab[3] * tab[8] - tab[5] * tab[6])
		+ tab[2] * (tab[3] * tab[7] - tab[4] * tab[6]);
}
inline Matrix3 Matrix3::RotateMatrix(float _x, float _y, float _z)
{
	Matrix3 rotX = CreateXRotationMatrix(_x);
	Matrix3 rotY = CreateYRotationMatrix(_y);
	Matrix3 rotZ = CreateZRotationMatrix(_z);
	return rotZ * rotY * rotX;
}
inline Matrix3 Matrix3::CreateXRotationMatrix(float angle)
{
	return Matrix3(1.f, 0.f, 0.f,
		0.f, cos(angle), -sin(angle),
		0.f, sin(angle), cos(angle));
}
inline Matrix3 Matrix3::CreateYRotationMatrix(float angle)
{
	return Matrix3(
		cos(angle), 0.f, sin(angle),
		0.f, 1.f, 0.f,
		-sin(angle), 0.f, cos(angle));
}
inline Matrix3 Matrix3::CreateZRotationMatrix(float angle)
{
	return Matrix3(cos(angle), -sin(angle), 0.f,
		sin(angle), cos(angle), 0.f,
		0, 0, 1.f);
}
inline void Matrix3::Print() const
{
	std::cout
		<< tab[0] << " " << tab[1] << " " << tab[2] << "\n"
		<< tab[3] << " " << tab[4] << " " << tab[5] << "\n"
		<< tab[6] << " " << tab[7] << " " << tab[8] << "\n";
}
inline Matrix3 Matrix3::operator*(const Matrix3& other) const
{
	return ProductMatrix3(other);
}
inline Matrix3 Matrix3::operator/(const Matrix3& other) const
{
	return ProductMatrix3(other.Inverse());
}
inline Matrix3 Matrix3::operator+(const Matrix3& other) const
{
	return AddMatrix3(other);
}
inline Matrix3 Matrix3::operator-(const Matrix3& other) const
{
	return AddMatrix3(other.GetOpposed3());
}
inline Matrix3& Matrix3::operator*=(const Matrix3& other)
{
	float m1 = tab[0] * other.tab[0] + tab[3] * other.tab[1] + tab[6] * other.tab[2]; // row 0
	float m2 = tab[1] * other.tab[0] + tab[4] * other.tab[1] + tab[7] * other.tab[2]; // row 1
	float m3 = tab[2] * other.tab[0] + tab[5] * other.tab[1] + tab[8] * other.tab[2]; // row 2

	float m4 = tab[0] * other.tab[3] + tab[3] * other.tab[4] + tab[6] * other.tab[5]; // row 3
	float m5 = tab[1] * other.tab[3] + tab[4] * other.tab[4] + tab[7] * other.tab[5]; // row 4
	float m6 = tab[2] * other.tab[3] + tab[5] * other.tab[4] + tab[8] * other.tab[5]; // row 5

	float m7 = tab[0] * other.tab[6] + tab[3] * other.tab[7] + tab[6] * other.tab[8]; // row 6
	float m8 = tab[1] * other.tab[6] + tab[4] * other.tab[7] + tab[7] * other.tab[8]; // row 7
	float m9 = tab[2] * other.tab[6] + tab[5] * other.tab[7] + tab[8] * other.tab[8]; // row 8
						
	tab[0] = m1;
	tab[1] = m2;
	tab[2] = m3;
	tab[3] = m4;
	tab[4] = m5;
	tab[5] = m6;
	tab[6] = m7;
	tab[7] = m8;
	tab[8] = m9;

	return *this;
}
inline Matrix3& Matrix3::operator/=(const Matrix3& other)
{
	*this *= other.Inverse();
	return *this;
}
inline Matrix3& Matrix3::operator+=(const Matrix3& other)
{
	tab[0] += other.tab[0];
	tab[1] += other.tab[1];
	tab[2] += other.tab[2];
	tab[3] += other.tab[3];
	tab[4] += other.tab[4];
	tab[5] += other.tab[5];
	tab[6] += other.tab[6];
	tab[7] += other.tab[7];
	tab[8] += other.tab[8];

	return *this;
}
inline Matrix3& Matrix3::operator-=(const Matrix3& other)
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

	return *this;
}
inline Matrix3 Matrix3::operator*(float n)
{
	return ProductScalar(n);
}
inline Matrix3 Matrix3::operator*=(float n)
{
	tab[0] = tab[0] * n;
	tab[1] = tab[1] * n;
	tab[2] = tab[2] * n;
	tab[3] = tab[3] * n;
	tab[4] = tab[4] * n;
	tab[5] = tab[5] * n;
	tab[6] = tab[6] * n;
	tab[7] = tab[7] * n;
	tab[8] = tab[8] * n;

	return *this;
}
inline Vector3 Matrix3::operator[](int index) const
{
	assert(index >= 0 && index < 3 && "Index out of range");
	return Vector3(tab[index * 3], tab[index * 3 + 1], tab[index * 3 + 2]);
}
inline Vector3& Matrix3::operator[](int index)
{
	assert(index >= 0 && index < 3 && "Index out of range");
	return *reinterpret_cast<Vector3*>(&tab[index * 3]);
}