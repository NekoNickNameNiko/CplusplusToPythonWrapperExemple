#pragma once

#include "Matrix2.h"

namespace Bwt
{
	namespace Core
	{
		namespace Maths
		{
			class Matrix3
			{
			public:
				float tab[9]; //3x3


				Matrix3(FillAll_t, float init);
				Matrix3(const Matrix3& copy);
				inline Matrix3(float m0 = 0.f, float m1 = 0.f, float m2 = 0.f, float m3 = 0.f, float m4 = 0.f, float m5 = 0.f, float m6 = 0.f, float m7 = 0.f, float m8 = 0.f)
					: tab{ m0, m3, m6, m1, m4, m7, m2, m5, m8 }
				{ }


				// -------------------------------------------------------------------------------- //	
				// Basic Matrix Operations
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Return the identity matrix of 3x3.
				/// </summary>
				/// <returns>The identity matrix.</returns>
				static Matrix3 GetIdentity3();

				/// <summary>
				/// Return the diagonal elements of the matrix as a Vector3.
				/// </summary>
				/// <returns>A Vector3 containing the diagonal elements.</returns>
				Vector3 GetDiagonal() const;

				/// <summary>
				/// Return the opposed (negated) matrix.
				/// </summary>
				/// <returns>The opposed matrix.</returns>
				Matrix3 GetOpposed3() const;

				/// <summary>
				/// Return the transposed matrix.
				/// </summary>
				/// <returns>The transposed matrix.</returns>
				Matrix3 GetTransposed3() const;


				// -------------------------------------------------------------------------------- //	
				// Arithmetic Operations on the Matrix
				// -------------------------------------------------------------------------------- //	

				/// <summary>
				/// Add another matrix to the current matrix.
				/// </summary>
				/// <param name="other">The matrix to add.</param>
				/// <returns>The resulting matrix after addition.</returns>
				Matrix3 AddMatrix3(const Matrix3& other) const;

				/// <summary>
				/// Multiply the matrix by a scalar value.
				/// </summary>
				/// <param name="n">The scalar value to multiply the matrix by.</param>
				/// <returns>The resulting matrix after multiplication.</returns>
				Matrix3 ProductScalar(float n) const;

				/// <summary>
				/// Multiply the matrix by another matrix.
				/// </summary>
				/// <param name="other">The matrix to multiply with.</param>
				/// <returns>The resulting matrix after multiplication.</returns>
				Matrix3 ProductMatrix3(const Matrix3& other) const;


				// -------------------------------------------------------------------------------- //	
				// Matrix Properties
				// -------------------------------------------------------------------------------- //	

				/// <summary>
				/// Return the trace of the matrix (sum of the diagonal elements).
				/// </summary>
				/// <returns>The trace of the matrix.</returns>
				float GetTrace() const;

				/// <summary>
				/// Return the determinant of the matrix.
				/// </summary>
				/// <returns>The determinant of the matrix.</returns>
				float GetDeterminant() const;

				/// <summary>
				/// Returns the inverse of the matrix if it exists.
				/// </summary>
				/// <returns>The inverse matrix, or an identity matrix if non-invertible.</returns>
				Matrix3 Inverse() const;

				/// <summary>
				/// Return a submatrix by excluding the specified row and column.
				/// </summary>
				/// <param name="excludeRow">Row to exclude (0-2).</param>
				/// <param name="excludeCol">Column to exclude (0-2).</param>
				/// <returns>The resulting submatrix after exclusion of the specified row and column.</returns>
				Matrix2 GetSubMatrix(int excludeRow, int excludeCol) const;


				// -------------------------------------------------------------------------------- //		
				// Lu Methode      
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Performs LU decomposition of the matrix.
				/// </summary>
				/// <returns>A matrix containing the upper triangular matrix (U), 
				/// with the lower triangular matrix (L) stored implicitly.</returns>
				Matrix3 luDecomposition() const;


				// -------------------------------------------------------------------------------- //		
				// Rotation matrix      
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Create an RST (Rotation - Scale - Transpose)
				/// Angle in rad.
				/// </summary>
				static Matrix3 RotateMatrix(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);

				/// <summary>
				/// Create an MatrixRotation axe X
				/// Angle in rad.
				/// </summary>
				static Matrix3 CreateXRotationMatrix(float angle);

				/// <summary>
				/// Create an MatrixRotation axe Y
				/// Angle in rad.
				/// </summary>
				static Matrix3 CreateYRotationMatrix(float angle);

				/// <summary>
				/// Create an MatrixRotation axe Z
				/// Angle in rad.
				/// </summary>
				static Matrix3 CreateZRotationMatrix(float angle);

				/// <summary>
				/// Create an MatrixRotation around a point
				/// </summary>
				static Matrix3 RotateMatrixVector(const Vector3& vec, float angle);


				// -------------------------------------------------------------------------------- //	
				// Display inline
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Prints all values of the Matrix3 to the console.
				/// </summary>
				void Print() const;


				// -------------------------------------------------------------------------------- //	
				// Overload operators inline
				// -------------------------------------------------------------------------------- //

				Matrix3 operator*(const Matrix3& other) const;
				Matrix3 operator/(const Matrix3& other)const;
				Matrix3 operator+(const Matrix3& other) const;
				Matrix3 operator-(const Matrix3& other) const;

				Matrix3& operator*=(const Matrix3& other);
				Matrix3& operator/=(const Matrix3& other);
				Matrix3& operator+=(const Matrix3& other);
				Matrix3& operator-=(const Matrix3& other);

				Matrix3 operator*(float n);
				Matrix3 operator*=(float n);
				Vector3 operator[](int index) const;
				Vector3& operator[](int index);
			};
		}
	}
}

#include "../Inline/Matrix3.inl"