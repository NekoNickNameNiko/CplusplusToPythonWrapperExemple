#include "pch.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../OpenGL_Modern/Toolbox3D/Include/Matrix4.h"
#include <cmath>
#include <chrono>

// TEST TEMPLATE

//TEST(/*Name*/, /*Name*/)
//{
//	/*TYPE*/ m1(/*....*/), m2(/*....*/);
//	auto start = std::chrono::high_resolution_clock::now();
//	for (int i = 0; i < 10000; ++i) {
//		/*Function need to be tested*/
//	}
//	auto end = std::chrono::high_resolution_clock::now();
//	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//	std::cout << duration.count() << std::endl;
//	EXPECT_LT(duration.count(), /*Time in µs*/); // 100000 µs = 100 ms
//}

// -------------------------------------------------------------------------------- //	
// All Comparator & Define value
// -------------------------------------------------------------------------------- //

constexpr auto EPSILON = 1e-6f;
// Mat2
inline static bool operator==(const Matrix2& mat2, const glm::mat2x2& mat)
{
	return std::abs(mat2.tab[0] - mat[0][0]) < EPSILON &&
		std::abs(mat2.tab[1] - mat[0][1]) < EPSILON &&
		std::abs(mat2.tab[2] - mat[1][0]) < EPSILON &&
		std::abs(mat2.tab[3] - mat[1][1]) < EPSILON;
}
inline static bool operator==(const glm::mat2x2& mat, const Matrix2& mat2)
{
	return mat2 == mat;
}

// Mat3
static void Matrix3Equal(const Matrix3& m1, const glm::mat3x3& m2, float epsilon = EPSILON)
{
	for (int col = 0; col < 3; ++col) {
		for (int row = 0; row < 3; ++row) {
			EXPECT_NEAR(m1.tab[col * 3 + row], m2[col][row], epsilon);
		}
	}
}

// Mat3 x Mat3
inline static bool operator==(const Matrix3& mat3, const Matrix3& otherMat3)
{
	return
		std::abs(mat3.tab[0] - otherMat3.tab[0]) < EPSILON &&
		std::abs(mat3.tab[1] - otherMat3.tab[1]) < EPSILON &&
		std::abs(mat3.tab[2] - otherMat3.tab[2]) < EPSILON &&
		std::abs(mat3.tab[3] - otherMat3.tab[3]) < EPSILON &&
		std::abs(mat3.tab[4] - otherMat3.tab[4]) < EPSILON &&
		std::abs(mat3.tab[5] - otherMat3.tab[5]) < EPSILON &&
		std::abs(mat3.tab[6] - otherMat3.tab[6]) < EPSILON &&
		std::abs(mat3.tab[7] - otherMat3.tab[7]) < EPSILON &&
		std::abs(mat3.tab[8] - otherMat3.tab[8]) < EPSILON;
}


//Mat4
static void Matrix4Equal(const Matrix4& m1, const glm::mat4 m2, float epsilon = EPSILON)
{
	for (int col = 0; col < 4; ++col) {
		for (int row = 0; row < 4; ++row) {
			EXPECT_NEAR(m1.tab[col * 4 + row], m2[col][row], epsilon);
		}
	}
}
// -------------------------------------------------------------------------------- //	
//									TEST MATRIX2									//
// -------------------------------------------------------------------------------- //

