#pragma once

#include "Vector2.h"
#include <cmath>

#include <ostream>

namespace Bwt
{
	namespace Core
	{
		namespace Maths
		{
			class Vector3
			{
			public:
				// -------------------------------------------------------------------------------- //	
				// Constructor & variables
				// -------------------------------------------------------------------------------- //

				float x{ 0 };
				float y{ 0 };
				float z{ 0 };

				Vector3() = default;
				inline Vector3(Vector2 vec2, float _z)
					: x(vec2.x), y(vec2.y), z(_z) {
				}
				inline Vector3(float _x, float _y, float _z)
					: x(_x), y(_y), z(_z) {
				}
				~Vector3() = default;


				// -------------------------------------------------------------------------------- //	
				// Elementary operations on vector components
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Returns the opposite of the vector (negating its components).
				/// </summary>
				/// <returns>The opposed vector.</returns>
				Vector3 GetOpposed() const;

				/// <summary>
				/// Adds the current vector with another vector.
				/// </summary>
				/// <param name="other">The vector to add.</param>
				/// <returns>The resulting vector after addition.</returns>
				Vector3 AddVector3(const Vector3& other) const;

				/// <summary>
				/// Addition of a scalar to each component
				/// </summary>
				/// <param name="scalar">The scalar to add.</param>
				/// <returns>The resulting vector after addition of the scalar.</returns>
				Vector3 AddScalar(float scalar) const;

				/// <summary>
				/// Term product of two Vector
				/// </summary>
				/// <param name="other">The vector to Element Wise Product with.</param>
				/// <returns>The resulting vector after Element Wise Product.</returns>
				Vector3 ElementWiseProduct(const Vector3& other) const;

				/// <summary>
				/// Multiply of a scalar to each component
				/// </summary>
				/// <param name="scalar">The scalar to Multiply.</param>
				/// <returns>The resulting vector after addition of the scalar.</returns>
				Vector3 ProductScalar(float scalar) const;


				// -------------------------------------------------------------------------------- //	
				// Geometric & standard calculations
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Calculates the midpoint between the current vector and another vector.
				/// </summary>
				/// <param name="other">The other vector to find the midpoint with.</param>
				/// <returns>The midpoint vector.</returns>
				Vector3 GetMid(const Vector3& other) const;

				/// <summary>
				/// Computes the distance between the current vector and another vector.
				/// </summary>
				/// <param name="other">The other vector to calculate the distance to.</param>
				/// <returns>The distance between the two vectors.</returns>
				float GetDistance(const Vector3& other) const;

				/// <summary>
				/// Computes the squared distance between the current vector and another vector, without calculating the square root (faster).
				/// </summary>
				/// <param name="other">The other vector to calculate the squared distance to.</param>
				/// <returns>The squared distance between the two vectors.</returns>
				float GetDistancePow(const Vector3& other) const;

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
				/// <returns>A new Vector3 with the same direction but a magnitude of 1.</returns>
				Vector3 Normalized() const;

				/// <summary>
				/// Returns the perspective-transformed value of the vector using the formula: (x² + y² + z²) / t.
				/// </summary>
				/// <param name="t">The perspective parameter. Must be greater than 0.</param>
				/// <returns>The result of the perspective function, or 0 if t is less than or equal to 0.</returns>
				float GetPerspective(float t) const;

				/// <summary>
				/// Return the Reflected Vector.
				/// </summary>
				/// <param name="I">vecteur incident</param>
				/// <param name="N">Surface Normal</param>
				/// <returns>The result of the perspective function, or 0 if t is less than or equal to 0.</returns>
				static Vector3 Reflect(Vector3 I, Vector3 N);

				// -------------------------------------------------------------------------------- //	
				// Products & angles
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Computes the scalar (dot) product of the current vector and another vector.
				/// </summary>
				/// <param name="other">The other vector to compute the dot product with.</param>
				/// <returns>The scalar (dot) product of the two vectors.</returns>
				float DotProductVector3(const Vector3& other) const;

				/// <summary>
				/// Computes the 3D cross product between the current vector and another vector.
				/// </summary>
				/// <param name="other">The other vector to compute the cross product with.</param>
				/// <returns>The scalar result of the 3D cross product.</returns>
				Vector3 CrossProductVector3(const Vector3& other) const;

				/// <summary>
				/// Calculates the angle (in degrees) between the current vector and another vector.
				/// </summary>
				/// <param name="v2">The other vector to calculate the angle with.</param>
				/// <returns>The angle in degrees between the two vectors.</returns>
				float GetAngle(const Vector3& v2) const;


				// -------------------------------------------------------------------------------- //	
				// Transform
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Rotates the vector by the specified angle (in degrees).
				/// </summary>
				/// <param name="angleX">The angle X in degrees to rotate the vector.</param>
				/// <param name="angleY">The angle Y in degrees to rotate the vector.</param>
				/// <param name="angleZ">The angle Z in degrees to rotate the vector.</param>
				/// <returns>None</returns>
				void Rotation(float angleX, float angleY, float angleZ);


				// -------------------------------------------------------------------------------- //	
				// Display
				// -------------------------------------------------------------------------------- //

				/// <summary>
				/// Prints all values of the vector (x, y, z) to the console.
				/// </summary>
				/// <param name="">None</param>
				/// <returns>None</returns>
				inline void Print() const
				{
					std::cout << "x : " << x << " y : " << y << " z : " << z << "\n";
				}

				std::array<float, 3> AsList() const;

				// -------------------------------------------------------------------------------- //	
				// Overload operators inline
				// -------------------------------------------------------------------------------- //

				inline Vector3 operator+(const Vector3& vec)
				{
					return AddVector3(vec);
				}
				inline Vector3 operator-(const Vector3& vec)
				{
					return AddVector3(GetOpposed());
				}
				inline Vector3 operator*(const Vector3& vec)
				{
					return ElementWiseProduct(vec);
				}
				inline Vector3 operator/(const Vector3& vec)
				{
					assert(vec.x != 0 && vec.y != 0 && vec.z != 0 && "Division by zero in Vector3D");
					return Vector3(x / vec.x, y / vec.y, z / vec.z);
				}
				inline Vector3& operator+=(const Vector3& vec)
				{
					x += vec.x;
					y += vec.y;
					z += vec.z;
					return *this;
				}
				inline Vector3& operator-=(const Vector3& vec)
				{
					x -= vec.x;
					y -= vec.y;
					z -= vec.z;
					return *this;
				}
				inline Vector3& operator*=(const Vector3& vec)
				{
					x *= vec.x;
					y *= vec.y;
					z *= vec.z;
					return *this;
				}
				inline Vector3& operator/=(const Vector3& vec)
				{
					assert(vec.x != 0 && vec.y != 0 && vec.z != 0 && "Division by zero in Vector3D");
					x /= vec.x;
					y /= vec.y;
					z /= vec.z;
					return *this;
				}

				inline Vector3 operator*(float scalar)
				{
					return Vector3(x * scalar, y * scalar, z * scalar);
				}

				inline Vector3 operator-() const
				{
					return Vector3{ -x, -y, -z };
				}

				inline float& operator[](int index)
				{
					assert(index >= 0 && index < 3 && "Index out of range in Vector3D");
					return (index == 0) ? x : (index == 1) ? y : z;
				}
				inline const float& operator[](int index) const
				{
					assert(index >= 0 && index < 3 && "Index out of range in Vector3D");
					return (index == 0) ? x : (index == 1) ? y : z;
				}
			};

			std::ostream& operator<<(std::ostream& os, const Vector3& vec);
		}
	}
}
