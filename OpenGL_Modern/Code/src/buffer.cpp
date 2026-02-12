#include "buffer.h"

#include <glad.h>

namespace Bwt
{
	namespace Core
	{
		VBO::VBO(float* vertices, unsigned long long size)
		{
			glCreateBuffers(1, &id);
			glBindBuffer(GL_ARRAY_BUFFER, id);
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		}

		VBO::~VBO()
		{
			glDeleteBuffers(1, &id);
		}

		void VBO::Bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, id);
		}

		void VBO::UnBind()const
		{
			glBindBuffer(GL_ARRAY_BUFFER,0);
		}
		EBO::EBO(unsigned int* indices, unsigned long long size)
		{
			glCreateBuffers(1, &id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
		}

		EBO::~EBO()
		{
			glDeleteBuffers(1, &id);
		}

		void EBO::Bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		}
		
		void EBO::UnBind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		VAO::VAO()
		{
			glCreateVertexArrays(1, &id);
		}

		VAO::~VAO()
		{
			glDeleteVertexArrays(1, &id);
		}

		void VAO::Bind() const
		{
			glBindVertexArray(id);
		}

		void VAO::UnBind()
		{
			glBindVertexArray(0);
		}

		void VAO::AddAttribute(VBO& vbo, unsigned int layout, int size, int type,  int stride,unsigned long long pointer)
		{
			vbo.Bind();
			glVertexAttribPointer(layout, size, type, GL_FALSE, stride, (void*) pointer);
			glEnableVertexAttribArray(layout);
			vbo.UnBind();
		}
	}
}