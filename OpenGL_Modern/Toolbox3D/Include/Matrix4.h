#pragma once

#include "Matrix3.h"

namespace Bwt
{
	namespace Core
	{
		namespace Maths
		{
			class Matrix4
			{
			public:
				float tab[16];

				Matrix4(FillAll_t, float init);
				Matrix4(const Matrix4& copy);
				Matrix4(const float* values);
				inline Matrix4(float m0 = 0.f, float m1 = 0.f, float m2 = 0.f, float m3 = 0.f,
					float m4 = 0.f, float m5 = 0.f, float m6 = 0.f, float m7 = 0.f,
					float m8 = 0.f, float m9 = 0.f, float m10 = 0.f, float m11 = 0.f,
					float m12 = 0.f, float m13 = 0.f, float m14 = 0.f, float m15 = 0.f
				)
					: tab{ m0, m4, m8, m12, m1, m5, m9, m13, m2 ,m6, m10, m14, m3, m7, m11, m15 } {
				}


				// -------------------------------------------------------------------------------- //	
				// Matrix value getter
				// -------------------------------------------------------------------------------- //

				class Row {
				private:
					float* rowData;
				public:
					Row(float* rowData) : rowData(rowData) {}

					inline float& operator[](int col) {
						return rowData[col];
					}
				};
				inline Row operator[](int row) {
					return Row(&tab[row * 4]);
				}

				// -------------------------------------------------------------------------------- //
				// Basic Matrix Operations
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Returns the 4x4 identity matrix.
				/// </summary>
				/// <returns>The identity matrix.</returns>
				static Matrix4 GetIdentity4();

				/// <summary>
				/// Returns the diagonal vector of the matrix.
				/// </summary>
				/// <returns>A Vector4 containing the diagonal elements.</returns>
				Vector4 GetDiagonal();

				/// <summary>
				/// Returns the additive inverse (negated version) of the matrix.
				/// </summary>
				/// <returns>The opposed matrix.</returns>
				Matrix4 GetOpposed4() const;

				/// <summary>
				/// Returns the transpose of the matrix.
				/// </summary>
				/// <returns>The transposed matrix.</returns>
				Matrix4 GetTransposed4() const;


				// -------------------------------------------------------------------------------- //	
				// Arithmetic Operations on the Matrix
				// -------------------------------------------------------------------------------- //	
				
				/// <summary>
				/// Returns the sum of this matrix and another matrix.
				/// </summary>
				/// <param name="other">The matrix to add.</param>
				/// <returns>The resulting matrix after addition.</returns>
				Matrix4 AddMatrix4(const Matrix4& other) const;

				/// <summary>
				/// Returns the result of scalar multiplication on this matrix.
				/// </summary>
				/// <param name="n">The scalar value to multiply the matrix by.</param>
				/// <returns>The resulting matrix after multiplication.</returns>
				Matrix4 ProductScalar(float n);

				/// <summary>
				/// Returns the result of matrix multiplication with another 4x4 matrix.
				/// </summary>
				/// <param name="other">The matrix to multiply with.</param>
				/// <returns>The resulting matrix after multiplication.</returns>
				Matrix4 ProductMatrix4(const Matrix4& other) const;


				// -------------------------------------------------------------------------------- //	
				// Matrix Properties
				// -------------------------------------------------------------------------------- //	

				/// <summary>
				/// Return the trace of the matrix (sum of the diagonal elements).
				/// </summary>
				/// <returns>The trace of the matrix.</returns>
				float GetTrace();

				/// <summary>
				/// Returns the determinant of the matrix.
				/// </summary>
				/// <returns>The determinant of the matrix.</returns>
				float GetDeterminant() const;

				//float GetDeterminantSSE() const;

				/// <summary>
				/// Returns the inverse of the matrix if it exists.
				/// </summary>
				/// <returns>The inverse matrix, or an identity matrix if non-invertible.</returns>
				Matrix4 Inverse() const;

