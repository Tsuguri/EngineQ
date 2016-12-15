#include "ShaderPass.hpp"

#include "Camera.hpp"
#include "Framebuffer.hpp"

#include "ShaderProperties.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		InputConfiguration::InputConfiguration(GLuint texture, std::string name) :
			Texture{ texture }, Name{ name }
		{
		}

		ShaderPass::ShaderPass(Resources::Resource<Shader> shader) :
			shader{ shader }
		{
		}

		void ShaderPass::BindTextures()
		{
			int i = 0;
			for (auto& inputTexture : inputTextures)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, inputTexture.Texture);
				if (inputTexture.Name != "")
				{
					auto prop = shader.TryGetProperty<GLint>(inputTexture.Name);
					
					if (prop != nullval)
						prop->Set(i);
				}
				i++;
			}
		}

		void ShaderPass::UnbindTextures()
		{
			for (int j=0;j<inputTextures.size();j++)
			{
				glActiveTexture(GL_TEXTURE0 + j);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		ShaderProperties & ShaderPass::GetShaderproperties()
		{
			return shader;
		}

		void ShaderPass::BindTargetBuffer() const
		{
			if (framebuffer == nullptr)
				Framebuffer::BindDefault();
			else
				framebuffer->Bind();
		}

		void ShaderPass::SetTargetBuffer(std::unique_ptr<Framebuffer>&&  buffer)
		{
			framebuffer = std::move(buffer);
		}

		bool ShaderPass::GetApplyShadowData()
		{
			return ApplyShadowData;
		}

		void ShaderPass::SetApplyShadowData(bool val)
		{
			ApplyShadowData = val;
		}

		void ShaderPass::AddInput(const InputConfiguration& input)
		{
			inputTextures.push_back(input);
		}

		void ShaderPass::Activate(Camera* cam, float time)
		{

			auto tmp = shader.TryGetProperty<Math::Vector3>(std::string("cameraPosition").c_str());
			if (tmp != nullval)
				*tmp = cam->GetPosition();
			auto tmp2 = shader.TryGetProperty<GLint>("time");
			if (tmp2 != nullval)
				*tmp2 = time;

			shader.Apply();
		}
	}
}