TEST(Matrix2Test, GetDiagonal)
{
	Matrix2 m(1.f, 2.f, 3.f, 4.f);
	Vector2 v = m.GetDiagonal();

	EXPECT_FLOAT_EQ(v.x, 1.f);
	EXPECT_FLOAT_EQ(v.y, 4.f);
}
TEST(Matrix2Test, GetOpposed2)
{
	Matrix2 m(1.f, 2.f, 3.f, 4.f);
	Matrix2 mOppo = m.GetOpposed2();
	EXPECT_FLOAT_EQ(mOppo.tab[0], -1.f);
	EXPECT_FLOAT_EQ(mOppo.tab[2], -2.f);
	EXPECT_FLOAT_EQ(mOppo.tab[1], -3.f);
	EXPECT_FLOAT_EQ(mOppo.tab[3], -4.f);
}
TEST(Matrix2Test, GetTransposed2)
{
	Matrix2 m(1.f, 2.f, 3.f, 4.f);
	glm::mat2x2 g(1.f, 3.f, 2.f, 4.f);
	Matrix2 mTranspo = m.GetTransposed2();
	glm::mat2x2 gTranspo = glm::transpose(g);
	EXPECT_TRUE(mTranspo == gTranspo);
}
TEST(Matrix2Test, GetTrace)
{
	Matrix2 m(1.f, 2.f, 3.f, 4.f);

	float trace = m.GetTrace();

	EXPECT_FLOAT_EQ(trace, 5.f);
}
TEST(Matrix2Test, GetDeterminant)
{
	Matrix2 m(1.f, 2.f, 3.f, 4.f);
	glm::mat2x2 g(1.f, 3.f, 2.f, 4.f);

	float det = m.GetDeterminant();
	float detglm = glm::determinant(g);
	EXPECT_FLOAT_EQ(det, detglm);
}
TEST(Matrix2Test, Inverse)
{
	Matrix2 m(4.f, 7.f, 2.f, 6.f);
	glm::mat2x2 g(4.f, 2.f, 7.f, 6.f);

	Matrix2 inv = m.Inverse();
	glm::mat2x2 invglm = glm::inverse(g);
	EXPECT_TRUE(inv == invglm);
}
TEST(Matrix2Test, SingularMatrix)
{
	Matrix2 m(2.f, 1.f, 4.f, 2.f);

	EXPECT_THROW(m.Inverse(), std::runtime_error);
}
TEST(Matrix2Test, Rotation180)
{
	Matrix2 m(1.f, 2.f, 3.f, 4.f);

	m *= m.Rotation(PI);

	EXPECT_FLOAT_EQ(m.tab[0], -1.f);
	EXPECT_FLOAT_EQ(m.tab[2], -2.f);
	EXPECT_FLOAT_EQ(m.tab[1], -3.f);
	EXPECT_FLOAT_EQ(m.tab[3], -4.f);
}
TEST(Matrix2Test, OperatorMultiply)
{
	Matrix2 m1(1.f, 2.f, 3.f, 4.f);
	Matrix2 m2(5.f, 6.f, 7.f, 8.f);
	Matrix2 result = m1 * m2;

	glm::mat2 g1(1.f, 3.f, 2.f, 4.f);
	glm::mat2 g2(5.f, 7.f, 6.f, 8.f);
	glm::mat2 gResult = g1 * g2;

	EXPECT_TRUE(result == gResult);
}
TEST(Matrix2Test, OperatorDivide)
{
	Matrix2 m1(1.f, 2.f, 3.f, 4.f);
	Matrix2 m2(5.f, 6.f, 7.f, 8.f);
	Matrix2 result = m1 / m2;

	glm::mat2 g1(1.f, 3.f, 2.f, 4.f);
	glm::mat2 g2(5.f, 7.f, 6.f, 8.f);
	glm::mat2 gResult = g1 * glm::inverse(g2);

	EXPECT_TRUE(result == gResult);
}
TEST(Matrix2Test, OperatorAdd)
{
	Matrix2 m1(1.f, 2.f, 3.f, 4.f);
	Matrix2 m2(5.f, 6.f, 7.f, 8.f);
	Matrix2 result = m1 + m2;

	glm::mat2 g1(1.f, 3.f, 2.f, 4.f);
	glm::mat2 g2(5.f, 7.f, 6.f, 8.f);
	glm::mat2 gResult = g1 + g2;

	EXPECT_TRUE(result == gResult);
}
TEST(Matrix2Test, OperatorSubtract)
{
	Matrix2 m1(1.f, 2.f, 3.f, 4.f);
	Matrix2 m2(5.f, 6.f, 7.f, 8.f);
	Matrix2 result = m1 - m2;

	glm::mat2 g1(1.f, 3.f, 2.f, 4.f);
	glm::mat2 g2(5.f, 7.f, 6.f, 8.f);
	glm::mat2 gResult = g1 - g2;

	EXPECT_TRUE(result == gResult);
}
TEST(Matrix2Test, OperatorMultiplyAssign)
{
	Matrix2 m1(1.f, 2.f, 3.f, 4.f);
	Matrix2 m2(5.f, 6.f, 7.f, 8.f);
	m1 *= m2;

	glm::mat2 g1(1.f, 3.f, 2.f, 4.f);
	glm::mat2 g2(5.f, 7.f, 6.f, 8.f);
	g1 *= g2;

	EXPECT_TRUE(m1 == g1);
}
TEST(Matrix2Test, OperatorDivideAssign)
{
	Matrix2 m1(1.f, 2.f, 3.f, 4.f);
	Matrix2 m2(5.f, 6.f, 7.f, 8.f);
	m1 /= m2;

	glm::mat2 g1(1.f, 3.f, 2.f, 4.f);
	glm::mat2 g2(5.f, 7.f, 6.f, 8.f);
	g1 *= glm::inverse(g2);

	EXPECT_TRUE(m1 == g1);
}
TEST(Matrix2Test, OperatorAddAssign)
{
	Matrix2 m1(1.f, 2.f, 3.f, 4.f);
	Matrix2 m2(5.f, 6.f, 7.f, 8.f);
	m1 += m2;

	glm::mat2 g1(1.f, 3.f, 2.f, 4.f);
	glm::mat2 g2(5.f, 7.f, 6.f, 8.f);
	g1 += g2;

	EXPECT_TRUE(m1 == g1);
}
TEST(Matrix2Test, OperatorSubtractAssign)
{
	Matrix2 m1(1.f, 2.f, 3.f, 4.f);
	Matrix2 m2(5.f, 6.f, 7.f, 8.f);
	m1 -= m2;

	glm::mat2 g1(1.f, 3.f, 2.f, 4.f);
	glm::mat2 g2(5.f, 7.f, 6.f, 8.f);
	g1 -= g2;

	EXPECT_TRUE(m1 == g1);
}
TEST(Matrix2Test, ProductScalarAssign)
{
	Matrix2 m1(1.f, 2.f, 3.f, 4.f);
	m1 *= 5.f;

	glm::mat2 g1(1.f, 3.f, 2.f, 4.f);
	g1 *= 5.f;

	EXPECT_TRUE(m1 == g1);
}
TEST(Matrix2Test, ProductScalar)
{
	Matrix2 m1(1.f, 2.f, 3.f, 4.f);
	m1 = m1 * 5.f;

	glm::mat2 g1(1.f, 3.f, 2.f, 4.f);
	g1 *= 5.f;

	EXPECT_TRUE(m1 == g1);
}

