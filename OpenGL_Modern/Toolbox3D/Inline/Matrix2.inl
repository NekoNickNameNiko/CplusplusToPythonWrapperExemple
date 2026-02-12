#include "../Include/Matrix2.h"

using namespace Bwt::Core::Maths;
inline Matrix2::Matrix2(FillAll_t, float init)
{
	std::fill(std::begin(tab), std::end(tab), init);
};
inline Matrix2::Matrix2(const Matrix2& copy)
{
	std::copy(std::begin(copy.tab), std::end(copy.tab), std::begin(tab));
};
inline Matrix2 Matrix2::GetIdentity2()
{
	return Matrix2(1, 0, 0, 1);
}
inline Vector2 Matrix2::GetDiagonal() const
{
	return Vector2(tab[0], tab[3]);
}
inline float Matrix2::GetTrace() const
{
	return tab[0] + tab[3];
}
inline Matrix2 Matrix2::GetOpposed2() const
{
	return	Matrix2(-tab[0], -tab[2], -tab[1], -tab[3]);
}
inline Matrix2 Matrix2::GetTransposed2() const
{
	return Matrix2(tab[0], tab[1],
		tab[2], tab[3]);
}
inline Matrix2 Matrix2::AddMatrix2(const Matrix2& other) const
{
	return Matrix2(
		tab[0] + other.tab[0], tab[2] + other.tab[2],
		tab[1] + other.tab[1], tab[3] + other.tab[3]
	);
}
inline Matrix2 Matrix2::ProductScalar(float n) const
{
	return Matrix2(tab[0] * n, tab[2] * n,
		tab[1] * n, tab[3] * n);
}
inline Matrix2 Matrix2::ProductMatrix2(const Matrix2& other) const
{
	return Matrix2(
		tab[0] * other.tab[0] + tab[2] * other.tab[1],
		tab[0] * other.tab[2] + tab[2] * other.tab[3],
		tab[1] * other.tab[0] + tab[3] * other.tab[1],
		tab[1] * other.tab[2] + tab[3] * other.tab[3] 
	);
}
inline float Matrix2::GetDeterminant() const
{
	return tab[0] * tab[3] - tab[1] * tab[2];
}
inline Matrix2 Matrix2::Inverse() const
{
	float det = GetDeterminant();

	if (std::abs(det) < 1e-6f)
	{
		throw std::runtime_error("Matrix is not invertible (det == 0)");
	}

	return Matrix2(
		tab[3] / det, -tab[2] / det,
		-tab[1] / det, tab[0] / det
	);
}
inline Matrix2 Matrix2::Rotation(float angle)
{
	return Matrix2(cos(angle), -sin(angle), sin(angle), cos(angle));
}
inline void Matrix2::Print() const
{
	std::cout
		<< tab[0] << " " << tab[1] << "\n"
		<< tab[2] << " " << tab[3] << "\n";
}
inline Matrix2 Matrix2::operator*(const Matrix2& other)const
{
	return ProductMatrix2(other);
}
inline Matrix2 Matrix2::operator/(const Matrix2& other)const
{
	return ProductMatrix2(other.Inverse());
}
inline Matrix2 Matrix2::operator+(const Matrix2& other) const
{
	return AddMatrix2(other);
}
inline Matrix2 Matrix2::operator-(const Matrix2& other) const
{
	return AddMatrix2(other.GetOpposed2());
}
inline Matrix2& Matrix2::operator*=(const Matrix2& other)
{
	float m0 = tab[0] * other.tab[0] + tab[2] * other.tab[1];
	float m1 = tab[1] * other.tab[0] + tab[3] * other.tab[1];
	float m2 = tab[0] * other.tab[2] + tab[2] * other.tab[3];
	float m3 = tab[1] * other.tab[2] + tab[3] * other.tab[3];

	tab[0] = m0;
	tab[1] = m1;
	tab[2] = m2;
	tab[3] = m3;

	return *this;
}
inline Matrix2& Matrix2::operator/=(const Matrix2& other)
{
	*this *= other.Inverse();
	return *this;
}
inline Matrix2& Matrix2::operator+=(const Matrix2& other)
{
	tab[0] += other.tab[0];
	tab[1] += other.tab[1];
	tab[2] += other.tab[2];
	tab[3] += other.tab[3];

	return *this;
}
inline Matrix2& Matrix2::operator-=(const Matrix2& other)
{
	tab[0] -= other.tab[0];
	tab[1] -= other.tab[1];
	tab[2] -= other.tab[2];
	tab[3] -= other.tab[3];

	return *this;
}
inline Matrix2 Matrix2::operator*(float n) const
{
	return ProductScalar(n);
}
inline Matrix2& Matrix2::operator*=(float n)
{
	tab[0] = tab[0] * n;
	tab[1] = tab[1] * n;
	tab[2] = tab[2] * n;
	tab[3] = tab[3] * n;
	return *this;
}