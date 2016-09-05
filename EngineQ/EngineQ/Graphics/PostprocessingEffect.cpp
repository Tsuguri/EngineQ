#include "PostprocessingEffect.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		GLenum PostprocessingEffect::textureLocations[10] = {
			GL_TEXTURE0,
			GL_TEXTURE1,
			GL_TEXTURE2,
			GL_TEXTURE3,
			GL_TEXTURE4,
			GL_TEXTURE5,
			GL_TEXTURE6,
			GL_TEXTURE7,
			GL_TEXTURE8,
			GL_TEXTURE9
		};



		InputConfiguration::InputConfiguration(GLenum position, GLuint texture) : Position(position), Texture(texture)
		{
		}

		PostprocessingEffect::PostprocessingEffect(std::shared_ptr<Shader> shader) : shader(shader)
		{
		}

		void PostprocessingEffect::BindTextures()
		{
			for(auto& i : inputTextures)
			{
				//glActiveTexture(i.Position);
				glBindTexture(GL_TEXTURE_2D, i.Texture);
			}
		}

		void PostprocessingEffect::UnbindTextures()
		{
			for(auto& i : inputTextures)
			{
				//glActiveTexture(i.Position);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		void PostprocessingEffect::BindTargetBuffer() const
		{
			if (framebuffer == nullptr)
				Framebuffer::BindDefault();
			else
				framebuffer->Bind();
		}

		void PostprocessingEffect::SetTargetBuffer(std::shared_ptr<Framebuffer>  buffer)
		{
			framebuffer = buffer;
		}

		void PostprocessingEffect::AddInput(InputConfiguration input)
		{
			inputTextures.push_back(input);
		}

		void PostprocessingEffect::Activate() const
		{
			shader->Activate();
		}
	}
}