// -------------------------------------------------------------------------------- //	
//									TEST PERFORMANCE								//
// -------------------------------------------------------------------------------- //

TEST(Matrix2Performance, MatrixMultiply)
{
	Matrix2 m1(1.f, 2.f, 3.f, 4.f), m2(1.f, 2.f, 3.f, 4.f);
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 10000; ++i) {
		Matrix2 res = m1 * m2;
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	EXPECT_LT(duration.count(), 1000);
}

// -------------------------------------------------------------------------------- //	
//									TEST MATRIX3									//
// -------------------------------------------------------------------------------- //

TEST(Matrix3Test, GetOpposed3)
{
	Matrix3 m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);

	Matrix3 mOppo = m1.GetOpposed3();

	EXPECT_TRUE(
		mOppo.tab[0] == -1.f &&
		mOppo.tab[1] == -4.f &&
		mOppo.tab[2] == -7.f &&
		mOppo.tab[3] == -2.f &&
		mOppo.tab[4] == -5.f &&
		mOppo.tab[5] == -8.f &&
		mOppo.tab[6] == -3.f &&
		mOppo.tab[7] == -6.f &&
		mOppo.tab[8] == -9.f);
}
TEST(Matrix3Test, GetTransposed3)
{
	Matrix3 m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
	glm::mat3 g1(1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f);

	Matrix3 mT = m1.GetTransposed3();
	glm::mat3 gT = glm::transpose(g1);

	Matrix3Equal(mT, gT);
}
TEST(Matrix3Test, AddMatrix3)
{
	Matrix3 m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
	Matrix3 m2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);

	glm::mat3 g1(1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f);
	glm::mat3 g2(1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f);

	m1 = m1 + m2;
	g1 = g1 + g2;

	Matrix3Equal(m1, g1);
}
TEST(Matrix3Test, GetTrace)
{
	Matrix3 m1(
		1.f, 2.f, 3.f,
		4.f, 5.f, 6.f,
		7.f, 8.f, 9.f);

	float trace = m1.GetTrace();

	EXPECT_FLOAT_EQ(trace, 15.f);
}
TEST(Matrix3Test, GetDeterminant)
{
	Matrix3 m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
	glm::mat3 g1(1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f);

	float det = m1.GetDeterminant();
	float detglm = glm::determinant(g1);
	EXPECT_FLOAT_EQ(det, detglm);
}
TEST(Matrix3Test, Inverse)
{
	Matrix3 m1(
		2.f, -1.f, 0.f,
		-1.f, 2.f, -1.f,
		0.f, -1.f, 2.f
	);
	glm::mat3 g1(
		2.f, -1.f, 0.f,
		-1.f, 2.f, -1.f,
		0.f, -1.f, 2.f);

	Matrix3 inv = m1.Inverse();
	glm::mat3x3 invglm = glm::inverse(g1);
	Matrix3Equal(inv, invglm);
}
TEST(Matrix3Test, SingularMatrix)
{
	Matrix3 m1(
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f
	);

	EXPECT_THROW(m1.Inverse(), std::runtime_error);
}

