#pragma once

#include "Vector4.h"

namespace Bwt
{
	namespace Core
	{
		namespace Maths
		{
			// Setting for different constructor
			struct FillAll_t {};
			constexpr FillAll_t FillAll{};

			class Matrix2
			{
			public:
				float tab[4];

				Matrix2(FillAll_t, float init);
				Matrix2(const Matrix2& copy);
				Matrix2(float m0 = 0.f, float m1 = 0.f, float m2 = 0.f, float m3 = 0.f) : tab{ m0, m2, m1, m3 } {}

				/// <summary>
				/// Return the identity matrix of 2x2.
				/// </summary>
				/// <returns>The identity matrix.</returns>
				static Matrix2 GetIdentity2();

				// -------------------------------------------------------------------------------- //	
				// Basic matrix operations
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Return the diagonal elements of the matrix as a Vector2.
				/// </summary>
				/// <returns>A Vector2 containing the diagonal elements.</returns>
				Vector2 GetDiagonal() const;

				/// <summary>
				/// Return the opposed (negated) matrix.
				/// </summary>
				/// <returns>The opposed matrix.</returns>
				Matrix2 GetOpposed2() const;

				/// <summary>
				/// Return the transposed matrix.
				/// </summary>
				/// <returns>The transposed matrix.</returns>
				Matrix2 GetTransposed2() const;


				// -------------------------------------------------------------------------------- //	
				// Arithmetic operations on the matrix
				// -------------------------------------------------------------------------------- //	

				/// <summary>
				/// Add another matrix to the current matrix.
				/// </summary>
				/// <param name="other">The matrix to add.</param>
				/// <returns>The resulting matrix after addition.</returns>
				Matrix2 AddMatrix2(const Matrix2& other) const;

				/// <summary>
				/// Multiply the matrix by a scalar value.
				/// </summary>
				/// <param name="n">The scalar value to multiply the matrix by.</param>
				/// <returns>The resulting matrix after multiplication.</returns>
				Matrix2 ProductScalar(float n) const;

				/// <summary>
				/// Multiply the matrix by another matrix.
				/// </summary>
				/// <param name="other">The matrix to multiply with.</param>
				/// <returns>The resulting matrix after multiplication.</returns>
				Matrix2 ProductMatrix2(const Matrix2& other) const;


				// -------------------------------------------------------------------------------- //	
				// Matrix properties
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
				/// Return the inverse of the matrix.
				/// </summary>
				/// <returns>The inverse matrix, or an Null matrix if non-invertible.</returns>
				Matrix2 Inverse() const;


				// -------------------------------------------------------------------------------- //	
				// Rotation matrix
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Rotate the matrix by a given angle (in Radian).
				/// </summary>
				/// <param name="angle">The angle by which to rotate the matrix.</param>
				/// <returns>The resulting rotated matrix.</returns>
				Matrix2 Rotation(float angle);

				// -------------------------------------------------------------------------------- //	
				// Display
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Prints all values of the Matrix2 to the console.
				/// </summary>
				void Print() const;


				// -------------------------------------------------------------------------------- //	
				// Overload operators inline
				// -------------------------------------------------------------------------------- //

				Matrix2 operator*(const Matrix2& other)const;
				Matrix2 operator/(const Matrix2& other)const;
				Matrix2 operator+(const Matrix2& other) const;
				Matrix2 operator-(const Matrix2& other) const;

				Matrix2& operator*=(const Matrix2& other);
				Matrix2& operator/=(const Matrix2& other);
				Matrix2& operator+=(const Matrix2& other);
				Matrix2& operator-=(const Matrix2& other);

				Matrix2 operator*(float other) const;
				Matrix2& operator*=(float other);
			};
		}
	}
}

#include "../Inline/Matrix2.inl"