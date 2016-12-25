#include "Texture.hpp"

// Libraries
#include <SOIL/SOIL.h>


namespace EngineQ
{
	namespace Graphics
	{
		void Texture::CreateFromFile(const char* filename, bool generateMipmaps)
		{
			int width, height;
			this->resizable = false;

			unsigned char* data = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
			
			this->CreateFromData(width, height, data, generateMipmaps);

			SOIL_free_image_data(data);
		}

		void Texture::CreateFromData(int width, int height, const unsigned char* data, bool generateMipmaps)
		{
			this->resizable = false;
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

		void Texture::CreateFromConfiguration(int width, int height, const Configuration::TextureConfiguration& configuration)
		{
			this->resizable = true;
			this->hasMipmaps = false;
			this->width = width;
			this->height = height;
			this->configuration = configuration;
			
			glGenTextures(1, &this->textureId);
			glBindTexture(GL_TEXTURE_2D, this->textureId);
			glTexImage2D(GL_TEXTURE_2D, 0, configuration.InternalFormat, width, height, 0, configuration.Format, configuration.DataType, nullptr);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			
			if (configuration.setBorderColor)
				glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, configuration.borderCorlor.data());
		}

		Texture::Texture(const char* filename, bool generateMipmaps)
		{
			this->CreateFromFile(filename, generateMipmaps);
		}

		Texture::Texture(int width, int height, const Configuration::TextureConfiguration& configuration)
		{
			this->CreateFromConfiguration(width,height, configuration);
		}
		
		Texture::Texture(int width, int height, const float* data)
		{
			glGenTextures(1, &this->textureId);
			glBindTexture(GL_TEXTURE_2D, this->textureId);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &this->textureId);
		}

		void Texture::Resize(int width, int height)
		{
			if (!resizable || (this->width == width && this->height == height))
				return;
			this->width = width;
			this->height = height;
			glBindTexture(GL_TEXTURE_2D, this->textureId);
			glTexImage2D(GL_TEXTURE_2D, 0, configuration.InternalFormat, width, height, 0, configuration.Format, configuration.DataType, nullptr);
		}

		int Texture::GetWidth() const
		{
			return this->width;
		}

		int Texture::GetHeight() const
		{
			return this->height;
		}

		GLuint Texture::GetTextureID()
		{
			return textureId;
		}

		bool Texture::HasMipmaps() const
		{
			return this->hasMipmaps;
		}
	}
}