TEST(Matrix3Test, OperatorMultiply)
{
	Matrix3 m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
	Matrix3 m2(10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f, 18.f);
	Matrix3 result = m1 * m2;

	glm::mat3 g1(1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f);
	glm::mat3 g2(10.f, 13.f, 16.f, 11.f, 14.f, 17.f, 12.f, 15.f, 18.f);
	glm::mat3 gResult = g1 * g2;

	Matrix3Equal(result, gResult);
}
TEST(Matrix3Test, OperatorDivide)
{
	Matrix3 m1(2.f, -1.f, 0.f, -1.f, 2.f, -1.f, 0.f, -1.f, 2.f);
	Matrix3 m2(2.f, -1.f, 0.f, -1.f, 2.f, -1.f, 0.f, -1.f, 2.f);
	Matrix3 result = m1 / m2;

	glm::mat3 g1(2.f, -1.f, 0.f, -1.f, 2.f, -1.f, 0.f, -1.f, 2.f);
	glm::mat3 g2(2.f, -1.f, 0.f, -1.f, 2.f, -1.f, 0.f, -1.f, 2.f);
	glm::mat3 gResult = g1 * glm::inverse(g2);

	Matrix3Equal(result, gResult);
}
TEST(Matrix3Test, OperatorAdd)
{
	Matrix3 m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
	Matrix3 m2(10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f, 18.f);
	Matrix3 result = m1 + m2;

	glm::mat3 g1(1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f);
	glm::mat3 g2(10.f, 13.f, 16.f, 11.f, 14.f, 17.f, 12.f, 15.f, 18.f);
	glm::mat3 gResult = g1 + g2;

	Matrix3Equal(result, gResult);
}
TEST(Matrix3Test, OperatorSubtract)
{
	Matrix3 m1(1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f);
	Matrix3 m2(10.f, 13.f, 16.f, 11.f, 14.f, 17.f, 12.f, 15.f, 18.f);
	Matrix3 result = m1 - m2;

	glm::mat3 g1(1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f);
	glm::mat3 g2(10.f, 13.f, 16.f, 11.f, 14.f, 17.f, 12.f, 15.f, 18.f);
	glm::mat3 gResult = g1 - g2;

	Matrix3Equal(result, gResult);
}
TEST(Matrix3Test, OperatorMultiplyAssign)
{
	Matrix3 m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
	Matrix3 m2(10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f, 18.f);
	m1 *= m2;

	glm::mat3 g1(1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f);
	glm::mat3 g2(10.f, 13.f, 16.f, 11.f, 14.f, 17.f, 12.f, 15.f, 18.f);
	g1 *= g2;

	Matrix3Equal(m1, g1);
}
TEST(Matrix3Test, OperatorDivideAssign)
{
	Matrix3 m1(2.f, -1.f, 0.f, -1.f, 2.f, -1.f, 0.f, -1.f, 2.f);
	Matrix3 m2(2.f, -1.f, 0.f, -1.f, 2.f, -1.f, 0.f, -1.f, 2.f);
	m1 /= m2;

	glm::mat3 g1(2.f, -1.f, 0.f, -1.f, 2.f, -1.f, 0.f, -1.f, 2.f);
	glm::mat3 g2(2.f, -1.f, 0.f, -1.f, 2.f, -1.f, 0.f, -1.f, 2.f);
	g1 *= glm::inverse(g2);

	Matrix3Equal(m1, g1);
}
TEST(Matrix3Test, OperatorAddAssign)
{
	Matrix3 m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
	Matrix3 m2(10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f, 18.f);
	m1 += m2;

	glm::mat3 g1(1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f);
	glm::mat3 g2(10.f, 13.f, 16.f, 11.f, 14.f, 17.f, 12.f, 15.f, 18.f);
	g1 += g2;

	Matrix3Equal(m1, g1);
}
TEST(Matrix3Test, OperatorSubtractAssign)
{
	Matrix3 m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
	Matrix3 m2(10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f, 18.f);
	m1 -= m2;

	glm::mat3 g1(1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f);
	glm::mat3 g2(10.f, 13.f, 16.f, 11.f, 14.f, 17.f, 12.f, 15.f, 18.f);
	g1 -= g2;

	Matrix3Equal(m1, g1);
}
TEST(Matrix3Test, ProductScalarAssign)
{
	Matrix3 m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
	m1 *= 5.f;

	glm::mat3 g1(1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f);
	g1 *= 5.f;

	Matrix3Equal(m1, g1);
}
TEST(Matrix3Test, ProductScalar)
{
	Matrix3 m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
	m1 = m1 * 5.f;

	glm::mat3 g1(1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f);
	g1 *= 5.f;

	Matrix3Equal(m1, g1);
}

