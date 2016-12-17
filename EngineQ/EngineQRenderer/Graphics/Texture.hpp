#ifndef ENGINEQ_GRAPHICS_TEXTURE_HPP
#define ENGINEQ_GRAPHICS_TEXTURE_HPP

#include <Libraries/GL/glew.h>

#include <Utilities/Immovable.hpp>
#include "Configuration\RendererConfiguration.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		class Texture : private Utilities::Immovable
		{
			friend class Shader;

		private:
			GLuint textureId;
			bool hasMipmaps = false;
			int width = 0;
			int height = 0;
			bool resizable = false;
			Configuration::TextureConfiguration configuration;

			Texture() = default;

			void CreateFromFile(const char* filename, bool generateMipmaps);
			void CreateFromData(int width, int height, const unsigned char* data, bool generateMipmaps);
			void CreateFromConfiguration(int width, int height, const Configuration::TextureConfiguration& configuration);

		public:
			Texture(const char* filename, bool generateMipmaps);
			Texture(int width, int height,const Configuration::TextureConfiguration& configuration);
			~Texture();

			void Resize(int width, int height);
			int GetWidth() const;
			int GetHeight() const;
			GLuint GetTextureID();
			bool HasMipmaps() const;
		};
	}
}

#endif // !ENGINEQ_GRAPHICS_TEXTURE_HPP
