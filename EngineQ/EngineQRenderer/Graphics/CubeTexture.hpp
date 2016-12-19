#ifndef ENGINEQ_GRAPHICS_CUBETEXTURE_HPP
#define ENGINEQ_GRAPHICS_CUBETEXTURE_HPP

// Libraries
#include <GL/glew.h>

// Other projects
#include "EngineQCommon/Utilities/Immovable.hpp"

// This project
#include "Configuration/RendererConfiguration.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		class CubeTexture : private Utilities::Immovable
		{
			friend class Shader;
		public:
			struct Configuration
			{
				GLuint Format = GL_RGB;
				GLuint InternalFormat = GL_RGB;
				GLuint DataType = GL_UNSIGNED_BYTE;
				int Width = 1;
				int Height = 1;

				Configuration(int with, int height, GLuint format = GL_RGB, GLuint internalFormat = GL_RGB, GLuint dataType = GL_UNSIGNED_BYTE);
				Configuration() = default;
			};
		private:
			GLuint textureID = 0;

			Configuration configuration;

			CubeTexture() = default;
			int width = -1;
			int height = -1;
			bool resizable = false;

			void Init();
			// TODO: add customizable texture format 
			void InitFromNames(std::array<const char*,6> names);
			void InitFromTextures(std::vector<Resources::Resource<Texture>> textures);
			void InitEmpty(Configuration& configuration);

			void Free();
		public:

			CubeTexture(const char* top, const char* bottom, const char* north, const char* south, const char* west, const char* east);
			/**
			 * names in standard order: top,bottom,north,south,west,east
			 */
			CubeTexture(std::array<const char*, 6> names);
			CubeTexture(std::vector<Resources::Resource<Texture>> textures);
			CubeTexture(Configuration& configuration);
			virtual ~CubeTexture();

			void Resize(int width, int height);
			int GetWidth() const;
			int GetHeight() const;

		};
	}
}

#endif