				/// <summary>
				/// Returns the 3x3 submatrix by excluding one row and one column.
				/// </summary>
				/// <param name="excludeRow">Row to exclude (0-3).</param>
				/// <param name="excludeCol">Column to exclude (0-3).</param>
				/// <returns>The resulting submatrix after exclusion of the specified row and column.</returns>
				Matrix3 GetSubMatrix(int excludeRow, int excludeCol) const;

				float GetSubMatrix3x3Determinant(int excludeRow, int excludeCol) const;

				static Matrix4 PerspectiveRH_NO(float fovy, float aspect, float zNear, float zFar)
				{
					float const tanHalfFovy = tan(fovy / 2.f);

					Matrix4 Result = Matrix4::GetIdentity4();
					Result.tab[0]= static_cast<float>(1) / (aspect * tanHalfFovy);
					Result.tab[5] = static_cast<float>(1) / (tanHalfFovy);
					Result.tab[10] = -(zFar + zNear) / (zFar - zNear);
					Result.tab[11] = -static_cast<float>(1);
					Result.tab[15] = -(static_cast<float>(2) * zFar * zNear) / (zFar - zNear);
					return Result;
				}
				// -------------------------------------------------------------------------------- //		
				// Rotation matrix      
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Creates a transformation matrix from position, rotation, and scale.
				/// </summary>
				/// <param name="position">Translation vector.</param>
				/// <param name="rotation">Rotation in radian (pitch, yaw, roll).</param>
				/// <param name="scale">Scaling vector.</param>
				static Matrix4 CreateTransformMatrix(const Vector3& position = Vector3(0, 0, 0), const Vector3& rotation = Vector3(0, 0, 0), const Vector3& scale = Vector3(1, 1, 1));

				/// <summary>
				/// Creates a translation matrix.
				/// </summary>
				/// <param name="translation">Translation vector.</param>
				static Matrix4 CreateTranslationMatrix(const Vector3& translation);

				/// <summary>
				/// Creates a scale matrix.
				/// </summary>
				/// <param name="scale">Scaling vector.</param>
				static Matrix4 CreateScaleMatrix(const Vector3& scale);

				/// <summary>
				/// Creates a rotation matrix around the X-axis.
				/// </summary>
				/// <param name="angle">Angle in Radian.</param>
				static Matrix4 CreateXRotationMatrix(float angle);

				/// <summary>
				/// Creates a rotation matrix around the Y-axis.
				/// </summary>
				/// <param name="angle">Angle in Radian.</param>
				static Matrix4 CreateYRotationMatrix(float angle);

				/// <summary>
				/// Creates a rotation matrix around the Z-axis.
				/// </summary>
				/// <param name="angle">Angle in Radian.</param>
				static Matrix4 CreateZRotationMatrix(float angle);

				static Matrix4 GetPerspectiveMatrix(unsigned int width, unsigned int height, float near, float far, float fov);

				// -------------------------------------------------------------------------------- //	
				// Display inline
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Prints all values of the Matrix4 to the console.
				/// </summary>
				inline void Print() const
				{
					std::cout
						<< tab[0] << " " << tab[1] << " " << tab[2] << " " << tab[3] << "\n"
						<< tab[4] << " " << tab[5] << " " << tab[6] << " " << tab[7] << "\n"
						<< tab[8] << " " << tab[9] << " " << tab[10] << " " << tab[11] << "\n"
						<< tab[12] << " " << tab[13] << " " << tab[14] << " " << tab[15] << "\n";
				}

				// -------------------------------------------------------------------------------- //	
				// Overload operators inline
				// -------------------------------------------------------------------------------- //

				Matrix4 operator*(const Matrix4& other) const;
				Matrix4 operator/(const Matrix4& other)const;
				Matrix4 operator+(const Matrix4& other) const;
				Matrix4 operator-(const Matrix4& other) const;

				Matrix4& operator*=(const Matrix4& other);
				Matrix4& operator/=(const Matrix4& other);
				Matrix4& operator+=(const Matrix4& other);
				Matrix4& operator-=(const Matrix4& other);

				Matrix4 operator*(float n);
				Matrix4 operator*=(float n);

				Vector3 operator*(const Vector4& mult) const;
			};
		}
	}
}

#include "../Inline/Matrix4.inl"
