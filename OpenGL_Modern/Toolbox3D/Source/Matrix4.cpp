#include "../Include/Matrix4.h"

using namespace Bwt::Core::Maths;
Matrix3 Matrix4::GetSubMatrix(int excludeRow, int excludeCol) const
{
	assert(excludeRow >= 0 && excludeRow < 4 && excludeCol >= 0 && excludeCol < 4);
	Matrix3 subMatrix;
	int index = 0;
	for (int col = 0; col < 4; ++col)
	{
		if (col == excludeCol) continue;
		for (int row = 0; row < 4; ++row)
		{
			if (row == excludeRow) continue;
			subMatrix.tab[index++] = tab[col * 4 + row];
		}
	}
	return subMatrix;
}
float Matrix4::GetDeterminant() const
{
	const float s0 = tab[10] * tab[15] - tab[11] * tab[14];
	const float s1 = tab[9] * tab[15] - tab[11] * tab[13];
	const float s2 = tab[9] * tab[14] - tab[10] * tab[13];
	const float s3 = tab[8] * tab[15] - tab[11] * tab[12];
	const float s4 = tab[8] * tab[14] - tab[10] * tab[12];
	const float s5 = tab[8] * tab[13] - tab[9] * tab[12];

	return tab[0] * (tab[5] * s0 - tab[6] * s1 + tab[7] * s2)
		- tab[4] * (tab[1] * s0 - tab[2] * s1 + tab[3] * s2)
		+ tab[8] * (tab[1] * s1 - tab[2] * s3 + tab[3] * s4)
		- tab[12] * (tab[1] * s2 - tab[2] * s4 + tab[3] * s5);
}
//float Matrix4::GetDeterminantSSE() const
//{
//	__m128 c0 = _mm_load_ps(&tab[0]);  //  0  1  2  3
//	__m128 c1 = _mm_load_ps(&tab[4]);  //  4 ( 5  6  7)
//	__m128 c2 = _mm_load_ps(&tab[8]);  //  8 ( 9 10 11)
//	__m128 c3 = _mm_load_ps(&tab[12]); // 12 (13 14 15)
//
//#define CALC_DET2(a, b) _mm_sub_ps( \
//    _mm_mul_ps( \
//        _mm_shuffle_ps(a, a, _MM_SHUFFLE(3,2,3,2)), \
//        _mm_shuffle_ps(b, b, _MM_SHUFFLE(2,3,2,3))), \
//    _mm_mul_ps( \
//        _mm_shuffle_ps(a, a, _MM_SHUFFLE(2,3,2,3)), \
//        _mm_shuffle_ps(b, b, _MM_SHUFFLE(3,2,3,2))) \
//)
//
//	// Calcul des 6 sous-sous-d¨¦terminants n¨¦cessaires
//	__m128 ss0 = CALC_DET2(c2, c3); 
//	__m128 ss1 = CALC_DET2(c1, c3); 
//	__m128 ss2 = CALC_DET2(c1, c2);
//
//	__m128 n0 = _mm_set1_ps(tab[1]);
//	__m128 n1 = _mm_set1_ps(tab[2]);
//	// Calcul des 4 sous-d¨¦terminants n¨¦cessaires
//	__m128 s0 = _mm_add_ps(_mm_sub_ss(_mm_mul_ps(_mm_set1_ps(tab[5]), ss0), _mm_mul_ps(_mm_set1_ps(tab[6]), ss1)), _mm_mul_ps(_mm_set1_ps(tab[7]), ss2));
//	__m128 s1 = _mm_add_ps(_mm_sub_ss(_mm_mul_ps(n0, ss0), _mm_mul_ps(n1, ss1)), _mm_mul_ps(_mm_set1_ps(tab[3]), ss2));
//	__m128 s2 = _mm_add_ps(_mm_sub_ss(_mm_mul_ps(n0, ss1), _mm_mul_ps(n1, CALC_DET2(c0, c3))), _mm_mul_ps(_mm_set1_ps(tab[3]), CALC_DET2(c0, c2)));
//	__m128 s3 = _mm_add_ps(_mm_sub_ss(_mm_mul_ps(n0, ss2), _mm_mul_ps(n1, CALC_DET2(c0, c2))), _mm_mul_ps(_mm_set1_ps(tab[3]), CALC_DET2(c0, c1)));
//
//	//// R¨¦duction finale
//	return _mm_cvtss_f32(_mm_sub_ps(
//		_mm_add_ps(
//			_mm_mul_ps(_mm_set1_ps(tab[0]), s0),
//			_mm_mul_ps(_mm_set1_ps(tab[8]), s2)
//		),
//		_mm_add_ps(
//			_mm_mul_ps(_mm_set1_ps(tab[4]), s1),
//			_mm_mul_ps(_mm_set1_ps(tab[12]), s3)
//		)
//	));
//}
Matrix4 Matrix4::Inverse() const 
{
	const float det = GetDeterminant();

	if (std::abs(det) < 1e-8f) {
		throw std::runtime_error("Matrix is not invertible (det == 0)");
	}

	Matrix4 inv;
	const float invDet = 1.0f / det;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			const float sign = ((i + j) % 2 == 0) ? 1.0f : -1.0f;

			float subDet = GetSubMatrix3x3Determinant(i, j);

			inv.tab[j * 4 + i] = sign * subDet * invDet;
		}
	}

	return inv;
}
float Matrix4::GetSubMatrix3x3Determinant(int excludeRow, int excludeCol) const
{
	int idx = 0;
	float elements[9];
	for (int col = 0; col < 4; ++col) {
		if (col == excludeCol) continue;
		for (int row = 0; row < 4; ++row) {
			if (row == excludeRow) continue;
			elements[idx++] = tab[col * 4 + row];
		}
	}
	return elements[0] * (elements[4] * elements[8] - elements[5] * elements[7])
		- elements[1] * (elements[3] * elements[8] - elements[5] * elements[6])
		+ elements[2] * (elements[3] * elements[7] - elements[4] * elements[6]);
}
Matrix4 Matrix4::CreateTransformMatrix(const Vector3& position, const Vector3& rotation, const Vector3& scale)
{
	return CreateTranslationMatrix(position) *
		(CreateXRotationMatrix(rotation.x) *
			CreateYRotationMatrix(rotation.y) *
			CreateZRotationMatrix(rotation.z) *
			CreateScaleMatrix(scale));
}
Vector3 Matrix4::operator*(const Vector4& mult) const
{
	// Chargement du vecteur dans un registre SIMD
	__m128 v = _mm_set_ps(mult.w, mult.z, mult.y, mult.x);

	// Multiplications SIMD (4 composantes en parall¨¨le)
	__m128 r0 = _mm_mul_ps(_mm_loadu_ps(&tab[0]), v);
	__m128 r1 = _mm_mul_ps(_mm_loadu_ps(&tab[4]), v);
	__m128 r2 = _mm_mul_ps(_mm_loadu_ps(&tab[8]), v);
	__m128 r3 = _mm_mul_ps(_mm_loadu_ps(&tab[12]), v);

	// R¨¦duction horizontale (somme des 4 composantes)
	r0 = _mm_hadd_ps(_mm_hadd_ps(r0, r1), _mm_hadd_ps(r2, r3));

	// Extraction des r¨¦sultats
	alignas(16) float res[4];
	_mm_store_ps(res, r0);

	// Division homog¨¨ne
	const float inv_w = 1.0f / (res[3] + static_cast<float>(res[3] == 0.0f));
	return Vector3(res[0] * inv_w, res[1] * inv_w, res[2] * inv_w);
}
Matrix4 Matrix4::GetPerspectiveMatrix(unsigned int width, unsigned int height, float near, float far, float fov)
{
	Matrix4 result;

	float q = 1.0f / tan(0.5f * fov * PI / 180.f);
	float a = q / ((float)width / height);

	float b = (near + far) / (near - far);
	float c = (2.0f * near * far) / (near - far);

	result.tab[0] = a;
	result.tab[5] = q;
	result.tab[10] = b;
	result.tab[14] = -1.0f;
	result.tab[11] = c;

	return result;
}