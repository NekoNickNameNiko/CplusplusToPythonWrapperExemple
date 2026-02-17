#pragma once

#include <cassert>
#include "Vector3.h"
namespace Bwt
{
	namespace Core
	{
		namespace Maths
		{
			class Vector4
			{
			public:
				float x;
				float y;
				float z;
				float w;

				inline Vector4(Vector3 vec3, float _w = 1.f)
					: x(vec3.x), y(vec3.y), z(vec3.z), w(_w) {
				}
				inline Vector4(float _x = 0.f, float _y = 0.f, float _z = 0.f, float _w = 1.f)
					: x(_x), y(_y), z(_z), w(_w) {
				}
				~Vector4() = default;

				// -------------------------------------------------------------------------------- //	
				// Elementary operations on vector components
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Returns the opposite of the vector (negating its components).
				/// </summary>
				/// <returns>The opposed vector.</returns>
				Vector4 GetOpposed() const;

				/// <summary>
				/// Adds the current vector with another vector.
				/// </summary>
				/// <param name="other">The vector to add.</param>
				/// <returns>The resulting vector after addition.</returns>
				Vector4 AddVector4(const Vector4& other) const;

				/// <summary>
				/// Addition of a scalar to each component
				/// </summary>
				/// <param name="scalar">The scalar to add.</param>
				/// <returns>The resulting vector after addition of the scalar.</returns>
				Vector4 AddScalar(float scalar) const;

				/// <summary>
				/// Term product of two Vector
				/// </summary>
				/// <param name="other">The vector to Element Wise Product with.</param>
				/// <returns>The resulting vector after Element Wise Product.</returns>
				Vector4 ElementWiseProduct(const Vector4& other) const;

				/// <summary>
				/// Multiply of a scalar to each component
				/// </summary>
				/// <param name="scalar">The scalar to Multiply.</param>
				/// <returns>The resulting vector after addition of the scalar.</returns>
				Vector4 ProductScalar(float scalar) const;


				// -------------------------------------------------------------------------------- //	
				// Geometric & standard calculations
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Calculates the midpoint between the current vector and another vector.
				/// </summary>
				/// <param name="other">The other vector to find the midpoint with.</param>
				/// <returns>The midpoint vector.</returns>
				Vector4 GetMid(const Vector4& other) const;

				/// <summary>
				/// Computes the distance between the current vector and another vector.
				/// </summary>
				/// <param name="other">The other vector to calculate the distance to.</param>
				/// <returns>The distance between the two vectors.</returns>
				float GetDistance(const Vector4& other) const;

				/// <summary>
				/// Computes the squared distance between the current vector and another vector, without calculating the square root (faster).
				/// </summary>
				/// <param name="other">The other vector to calculate the squared distance to.</param>
				/// <returns>The squared distance between the two vectors.</returns>
				float GetDistancePow(const Vector4& other) const;

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
				/// Returns a normalized version of the vector (unit vector).
				/// </summary>
				/// <returns>A new Vector4 with the same direction but a magnitude of 1.</returns>
				Vector4 Normalized() const;

				/// <summary>
				/// Returns the perspective-transformed value of the vector using the formula: (x² + y² + z² + w²) / t.
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
				float DotProductVector4(const Vector4& other) const;


				// -------------------------------------------------------------------------------- //	
				// Display
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Prints all values of the vector (x, y, z, w) to the console.
				/// </summary>
				/// <param name="">None</param>
				/// <returns>None</returns>
				inline void Print() const
				{
					std::cout << "x : " << x << " y : " << y << " z : " << z << " w : " << w << "\n";
				}


				// -------------------------------------------------------------------------------- //	
				// Overload operators inline
				// -------------------------------------------------------------------------------- //

				inline Vector4 operator+(const Vector4& vec)
				{
					return AddVector4(vec);
				}
				inline Vector4 operator-(const Vector4& vec)
				{
					return AddVector4(GetOpposed());
				}
				Vector4 operator*(const Vector4& vec);
				inline Vector4 operator/(const Vector4& vec)
				{
					assert(vec.x != 0 && vec.y != 0 && vec.z != 0 && vec.w != 0 && "Division by zero in Vector4D");
					return Vector4(x / vec.x, y / vec.y, z / vec.z, w / vec.w);
				}
				inline Vector4& operator+=(const Vector4& vec)
				{
					x += vec.x;
					y += vec.y;
					z += vec.z;
					w += vec.w;
					return *this;
				}
				inline Vector4& operator-=(const Vector4& vec)
				{
					x -= vec.x;
					y -= vec.y;
					z -= vec.z;
					w -= vec.w;
					return *this;
				}
				inline Vector4& operator*=(const Vector4& vec)
				{
					x *= vec.x;
					y *= vec.y;
					z *= vec.z;
					w *= vec.w;
					return *this;
				}
				inline Vector4& operator/=(const Vector4& vec)
				{
					assert(vec.x != 0 && vec.y != 0 && vec.z != 0 && vec.w != 0 && "Division by zero in Vector4D");
					x /= vec.x;
					y /= vec.y;
					z /= vec.z;
					w /= vec.w;
					return *this;
				}

				inline operator Vector3() const
				{
					return Vector3(x, y, z);
				}

				inline float& operator[](int index)
				{
					assert(index >= 0 && index < 4 && "Index out of range in Vector4D");
					return (index == 0) ? x : (index == 1) ? y : (index == 2) ? z : w;
				}
				inline const float& operator[](int index) const
				{
					assert(index >= 0 && index < 4 && "Index out of range in Vector4D");
					return (index == 0) ? x : (index == 1) ? y : (index == 2) ? z : w;
				}

				std::array<float, 4> AsList() const;
			};
		}
	}
}
