#pragma once

#include <cmath>
#include <iostream>
#include <cassert>
#include <immintrin.h>

#define PI 3.14159265359f

inline float ToRad(float angle)
{
	return angle * PI / 180.f;
}

namespace Bwt
{
	namespace Core
	{
		namespace Maths
		{
			class Vector2
			{
			public:
				// -------------------------------------------------------------------------------- //	
				// Constructor & variables
				// -------------------------------------------------------------------------------- //

				float x;
				float y;

				inline Vector2(float _x = 0, float _y = 0)
					: x(_x), y(_y) {
				}
				~Vector2() = default;


				// -------------------------------------------------------------------------------- //	
				// Elementary operations on vector components
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Returns the opposite of the vector (negating its components).
				/// </summary>
				/// <returns>The opposed vector.</returns>
				Vector2 GetOpposed() const;

				/// <summary>
				/// Adds the current vector with another vector.
				/// </summary>
				/// <param name="other">The vector to add.</param>
				/// <returns>The resulting vector after addition.</returns>
				Vector2 AddVector2(const Vector2& other) const;

				/// <summary>
				/// Addition of a scalar to each component
				/// </summary>
				/// <param name="scalar">The scalar to add.</param>
				/// <returns>The resulting vector after addition of the scalar.</returns>
				Vector2 AddScalar(float scalar) const;

				/// <summary>
				/// Term product of two Vector
				/// </summary>
				/// <param name="other">The vector to Element Wise Product with.</param>
				/// <returns>The resulting vector after Element Wise Product.</returns>
				Vector2 ElementWiseProduct(const Vector2& other) const;

				/// <summary>
				/// Multiply of a scalar to each component
				/// </summary>
				/// <param name="scalar">The scalar to Multiply.</param>
				/// <returns>The resulting vector after addition of the scalar.</returns>
				Vector2 ProductScalar(float scalar) const;


				// -------------------------------------------------------------------------------- //	
				// Geometric & standard calculations
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Calculates the midpoint between the current vector and another vector.
				/// </summary>
				/// <param name="other">The other vector to find the midpoint with.</param>
				/// <returns>The midpoint vector.</returns>
				Vector2 GetMid(const Vector2& other) const;

				/// <summary>
				/// Computes the distance between the current vector and another vector.
				/// </summary>
				/// <param name="other">The other vector to calculate the distance to.</param>
				/// <returns>The distance between the two vectors.</returns>
				float GetDistance(const Vector2& other) const;

				/// <summary>
				/// Computes the squared distance between the current vector and another vector, without calculating the square root (faster).
				/// </summary>
				/// <param name="other">The other vector to calculate the squared distance to.</param>
				/// <returns>The squared distance between the two vectors.</returns>
				float GetDistancePow(const Vector2& other) const;

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
				/// <returns>A new Vector2 with the same direction but a magnitude of 1.</returns>
				Vector2 Normalized() const;

				/// <summary>
				/// Returns the perspective-transformed value of the vector using the formula: (x² + y²) / t.
				/// </summary>
				/// <param name="t">The perspective parameter. Must be greater than 0.</param>
				/// <returns>The result of the perspective function, or 0 if t is less than or equal to 0.</returns>
				float GetPerspective(float t) const;


				// -------------------------------------------------------------------------------- //	
				// Products & angles
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Computes the scalar (dot) product of the current vector and another vector.
				/// </summary>
				/// <param name="other">The other vector to compute the dot product with.</param>
				/// <returns>The scalar (dot) product of the two vectors.</returns>
				float DotProductVector2(const Vector2& other) const;

				/// <summary>
				/// Computes the 2D cross product between the current vector and another vector.
				/// </summary>
				/// <param name="other">The other vector to compute the cross product with.</param>
				/// <returns>The scalar result of the 2D cross product.</returns>
				float CrossProductVector2(const Vector2& other) const;

				/// <summary>
				/// Calculates the angle (in degrees) between the current vector and another vector.
				/// </summary>
				/// <param name="v2">The other vector to calculate the angle with.</param>
				/// <returns>The angle in degrees between the two vectors.</returns>
				float GetAngle(const Vector2& v2) const;


				// -------------------------------------------------------------------------------- //	
				// Transform
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Rotates the vector by the specified angle (in degrees).
				/// </summary>
				/// <param name="angle">The angle in degrees to rotate the vector.</param>
				/// <returns>None</returns>
				void Rotation(float angle);


				// -------------------------------------------------------------------------------- //	
				// Display
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Prints all values of the vector (x, y) to the console.
				/// </summary>
				/// <param name="">None</param>
				/// <returns>None</returns>
				inline void Print() const
				{
					std::cout << "x : " << x << " y : " << y << "\n";
				}


				// -------------------------------------------------------------------------------- //	
				// Overload operators inline
				// -------------------------------------------------------------------------------- //


				inline Vector2 operator+(const Vector2& vec)
				{
					return AddVector2(vec);
				}
				inline Vector2 operator-(const Vector2& vec)
				{
					return AddVector2(GetOpposed());
				}
				inline Vector2 operator*(const Vector2& vec)
				{
					return ElementWiseProduct(vec);
				}
				inline Vector2 operator/(const Vector2& vec)
				{
					assert(vec.x != 0 && vec.y != 0 && "Division by zero in Vector2D");
					return Vector2(x / vec.x, y / vec.y);
				}
				inline Vector2& operator+=(const Vector2& vec)
				{
					x += vec.x;
					y += vec.y;
					return *this;
				}
				inline Vector2& operator-=(const Vector2& vec)
				{
					x -= vec.x;
					y -= vec.y;
					return *this;
				}
				inline Vector2& operator*=(const Vector2& vec)
				{
					x *= vec.x;
					y *= vec.y;
					return *this;
				}
				inline Vector2& operator/=(const Vector2& vec)
				{
					x /= vec.x;
					y /= vec.y;
					return *this;
				}
				inline float& operator[](int index)
				{
					assert(index >= 0 && index < 2 && "Index out of range in Vector2D");
					return (index == 0) ? x : y;
				}
				inline const float& operator[](int index) const
				{
					assert(index >= 0 && index < 2 && "Index out of range in Vector2D");
					return (index == 0) ? x : y;
				}
			};
		}
	}
}
