#pragma once

#include "Interface.h"

#include <glad.h>
#include <filesystem>

namespace Bwt
{
	namespace Resources
	{
		struct TextureParams
		{
			std::string m_filepath;
			int width = 0, height = 0, component = 0;
			GLuint m_textureID = 0;

			GLint level = 0;
			GLenum format = GL_RGBA;
			GLenum type = GL_UNSIGNED_BYTE;
			bool useMipMaps = false;
			GLuint textureUnit = 0;
			unsigned int wrapMode = GL_REPEAT;
			bool pixelate = false;
		};

		class Texture : public IResource
		{
		public:
			Texture(std::filesystem::path const& file, const TextureParams& params = TextureParams());

			void Bind(unsigned int _textureUnit);

			int Width() const { return m_params.width; }
			int Height() const { return m_params.height; }
			int Component() const { return m_params.component; }
			GLuint TextureID() const { return m_params.m_textureID; }

		private:
			TextureParams m_params;
			~Texture();

			// Prevent copy
			Texture(const Texture&) = delete;
			Texture& operator=(const Texture&) = delete;

		};
	}
}