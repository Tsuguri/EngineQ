#ifndef ENGINEQ_GRAPHICS_POSTPROCESSING_EFFECT_HPP
#define ENGINEQ_GRAPHICS_POSTPROCESSING_EFFECT_HPP

#include "Configuration/RendererConfiguration.hpp"
//#include "Framebuffer.hpp"
//#include "Shader.hpp"
#include <Resources/Resource.hpp>
#include "Types.hpp"
namespace EngineQ
{
	namespace Graphics
	{
		struct InputConfiguration
		{
			GLuint Position;
			GLuint Texture;
			std::string Name;

			InputConfiguration(GLuint position, GLuint texture,std::string name);
		};


		class ShaderPass
		{
			Resources::Resource<Shader> shader;

			std::vector<InputConfiguration> inputTextures;
			std::unique_ptr<Framebuffer> framebuffer;
		public:
			static GLenum textureLocations[10];
			ShaderPass(Resources::Resource<Shader> shader);

			void BindTextures();
			void UnbindTextures();

			void BindTargetBuffer() const;
			void SetTargetBuffer(std::unique_ptr<Framebuffer>&& buffer);

			void AddInput(const InputConfiguration& input);

			void Activate(Camera* cam, float time) const;

		};
	}
}

#endif