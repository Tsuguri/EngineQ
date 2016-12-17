#include "ShaderPass.hpp"

#include "Camera.hpp"
#include "Framebuffer.hpp"

#include "ShaderProperties.hpp"

namespace EngineQ
{
	namespace Graphics
	{
		InputConfiguration::InputConfiguration(Resources::Resource<Texture> texture, std::string name) :
			texture{ texture }, Name{ name }
		{
		}

		ShaderPass::ShaderPass(Resources::Resource<Shader> shader) :
			shader{ shader }
		{
		}

		void ShaderPass::BindTextures()
		{
			for (auto& inputTexture : inputTextures)
			{
				auto property = shader.TryGetProperty <Resources::Resource<Texture>>(inputTexture.Name);
				if (property != nullval)
				{
					property->Set(inputTexture.texture);
				}
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
			BindTextures();
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