// -------------------------------------------------------------------------------- //	
//									TEST PERFORMANCE								//
// -------------------------------------------------------------------------------- //

TEST(Matrix3Performance, MatrixMultiply)
{
	Matrix3 m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f), m2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 10000; ++i) {
		Matrix3 res = m1 * m2;
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	EXPECT_LT(duration.count(), 1000);
}

// -------------------------------------------------------------------------------- //	
//									TEST ROTATION   								//
// -------------------------------------------------------------------------------- //

TEST(Matrix3RotationTest, XRotationMatrix_IdentityAtZeroAngle)
{
	Matrix3 rot = Matrix3::CreateXRotationMatrix(0.0f);
	Matrix3 identity = Matrix3::GetIdentity3();

	EXPECT_TRUE(rot == identity);
}
TEST(Matrix3RotationTest, XRotationMatrix_90Degrees)
{
	float angle = PI / 2.f;

	Matrix3 matR = Matrix3::CreateXRotationMatrix(angle);

	glm::mat4 glmMat4R = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat3 glmMat3R = glm::mat3(glmMat4R);

	Matrix3Equal(matR, glmMat3R);
}
TEST(Matrix3RotationTest, XRotationMatrix_InverseIsTranspose)
{
	Matrix3 rot = Matrix3::CreateXRotationMatrix(1.234f);
	Matrix3 inv = rot.Inverse();
	Matrix3 trans = rot.GetTransposed3();

	for (int i = 0; i < 9; ++i) {
		EXPECT_NEAR(inv.tab[i], trans.tab[i], EPSILON);
	}
}
TEST(Matrix3RotationTest, YRotationMatrix_180Degrees)
{
	float angle = PI;

	Matrix3 matR = Matrix3::CreateYRotationMatrix(angle);

	glm::mat4 glmMat4R = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat3 glmMat3R = glm::mat3(glmMat4R);

	Matrix3Equal(matR, glmMat3R);
}
TEST(Matrix3RotationTest, YRotationMatrix_DeterminantIsOne)
{
	Matrix3 rot = Matrix3::CreateYRotationMatrix(0.789f);
	EXPECT_NEAR(rot.GetDeterminant(), 1.0f, EPSILON);
}
TEST(Matrix3RotationTest, ZRotationMatrix_360Degrees)
{
	Matrix3 rot = Matrix3::CreateZRotationMatrix(PI * 2);
	Matrix3 identity = Matrix3::GetIdentity3();

	EXPECT_TRUE(rot == identity);
}
TEST(Matrix3RotationTest, ZRotationMatrix_Composition)
{
	Matrix3 rot1 = Matrix3::CreateZRotationMatrix(PI / 4);
	Matrix3 rot2 = Matrix3::CreateZRotationMatrix(PI / 4);
	Matrix3 expected = Matrix3::CreateZRotationMatrix(PI / 2);
	Matrix3 result = rot1 * rot2;

	EXPECT_TRUE(expected == result);
}
TEST(Matrix3RotationTest, RotateMatrix_XYZ_Order) {
	Matrix3 rot = Matrix3::RotateMatrix(PI / 2, PI / 2, PI / 2);
	Matrix3 xRot = Matrix3::CreateXRotationMatrix(PI / 2);
	Matrix3 yRot = Matrix3::CreateYRotationMatrix(PI / 2);
	Matrix3 zRot = Matrix3::CreateZRotationMatrix(PI / 2);
	Matrix3 expected = zRot * yRot * xRot;

	EXPECT_TRUE(expected == rot);
}
TEST(Matrix3RotationTest, RotateMatrix_SingleAxis) {
	Matrix3 rotX = Matrix3::RotateMatrix(0.1f, 0.0f, 0.0f);
	Matrix3 expectedX = Matrix3::CreateXRotationMatrix(0.1f);
	Matrix3 rotY = Matrix3::RotateMatrix(0.0f, 0.1f, 0.0f);
	Matrix3 expectedY = Matrix3::CreateYRotationMatrix(0.1f);
	Matrix3 rotZ = Matrix3::RotateMatrix(0.0f, 0.0f, 0.1f);
	Matrix3 expectedZ = Matrix3::CreateZRotationMatrix(0.1f);


	EXPECT_TRUE(rotX == expectedX);
	EXPECT_TRUE(rotY == expectedY);
	EXPECT_TRUE(rotZ == expectedZ);
}
TEST(Matrix3RotationTest, InverseProperty) {
	Matrix3 m(
		2.f, -1.f, 0.f,
		-1.f, 2.f, -1.f,
		0.f, -1.f, 2.f
	);
	Matrix3 inv = m.Inverse();
	Matrix3 identity = m * inv;
	EXPECT_TRUE(identity == Matrix3::GetIdentity3());
}

