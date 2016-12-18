#include "CubeTexture.hpp"

#include <SOIL/SOIL.h>
#include <array>
namespace EngineQ
{
	namespace Graphics
	{

		CubeTexture::Configuration::Configuration(int width, int height, GLuint format, GLuint internalFormat, GLuint dataType)
		{
			this->Width = width;
			this->Height = height;
			this->Format = format;
			this->InternalFormat = internalFormat;
		}

		void CubeTexture::Init()
		{
			Free();
			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}
		void CubeTexture::InitFromNames(std::array<const char*, 6> names)
		{
			Init();
			int soilWidth, soilHeight;

			for (int i = 0; i < 6; i++)
			{
				unsigned char* data = SOIL_load_image(names[i], &soilWidth, &soilHeight, 0, SOIL_LOAD_RGB);

				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, soilWidth, soilHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			}
			this->configuration = Configuration{ soilWidth,soilHeight };

		}

		void CubeTexture::InitFromTextures(std::vector<Resources::Resource<Texture>> textures)
		{
			throw "Not implemented yet";
		}

		void CubeTexture::InitEmpty(Configuration& configuration)
		{
			Init();
			this->width = configuration.Width;
			this->height = configuration.Height;
			this->resizable = true;
			this->configuration = configuration;
			for (int i = 0; i < 6; i++)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, configuration.InternalFormat, width, height, 0, configuration.Format, configuration.DataType, nullptr);
			}
		}

		void CubeTexture::Free()
		{
			if (textureID == 0)
				return;
			glDeleteTextures(1, &this->textureID);
		}

		CubeTexture::CubeTexture(const char * top, const char * bottom, const char * north, const char * south, const char * west, const char * east)
		{

			std::array<const char*, 6> names = { east, west, top, bottom, north, south };

			InitFromNames(names);


		}

		CubeTexture::CubeTexture(std::array<const char*, 6> names)
		{
			InitFromNames(names);
		}

		CubeTexture::CubeTexture(Configuration& configuration)
		{
			InitEmpty(configuration);
		}

		CubeTexture::~CubeTexture()
		{
			Free();
		}

		void CubeTexture::Resize(int width, int height)
		{
			if (this->width == width && this->height == height)
				return;
			if (!resizable)
				return;
			this->width = width;
			this->height = height;
			glBindTexture(GL_TEXTURE_2D, this->textureID);
			for (int i = 0; i < 6; i++)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, configuration.InternalFormat, width, height, 0, configuration.Format, configuration.DataType, nullptr);
			}
		}

		int CubeTexture::GetWidth() const
		{
			return width;
		}

		int CubeTexture::GetHeight() const
		{
			return height;
		}
	}
}