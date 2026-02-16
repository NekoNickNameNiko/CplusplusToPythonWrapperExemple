#pragma once

#include "../../Toolbox3D/Include/Vector4.h"
#include "../../Toolbox3D/Include/Matrix4.h"
#include "../../Code/include/transform.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

using namespace Bwt::Core::Maths;

namespace Bwt
{
	namespace LowRenderer
	{
		class Camera
		{
		private:

			Matrix4 viewMatrix;
			Matrix4 projection;
			Matrix4 vpMatrix;

			void SoftUpdate();

		public:

			Bwt::Physics::Transform transform;
			Bwt::Core::Maths::Vector3 center = { 0.f, 0.f, 0.f };

			float speed = 0.1f;
			float speedRotation = 0.1f;

			Camera();
			Camera(Bwt::Core::Maths::Vector3 position, Matrix4 projection);
			~Camera();

			void Update();
			void SetProjectionMatrix(const Matrix4& proj);
			Matrix4 GetVPMatrix(bool b);
			void Move(Bwt::Core::Maths::Vector3 motion);
			void Rotate(const Bwt::Core::Maths::Vector3& rotation);

			Matrix4 LookAt(const Bwt::Core::Maths::Vector3& eye, 
				const Bwt::Core::Maths::Vector3& center, const Bwt::Core::Maths::Vector3& Up);

		};
	}
}