// -------------------------------------------------------------------------------- //	
//									TEST MATRIX4									//
// -------------------------------------------------------------------------------- //

TEST(Matrix4Test, GetTrace)
{
	Matrix4 m(
		1.f, 0.f, 0.f, 0.f,
		0.f, 2.f, 0.f, 0.f,
		0.f, 0.f, 3.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	);

	float trace = m.GetTrace();

	EXPECT_NEAR(trace, 7.f, EPSILON);
}
TEST(Matrix4Test, GetDeterminant)
{
	Matrix4 m(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);
	glm::mat4 g(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);

	float det = m.GetDeterminant();
	float gdet = glm::determinant(g);

	EXPECT_NEAR(det, gdet, EPSILON);
}
TEST(Matrix4Test, Inverse)
{
	Matrix4 m(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);
	glm::mat4 g(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);

	m = m.Inverse();
	g = glm::inverse(g);

	Matrix4Equal(m, g);
}
TEST(Matrix4Test, SingularMatrix)
{
	Matrix4 singular(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);

	EXPECT_THROW(singular.Inverse(), std::runtime_error);
}
TEST(Matrix4Test, Perspective) 
{
	Matrix4 mat1 = Matrix4::CreateTransformMatrix();
	glm::mat4 glmMat(1.0f);
	float fov = 90.f;
	float aspect = 1;
	float near = 0.1f;
	float far = 100.f;

	glm::mat4 perspective = glm::perspective(fov, aspect, near, far);
	Matrix4 mat = Matrix4::PerspectiveRH_NO(fov, aspect, near, far);

	Matrix4Equal(mat1, glmMat);
}
TEST(Matrix4Test, OperatorMultiplyAssign)
{
	Matrix4 m1(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f),
		m2(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);

	glm::mat4 g1(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f),
		g2(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);

	m1 *= m2;
	g1 *= g2;

	Matrix4Equal(m1, g1);
}
TEST(Matrix4Test, OperatorDivideAssign)
{
	Matrix4 m1(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f),
		m2(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);

	glm::mat4 g1(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f),
		g2(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);

	m1 /= m2;
	g1 /= g2;

	Matrix4Equal(m1, g1);
}
TEST(Matrix4Test, OperatorAddAssign)
{
	Matrix4 m1(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f),
		m2(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);

	glm::mat4 g1(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f),
		g2(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);

	m1 += m2;
	g1 += g2;

	Matrix4Equal(m1, g1);
}
TEST(Matrix4Test, OperatorSubtractAssign)
{
	Matrix4 m1(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f),
		m2(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);

	glm::mat4 g1(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f),
		g2(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);

	m1 -= m2;
	g1 -= g2;

	Matrix4Equal(m1, g1);
}
TEST(Matrix4Test, OperatorMultiply)
{
	Matrix4 m1(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f),
		m2(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);

	glm::mat4 g1(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f),
		g2(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);

	m1 = m1 * m2;
	g1 = g1 * g2;

	Matrix4Equal(m1, g1);
}
TEST(Matrix4Test, OperatorDivide)
{
	Matrix4 m1(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f),
		m2(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);

	glm::mat4 g1(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f),
		g2(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);

	m1 = m1 / m2;
	g1 = g1 / g2;

	Matrix4Equal(m1, g1);
}
TEST(Matrix4Test, OperatorAdd)
{
	Matrix4 m1(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f),
		m2(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);

	glm::mat4 g1(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f),
		g2(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);

	m1 = m1 + m2;
	g1 = g1 + g2;

	Matrix4Equal(m1, g1);
}
TEST(Matrix4Test, OperatorSubtract)
{
	Matrix4 m1(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f),
		m2(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);

	glm::mat4 g1(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f),
		g2(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);

	m1 = m1 - m2;
	g1 = g1 - g2;

	Matrix4Equal(m1, g1);
}


