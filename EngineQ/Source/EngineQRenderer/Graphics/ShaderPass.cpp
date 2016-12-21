#include "ShaderPass.hpp"

// This project
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
			if (input.Name.empty())
			{
				auto properties = shader.GetAllProperties<Resources::Resource<Texture>>();
				if (properties.size() != 1)
					throw "Invalid input configuration. No location name specified";

				auto& nameProperty = properties[0];

				inputTextures.emplace_back(input.texture, nameProperty.first);
				nameProperty.second = input.texture;
			}
			else
			{
				inputTextures.push_back(input);
				auto property = shader.GetProperty<Resources::Resource<Texture>>(input.Name);
				property = input.texture;
			}
		}

		void ShaderPass::Activate(Camera* cam, float time)
		{
			// TMP
			auto tmp = shader.TryGetProperty<Math::Vector3>(std::string("cameraPosition").c_str());
			if (tmp != nullval)
				*tmp = cam->GetPosition();
			auto tmp2 = shader.TryGetProperty<GLint>("time");
			if (tmp2 != nullval)
				*tmp2 = static_cast<GLint>(time);


			shader.Apply();
		}
	}
}