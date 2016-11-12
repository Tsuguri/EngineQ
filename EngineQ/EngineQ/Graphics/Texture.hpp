#ifndef ENGINEQ_GRAPHICS_TEXTURE_HPP
#define ENGINEQ_GRAPHICS_TEXTURE_HPP

#include <GL\glew.h>

#include <Utilities/Immovable.hpp>

namespace EngineQ
{
	namespace Graphics
	{
		class Texture : private Utilities::Immovable
		{
			friend class Shader;

		private:
			GLuint textureId;
			bool hasMipmaps;
			int width;
			int height;

			Texture() = default;

			void CreateFromFile(const char* filename, bool generateMipmaps);
			void CreateFromData(int width, int height, const unsigned char* data, bool generateMipmaps);

		public:
			Texture(const char* filename, bool generateMipmaps);
			~Texture();

			int GetWidth() const;
			int GetHeight() const;
			bool HasMipmaps() const;
		};
	}
}

#endif // !ENGINEQ_GRAPHICS_TEXTURE_HPP