// -------------------------------------------------------------------------------- //	
//									TEST ROTATION   								//
// -------------------------------------------------------------------------------- //

TEST(Matrix4Test, CreateTranslationMatrix)
{
	Vector3 translation(2.0f, -3.5f, 1.0f);

	Matrix4 mat1 = Matrix4::CreateTranslationMatrix(translation);
	glm::mat4 glmMat = glm::translate(glm::mat4(1.0f),
		glm::vec3(translation.x, translation.y, translation.z));

	Matrix4Equal(mat1, glmMat);
}
TEST(Matrix4Test, CreateScaleMatrix) {
	Vector3 scale(1.5f, 2.0f, 0.5f);

	Matrix4 mat1 = Matrix4::CreateScaleMatrix(scale);
	glm::mat4 glmMat = glm::scale(glm::mat4(1.0f),
		glm::vec3(scale.x, scale.y, scale.z));

	Matrix4Equal(mat1, glmMat);
}
TEST(Matrix4Test, CreateXRotationMatrix) {
	float angle = PI / 4.0f; // 45 degrés

	Matrix4 mat1 = Matrix4::CreateXRotationMatrix(angle);
	glm::mat4 glmMat = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.0f, 0.0f));

	Matrix4Equal(mat1, glmMat);
}
TEST(Matrix4Test, CreateYRotationMatrix) {
	float angle = PI / 3.0f; // 60 degrés

	Matrix4 mat1 = Matrix4::CreateYRotationMatrix(angle);
	glm::mat4 glmMat = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));

	Matrix4Equal(mat1, glmMat);
}
TEST(Matrix4Test, CreateZRotationMatrix) {
	float angle = PI / 6.0f; // 30 degrés

	Matrix4 mat1 = Matrix4::CreateZRotationMatrix(angle);
	glm::mat4 glmMat = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));

	Matrix4Equal(mat1, glmMat);
}
TEST(Matrix4Test, CreateTransformMatrix_TranslationOnly) {
	Vector3 pos(1.0f, 2.0f, 3.0f);
	Vector3 rot(0.0f, 0.0f, 0.0f);
	Vector3 scale(1.0f, 1.0f, 1.0f);

	Matrix4 mat1 = Matrix4::CreateTransformMatrix(pos, rot, scale);
	glm::mat4 glmMat = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, pos.z));

	Matrix4Equal(mat1, glmMat);
}
TEST(Matrix4Test, CreateTransformMatrix_RotationOnly)
{
	Vector3 pos(0.0f, 0.0f, 0.0f);
	Vector3 rot(PI / 4, PI / 3, PI / 6); // 45°, 60°, 30°
	Vector3 scale(1.0f, 1.0f, 1.0f);

	Matrix4 mat1 = Matrix4::CreateTransformMatrix(pos, rot, scale);

	glm::mat4 glmMat = glm::mat4(1.0f);
	glmMat = glm::rotate(glmMat, rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glmMat = glm::rotate(glmMat, rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glmMat = glm::rotate(glmMat, rot.x, glm::vec3(1.0f, 0.0f, 0.0f));

	Matrix4Equal(mat1, glmMat, 1e-4f);
}
TEST(Matrix4Test, CreateTransformMatrix_ScaleOnly) {
	Vector3 pos(0.0f, 0.0f, 0.0f);
	Vector3 rot(0.0f, 0.0f, 0.0f);
	Vector3 scale(2.0f, 3.0f, 0.5f);


	Matrix4 mat1 = Matrix4::CreateTransformMatrix(pos, rot, scale);

	glm::mat4 glmMat = glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, scale.z));

	Matrix4Equal(mat1, glmMat);
}
TEST(Matrix4Test, CreateTransformMatrix_Combined) {
	Vector3 pos(1.0f, -2.0f, 3.0f);
	Vector3 rot(PI / 6, PI / 4, PI / 3); // 30°, 45°, 60°
	Vector3 scale(1.5f, 2.0f, 0.8f);

	Matrix4 mat1 = Matrix4::CreateTransformMatrix(pos, rot, scale);

	glm::mat4 glmMat = glm::mat4(1.0f);
	glmMat = glm::scale(glmMat, glm::vec3(scale.x, scale.y, scale.z));
	glmMat = glm::rotate(glmMat, rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glmMat = glm::rotate(glmMat, rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glmMat = glm::rotate(glmMat, rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glmMat = glm::translate(glmMat, glm::vec3(pos.x, pos.y, pos.z));

	Matrix4Equal(mat1, glmMat, 1e-4f);
}
TEST(Matrix4Test, CreateTransformMatrix_Identity) {
	Matrix4 mat1 = Matrix4::CreateTransformMatrix();
	glm::mat4 glmMat(1.0f);

	Matrix4Equal(mat1, glmMat);
}

// -------------------------------------------------------------------------------- //	
//									TEST PERFORMANCE								//
// -------------------------------------------------------------------------------- //

TEST(Matrix4TestPerformance, MatrixDeterminant)
{
	Matrix4 m1(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 10000; ++i) {
		volatile float res = m1.GetDeterminant();
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	EXPECT_LT(duration.count(), 1000); // 100000 µs = 100 ms
}
TEST(Matrix4TestPerformance, Inverse)
{
	Matrix4 m(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 10000; ++i) {
		volatile Matrix4 res = m.Inverse();
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	EXPECT_LT(duration.count(), 12000); // 100000 µs = 100 ms
}
TEST(Matrix4TestPerformance, OperatorMultiply)
{
	Matrix4 m1(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);
	Matrix4 m2(1.f, 0.f, 0.f, 0.f, 0.f, 2.f, 0.f, 0.f, 0.f, 0.f, 3.f, 0.f, 0.f, 0.f, 0.f, 1.f);
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 10000; ++i) {
		volatile Matrix4 res = m1 * m2;
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	EXPECT_LT(duration.count(), 1000); // 100000 µs = 100 ms
}
