#include "../Include/Matrix3.h"

using namespace Bwt::Core::Maths;
Matrix3 Matrix3::Inverse() const 
{
	const float det = GetDeterminant();
	if (std::abs(det) < 1e-6f) 
	{
		throw std::runtime_error("Matrix is not invertible (det == 0)");
	}

	Matrix3 inverse;
	const float invDet = 1.0f / det;

	for (int col = 0; col < 3; ++col) {
		for (int row = 0; row < 3; ++row) {
			
			const float cofactor = ((row + col) % 2 == 0 ? 1 : -1)
				* GetSubMatrix(row, col).GetDeterminant();
			inverse.tab[col * 3 + row] = cofactor * invDet;
		}
	}

	return inverse;
}
Matrix2 Matrix3::GetSubMatrix(int excludeRow, int excludeCol) const
{
	Matrix2 subMatrix;
	int index = 0;
	for (int i = 0; i < 3; ++i)
	{
		if (i == excludeCol) continue;

		for (int j = 0; j < 3; ++j)
		{
			if (j == excludeRow) continue;

			subMatrix.tab[index++] = tab[j * 3 + i];
		}
	}

	return subMatrix;
}
Matrix3 Matrix3::luDecomposition() const
{
	Matrix3 upper = *this;
	Matrix3 lower = GetIdentity3();

	//Make null first Line
	lower.tab[3] = upper.tab[3] / upper.tab[0];
	lower.tab[6] = upper.tab[6] / upper.tab[0];

	upper[1] -= upper[0] * lower.tab[3];
	upper[2] -= upper[0] * lower.tab[6];

	//Make null second line
	lower.tab[7] = upper.tab[7] / upper.tab[4];

	upper[2] -= upper[1] * lower.tab[7];

	return upper;
}
Matrix3 Matrix3::RotateMatrixVector(const Vector3& vec, float angle)
{
	float length = vec.GetNorm();
	float x = vec.x / length;
	float y = vec.y / length;
	float z = vec.z / length;

	float c = std::cos(ToRad(angle));
	float s = std::sin(ToRad(angle));
	float oneMinusC = 1 - c;

	// Rodrigues formula
	return Matrix3(
		c + x * x * oneMinusC, x * y * oneMinusC - z * s, x * z * oneMinusC + y * s,
		y * x * oneMinusC + z * s, c + y * y * oneMinusC, y * z * oneMinusC - x * s,
		z * x * oneMinusC - y * s, z * y * oneMinusC + x * s, c + z * z * oneMinusC);
}