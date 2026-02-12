#pragma once

#include "VectorND.h"

namespace Bwt
{
	namespace Core
	{
		namespace Maths
		{
			class MatrixMxN
			{
			private:
				int column, row;
				std::vector<float> data;

			public:
				// -------------------------------------------------------------------------------- //
				// Constructors / Destructor
				// -------------------------------------------------------------------------------- //

				inline MatrixMxN(int  _row, int _column, float init = 0.0f)
					: row(_row), column(_column), data(_row* _column, init)
				{
				}
				inline MatrixMxN(const MatrixMxN& copy)
					: row(copy.row), column(copy.column), data(copy.data)
				{
				}
				inline MatrixMxN(int _ligne, int _colonne, std::vector<float>& _data)
					: row(_ligne), column(_colonne), data(_data) {
				}


				// -------------------------------------------------------------------------------- //
				// Basic Matrix Operations
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Returns the identity matrix of size MxN.
				/// </summary>
				void GetIdentity();

				/// <summary>
				/// Returns the diagonal elements of the matrix as a VectorND.
				/// </summary>
				/// <returns>A VectorND containing the diagonal elements.</returns>
				VectorND GetDiagonal() const;

				/// <summary>
				/// Sets the value of a specific element in the matrix.
				/// </summary>
				/// <param name="li">The row index.</param>
				/// <param name="col">The column index.</param>
				/// <param name="value">The new value for the element.</param>
				void SetValue(int li, int col, float value);

				/// <summary>
				/// Gets the value of a specific element in the matrix.
				/// </summary>
				/// <param name="li">The row index.</param>
				/// <param name="col">The column index.</param>
				/// <returns>The value of the specified element.</returns>
				float GetValue(int li, int col) const;

				/// <summary>
				/// Returns the trace of the matrix (sum of the diagonal elements).
				/// </summary>
				/// <returns>The trace of the matrix.</returns>
				float GetTrace() const;

				/// <summary>
				/// Returns the opposed (negated) matrix.
				/// </summary>
				/// <returns>The opposed matrix.</returns>
				MatrixMxN GetOpposed() const;

				/// <summary>
				/// Returns the transposed matrix.
				/// </summary>
				/// <returns>The transposed matrix.</returns>
				MatrixMxN GetTransposed() const;


				// -------------------------------------------------------------------------------- //
				// Arithmetic Operations on the Matrix
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Adds another matrix to the current matrix.
				/// </summary>
				/// <param name="other">The matrix to add.</param>
				/// <returns>The resulting matrix after addition.</returns>
				MatrixMxN AddMatrix(const MatrixMxN& other) const;

				/// <summary>
				/// Multiplies the matrix by a scalar value.
				/// </summary>
				/// <param name="n">The scalar value to multiply the matrix by.</param>
				/// <returns>The resulting matrix after multiplication.</returns>
				MatrixMxN ProductScalar(float n);

				/// <summary>
				/// Multiplies the matrix by another matrix.
				/// </summary>
				/// <param name="other">The matrix to multiply with.</param>
				/// <returns>The resulting matrix after multiplication.</returns>
				MatrixMxN ProductMatrix(const MatrixMxN& other) const;

				/// <summary>
				/// Returns a submatrix by excluding the specified row and column.
				/// </summary>
				/// <param name="excludeRow">The row to exclude.</param>
				/// <param name="excludeCol">The column to exclude.</param>
				/// <returns>The resulting submatrix after exclusion of the specified row and column.</returns>
				MatrixMxN GetSubMatrix(int excludeRow, int excludeCol) const;


				// -------------------------------------------------------------------------------- //
				// Matrix Properties
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Returns the determinant of the matrix.
				/// </summary>
				/// <returns>The determinant of the matrix.</returns>
				float GetDeterminant() const;

				/// <summary>
				/// Merges the current matrix with another matrix.
				/// </summary>
				/// <param name="other">The matrix to merge with.</param>
				/// <returns>The resulting merged matrix.</returns>
				MatrixMxN FusionMatrix(const MatrixMxN& other) const;

				/// <summary>
				/// Extends the matrix by adding extra rows and columns.
				/// </summary>
				/// <param name="n">The number of rows and columns to add.</param>
				/// <returns>The extended matrix.</returns>
				MatrixMxN ExtendMatrix(int n) const;

				/// <summary>
				/// Returns the cofactor matrix of the current matrix.
				/// </summary>
				/// <returns>The cofactor matrix.</returns>
				MatrixMxN GetCofactorMatrix() const;

				/// <summary>
				/// Returns the inverse of the matrix.
				/// </summary>
				/// <returns>The inverse matrix, or an identity matrix if non-invertible.</returns>
				MatrixMxN Inverse() const;


				// -------------------------------------------------------------------------------- //	
				// Display
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Prints the matrix to the console.
				/// </summary>
				void Print() const;
			};
		}
	}
}
