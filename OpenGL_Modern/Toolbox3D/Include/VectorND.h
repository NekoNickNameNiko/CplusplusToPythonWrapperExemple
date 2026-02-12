#pragma once

#include "Vector4.h"
#include <vector>
#include <cstdarg>
namespace Bwt
{
	namespace Core
	{
		namespace Maths
		{
			class VectorND
			{
			public:
				std::vector<float> tab;
				int nValue;

				VectorND() = delete;
				inline VectorND(const VectorND& other) : tab(other.tab), nValue(other.nValue) {}
				VectorND(int count, ...);
				inline VectorND(int _nValue, std::vector<float> _M) : tab(_M), nValue(_nValue) {}
				~VectorND() = default;


				// -------------------------------------------------------------------------------- //	
				// Elementary operations on vector components
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Returns the opposite of the vector (negating its components).
				/// </summary>
				/// <returns>The opposed vector.</returns>
				VectorND GetOpposed() const;

				/// <summary>
				/// Adds the current vector with another vector.
				/// </summary>
				/// <param name="other">The vector to add.</param>
				/// <returns>The resulting vector after addition.</returns>
				VectorND AddVectorND(const VectorND& other) const;

				/// <summary>
				/// Addition of a scalar to each component
				/// </summary>
				/// <param name="scalar">The scalar to add.</param>
				/// <returns>The resulting vector after addition of the scalar.</returns>
				VectorND AddScalar(float scalar) const;

				/// <summary>
				/// Term product of two Vector
				/// </summary>
				/// <param name="other">The vector to Element Wise Product with.</param>
				/// <returns>The resulting vector after Element Wise Product.</returns>
				VectorND ElementWiseProduct(const VectorND& other) const;

				/// <summary>
				/// Multiply of a scalar to each component
				/// </summary>
				/// <param name="scalar">The scalar to Multiply.</param>
				/// <returns>The resulting vector after addition of the scalar.</returns>
				VectorND ProductScalar(float scalar) const;


				// -------------------------------------------------------------------------------- //	
				// Geometric & standard calculations
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Calculates the midpoint between the current vector and another vector.
				/// </summary>
				/// <param name="other">The other vector to find the midpoint with.</param>
				/// <returns>The midpoint vector.</returns>
				VectorND GetMid(const VectorND& other) const;

				/// <summary>
				/// Computes the distance between the current vector and another vector.
				/// </summary>
				/// <param name="other">The other vector to calculate the distance to.</param>
				/// <returns>The distance between the two vectors.</returns>
				float GetDistance(const VectorND& other) const;

				/// <summary>
				/// Computes the squared distance between the current vector and another vector, without calculating the square root (faster).
				/// </summary>
				/// <param name="other">The other vector to calculate the squared distance to.</param>
				/// <returns>The squared distance between the two vectors.</returns>
				float GetDistancePow(const VectorND& other) const;

				/// <summary>
				/// Returns the norm (magnitude) of the vector.
				/// </summary>
				/// <returns>The length of the vector.</returns>
				float GetNorm() const;

				/// <summary>
				/// Return the sum of the squares of its components.
				/// </summary>
				/// <returns>Return the Square of the vector.</returns>
				float GetSquareNorm() const;

				/// <summary>
				/// Returns the perspective-transformed value of the vector using the formula: (n1² +n2² + ...n² ) / t.
				/// </summary>
				/// <param name="t">The perspective parameter. Must be greater than 0.</param>
				/// <returns>The result of the perspective function, or 0 if t is less than or equal to 0.</returns>
				float GetPerspective(float t) const;


				// -------------------------------------------------------------------------------- //	
				// Products
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Computes the scalar (dot) product of the current vector and another vector.
				/// </summary>
				/// <param name="other">The other vector to compute the dot product with.</param>
				/// <returns>The scalar (dot) product of the two vectors.</returns>
				float DotProductVectorND(const VectorND& other) const;


				// -------------------------------------------------------------------------------- //	
				// Display
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Prints all values of the vector to the console.
				/// </summary>
				/// <param name="">None</param>
				/// <returns>None</returns>
				void Print() const;


				// -------------------------------------------------------------------------------- //	
				// Other
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Check if the vector contains a Zero.
				/// </summary>
				/// <param name="vec">The Vector need to be verified</param>
				/// <returns>Return true if it contains a 0 in the Vector</returns>
				bool ContainsZero(const std::vector<float>& vec);


				// -------------------------------------------------------------------------------- //	
				// Overload operators inline
				// -------------------------------------------------------------------------------- //

				inline VectorND operator+(const VectorND& vec)
				{
					return AddVectorND(vec);
				}
				inline VectorND operator-(const VectorND& vec)
				{
					return AddVectorND(GetOpposed());
				}
				inline VectorND operator*(const VectorND& vec)
				{
					return ElementWiseProduct(vec);
				}
				inline VectorND operator/(const VectorND& other)
				{
					assert(nValue == other.nValue && !ContainsZero(other.tab) && !ContainsZero(tab) && "Division by zero in VectorND");
					VectorND vec(nValue, tab);
					for (int i = 0; i < nValue; i++)
					{
						vec.tab[i] /= other.tab[i];
					}
					return vec;
				}
				inline VectorND& operator+=(const VectorND& other)
				{
					assert(nValue == other.nValue && "Size different VectorND");
					for (int i = 0; i < nValue; i++)
					{
						tab[i] += other.tab[i];
					}
					return *this;
				}
				inline VectorND& operator-=(const VectorND& other)
				{
					assert(nValue == other.nValue && "Size different VectorND");
					for (int i = 0; i < nValue; i++)
					{
						tab[i] -= other.tab[i];
					}
					return *this;
				}
				inline VectorND& operator*=(const VectorND& other)
				{
					assert(nValue == other.nValue && "Size different VectorND");
					for (int i = 0; i < nValue; i++)
					{
						tab[i] *= other.tab[i];
					}
					return *this;
				}
				inline VectorND& operator/=(const VectorND& other)
				{
					assert(nValue == other.nValue && !ContainsZero(other.tab) && "Division by zero in VectorND");
					for (int i = 0; i < nValue; i++)
					{
						tab[i] /= other.tab[i];
					}
					return *this;
				}
				inline float& operator[](int index)
				{
					assert(index >= 0 && index < nValue && "Index out of range in VectorND");
					return tab[index];
				}
				inline const float& operator[](int index) const
				{
					assert(index >= 0 && index < nValue && "Index out of range in VectorND");
					return tab[index];
				}
			};
		}
	}
}
