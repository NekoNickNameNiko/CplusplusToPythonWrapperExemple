#pragma once
#include "../../Toolbox3D/Include/Matrix4.h"

using namespace Bwt::Core::Maths;

namespace Bwt
{
	namespace Physics
	{
		class Transform
		{
		public:
			Bwt::Core::Maths::Vector3 position;
			Bwt::Core::Maths::Vector3 rotation;
			Bwt::Core::Maths::Vector3 scale;

			Bwt::Core::Maths::Vector3 forward;
			Bwt::Core::Maths::Vector3 right;
			Bwt::Core::Maths::Vector3 up;

			Transform(Bwt::Core::Maths::Vector3 position);

			Bwt::Core::Maths::Matrix4 modelMatrix;

			Matrix4 GetTransformMatrix() const;

			void Rotate(const Bwt::Core::Maths::Vector3& rotationAxis);
			void Move(const Bwt::Core::Maths::Vector3& motion);
		};
	}
}