#include "../Include/MatrixMxN.h"

using namespace Bwt::Core::Maths;
void MatrixMxN::GetIdentity()
{
	for (int i = 0; i < row; i++)
	{
		if (i + i * row > row * column) break;
		data[i + i * row] = 1;
	}
}
VectorND MatrixMxN::GetDiagonal() const
{
	std::vector<float> list;
	list.reserve(row * column);
	for (int i = 0; i < row; i++)
	{
		if (i + i * row > row * column) break;
		list.push_back(data[i + i * row]);
	}
	return VectorND((int)list.size(), list);
}
void MatrixMxN::SetValue(int li, int col, float value)
{
	if (li < row && li > 0 && col > 0 && col < column)
	{
		data[li + col * row] = value;
		return;
	}
	else
	{
		std::cout << "Set value out of matrix" << std::endl;
		return;
	}
}
float MatrixMxN::GetValue(int li, int col) const
{
	if (li <= row && li >= 0 && col >= 0 && col <= column)
	{
		return data[li + col * row];
	}
	else
	{
		std::cout << "Set value out of matrix" << std::endl;
		return 0.f;
	}
}
void MatrixMxN::Print() const
{
	for (int col = 0; col < column; col++)
	{
		for (int li = 0; li < row; li++)
		{
			std::cout << data[li + col * row] << " ";
		}
		std::cout << std::endl;
	}
}
float MatrixMxN::GetTrace() const
{
	VectorND vecND = GetDiagonal();
	float somme = 0;
	for (float n : vecND.tab)
	{
		somme += n;
	}
	return somme;
}
MatrixMxN MatrixMxN::GetOpposed() const
{
	std::vector<float> list;
	list.reserve(row * column);
	for (int c = 0; c < column; c++)
	{
		for (int l = 0; l < row; l++)
		{
			list.push_back(-data[l + c * row]);
		}
	}
	return MatrixMxN(column, row, list);
}
MatrixMxN MatrixMxN::GetTransposed() const
{
	std::vector<float> list;
	list.reserve(row * column);
	for (int l = 0; l < row; l++)
	{
		for (int c = 0; c < column; c++)
		{
			list.push_back(data[c + l * column]);
		}
	}
	return MatrixMxN(row, column, list);
}
MatrixMxN MatrixMxN::AddMatrix(const MatrixMxN& other) const
{
	assert(other.row == row && other.column == column && "Not Same Dimension");
	std::vector<float> list;
	list.reserve(row * column);
	for (int c = 0; c < column; c++)
	{
		for (int l = 0; l < row; l++)
		{
			list.push_back(data[l + c * row] + other.data[l + c * row]);
		}
	}
	return MatrixMxN(column, row, list);
}
MatrixMxN MatrixMxN::ProductScalar(float n)
{
	std::vector<float> list;
	list.reserve(row * column);
	for (int i = 0 ; i < row * column; i++)
	{
		list[i] = data[i] * n;
	}
	return MatrixMxN(row, column, list);
}
MatrixMxN MatrixMxN::ProductMatrix(const MatrixMxN& other) const
{
	assert(other.row == row && other.column == column && "Not Same Dimension");
	std::vector<float> list;
	list.reserve(row * column);
	for (int c = 0; c < column; c++)
	{
		for (int l = 0; l < row; l++)
		{
			list.push_back(data[l + c * row] * other.data[l + c * row]);
		}
	}
	return MatrixMxN(row, column, list);
}
MatrixMxN MatrixMxN::GetSubMatrix(int excludeRow, int excludeCol) const
{
	assert(row == column && "Matrix must be square");
	std::vector<float> subMatrix;
	subMatrix.reserve((row - 1) * (column - 1));
	for (int i = 0; i < row; ++i)
	{
		if (i == excludeRow) continue;

		for (int j = 0; j < column; ++j)
		{
			if (j == excludeCol) continue;

			subMatrix.push_back(GetValue(i, j));
		}
	}
	return MatrixMxN(row - 1, column - 1, subMatrix);
}
float MatrixMxN::GetDeterminant() const
{
	assert(row == column && "Matrix must be square");

	if (row == 1) return data[0];
	if (row == 2)
		return data[0] * data[3] - data[1] * data[2];

	float det = 0.0f;
	for (int col = 0; col < column; ++col)
	{
		float sign = (col % 2 == 0) ? 1.0f : -1.0f;
		MatrixMxN subMatrix = GetSubMatrix(0, col);
		det += sign * GetValue(0, col) * subMatrix.GetDeterminant();
	}
	return det;
}
MatrixMxN MatrixMxN::FusionMatrix(const MatrixMxN& other) const
{
	assert(column == other.column && "Matrix have not same size col");
	std::vector<float> fusionMatrix;
	fusionMatrix.reserve((row + other.row) * column);
	for (int c = 0; c < column; c++)
	{
		for (int l = 0; l < row; l++)
		{
			fusionMatrix.push_back(data[l + c * row]);
		}
		for (int l = 0; l < other.row; l++)
		{
			fusionMatrix.push_back(other.data[l + c * other.row]);
		}
	}
	return MatrixMxN(row + other.row, column, fusionMatrix);
}
MatrixMxN MatrixMxN::ExtendMatrix(int n) const
{
	MatrixMxN extendedMatrix(n, column);
	return FusionMatrix(extendedMatrix);
}
MatrixMxN MatrixMxN::GetCofactorMatrix() const
{
	assert(row == column && "Matrix must be square");
	std::vector<float> cofactors;
	cofactors.reserve(row * column);
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < column; ++j)
		{
			MatrixMxN subMatrix = GetSubMatrix(i, j);
			float sign = ((i + j) % 2 == 0) ? 1.0f : -1.0f;
			cofactors.push_back(sign * subMatrix.GetDeterminant());
		}
	}

	return MatrixMxN(row, column, cofactors);
}

MatrixMxN MatrixMxN::Inverse() const
{
	float det = GetDeterminant();
	assert(det != 0.0f && "Matrix is not invertible");

	MatrixMxN cofactors = GetCofactorMatrix();
	MatrixMxN adjoint = cofactors.GetTransposed();

	std::vector<float> inverseMatrix;
	inverseMatrix.reserve(row * column);

	for (float val : adjoint.data)
	{
		inverseMatrix.push_back(val / det);
	}

	return MatrixMxN(row, column, inverseMatrix);
}