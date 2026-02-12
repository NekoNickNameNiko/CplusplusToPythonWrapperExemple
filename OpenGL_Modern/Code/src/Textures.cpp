#include "../Include/Textures.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glad.h>

using namespace Bwt::Resources;


Texture::Texture(std::filesystem::path const& file, const TextureParams& params)
	: m_params(params)
{
	m_params.textureUnit = std::min(m_params.textureUnit, 31U);

	unsigned char* data = nullptr;

	std::cout << file.string(); 
	if (std::filesystem::exists(file))
	{
		std::cout << " exists\n";
		m_params.m_filepath = file.string();
		try
		{
			stbi_set_flip_vertically_on_load(1);
			data = stbi_load(m_params.m_filepath.c_str(), &m_params.width, &m_params.height, &m_params.component, STBI_rgb_alpha);
			if (!data)
			{
				throw std::runtime_error("No File.");
			}
		}
		catch (std::runtime_error)
		{
			std::cout << "Textures hasn't been load" << std::endl;
			return;
		}

		// Generate & Bind image
		glGenTextures(1, &m_params.m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_params.m_textureID);
		glTexImage2D(GL_TEXTURE_2D, m_params.level, GL_RGBA, m_params.width, m_params.height, 0, m_params.format, m_params.type, data);

		glBindTexture(GL_TEXTURE_2D, m_params.m_textureID);

		if (m_params.useMipMaps)
		{
			glGenerateMipmap(GL_TEXTURE_2D); // Load the Mipmap (Reduse texture quality later)
		}

		// Image setting
		if (m_params.useMipMaps)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //for when we are close
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //when we are far away
		}
		else if (m_params.pixelate)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //for when we are close
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //when we are far away
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //for when we are close
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //when we are far away
		}

		//	S and T just mean U and V(or X and Y if you prefer), or in GLSL :
		//	The GL_REPEAT mode has textures repeat when you go past(0, 0) to(1, 1) range
		//	The GL_CLAMP_TO_EDGE mode has textures stop at the last pixel when you fall off the edge.
		//	The GL_CLAMP and GL_CLAMP_TO_BORDER are depreciated because all texture borders must be 0 pixels, so the modes don't make sense anymore.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_params.wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_params.wrapMode);

		glBindTexture(GL_TEXTURE_2D, 0); // Reset le bind

		if (data != nullptr)
		{
			stbi_image_free(data);
			data = nullptr;
		}
	}
	else
	{
		std::cout << " does not exist\n";
	}
}

void Texture::Bind(unsigned int _textureUnit)
{
	m_params.textureUnit = _textureUnit;
	glActiveTexture(GL_TEXTURE0 + m_params.textureUnit);
	glBindTexture(GL_TEXTURE_2D, m_params.m_textureID);
}

Texture::~Texture()
{
	if (glIsTexture(m_params.m_textureID))
		glDeleteTextures(1, &m_params.m_textureID);
}
