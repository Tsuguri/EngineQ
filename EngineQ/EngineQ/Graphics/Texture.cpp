#include "Texture.hpp"

#include <SOIL/SOIL.h>

namespace EngineQ
{
	namespace Graphics
	{
		void Texture::CreateFromFile(const char* filename, bool generateMipmaps)
		{
			int width, height;
			unsigned char* data = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
			
			this->CreateFromData(width, height, data, generateMipmaps);

			SOIL_free_image_data(data);
		}

		void Texture::CreateFromData(int width, int height, const unsigned char* data, bool generateMipmaps)
		{
			this->width = width;
			this->height = height;
			this->hasMipmaps = generateMipmaps;

			glGenTextures(1, &this->textureId);
			glBindTexture(GL_TEXTURE_2D, this->textureId);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			
			if (generateMipmaps)
			{
				glGenerateMipmap(GL_TEXTURE_2D);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			}
			else
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}

		Texture::Texture(const char* filename, bool generateMipmaps)
		{
			this->CreateFromFile(filename, generateMipmaps);
		}
		
		Texture::~Texture()
		{
			glDeleteTextures(1, &this->textureId);
		}

		int Texture::GetWidth() const
		{
			return this->width;
		}

		int Texture::GetHeight() const
		{
			return this->height;
		}

		bool Texture::HasMipmaps() const
		{
			return this->hasMipmaps;
		}
	}
}