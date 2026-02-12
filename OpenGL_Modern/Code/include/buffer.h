#pragma once

namespace Bwt
{
	namespace Core
	{
		class VBO
		{
		private:

			unsigned int id;

		public:

			VBO(float* vertices, unsigned long long size);
			~VBO();

			void Bind() const;
			void UnBind() const;
		};

		class EBO
		{
		private:

			unsigned int id;

		public:

			EBO(unsigned int* indices, unsigned long long size);
			~EBO();

			void Bind() const;
			void UnBind() const;
		};

		class VAO
		{
		private:

			unsigned int id;

		public:

			VAO();
			~VAO();

			void Bind() const;
			void UnBind();

			void AddAttribute(VBO& vbo, unsigned int layout, int size, int type, int stride, unsigned long long pointer);
		};
	}
}