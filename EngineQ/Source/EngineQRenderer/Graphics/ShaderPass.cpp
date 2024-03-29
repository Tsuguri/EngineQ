#include "ShaderPass.hpp"

// This project
#include "Camera.hpp"
#include "Framebuffer.hpp"
#include "ShaderProperties.hpp"


namespace EngineQ
{
	namespace Graphics
	{
		InputConfiguration::InputConfiguration(Resources::Resource<Texture> texture, const std::string& name) :
			texture{ texture }, Name{ name }
		{
		}

		ShaderPass::ShaderPass(std::unique_ptr<ShaderProperties> shaderProperties, const std::string& name) :
			shaderProperties{ std::move(shaderProperties) }, name{ name }
		{
		}

		ShaderPass::ShaderPass(Resources::Resource<Shader> shader, const std::string& name) :
			shaderProperties{ std::make_unique<ShaderProperties>(shader) }, name{ name }
		{
		}

		ShaderPass::~ShaderPass()
		{
		}

		ShaderProperties& ShaderPass::GetShaderProperties() const
		{
			return *shaderProperties.get();
		}

		void ShaderPass::BindTargetBuffer() const
		{
			if (framebuffer == nullptr)
				Framebuffer::BindDefault();
			else
				framebuffer->Bind();
		}

		void ShaderPass::SetTargetBuffer(std::unique_ptr<Framebuffer>&& buffer)
		{
			framebuffer = std::move(buffer);
		}

		const std::string & ShaderPass::GetName() const
		{
			return this->name;
		}

		bool ShaderPass::GetApplyShadowData() const
		{
			return applyShadowData;
		}

		void ShaderPass::SetApplyShadowData(bool val)
		{
			applyShadowData = val;
		}

		void ShaderPass::AddInput(const InputConfiguration& input)
		{
			if (input.Name.empty())
			{
				auto properties = shaderProperties->GetAllProperties<Resources::Resource<Texture>>();
				if (properties.size() != 1)
					throw "Invalid input configuration. No location name specified";

				auto& nameProperty = properties[0];

				inputTextures.emplace_back(input.texture, nameProperty.first);
				nameProperty.second = input.texture;
			}
			else
			{
				inputTextures.push_back(input);
				auto prop = shaderProperties->GetProperty<Resources::Resource<Texture>>(input.Name);
				prop = input.texture;
			}
		}

		void ShaderPass::BeforeRender()
		{
		}

		void ShaderPass::AfterRender()
		{
		}

		void ShaderPass::Created()
		{
		}

		void ShaderPass::Activate(Camera* cam, float time)
		{
			// TMP
			auto tmp = shaderProperties->TryGetProperty<Math::Vector3>(std::string("cameraPosition").c_str());
			if (tmp != nullval)
				*tmp = cam->GetPosition();
			auto tmp2 = shaderProperties->TryGetProperty<GLint>("time");
			if (tmp2 != nullval)
				*tmp2 = static_cast<GLint>(time);


			shaderProperties->Apply();
		}

		std::unique_ptr<ShaderPass> ShaderPassFactory::CreateShaderPass(const Configuration::EffectConfiguration& config, const std::string& name)
		{
			return std::make_unique<ShaderPass>(config.EffectShader, name);
		}
	}
}