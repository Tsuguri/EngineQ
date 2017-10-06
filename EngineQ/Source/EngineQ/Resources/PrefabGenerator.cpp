#include "PrefabGenerator.hpp"

// Standard includes
#include <memory>
#include <random>

// Other projects
#include "EngineQCommon/Math/Vector3.hpp"
#include "EngineQCommon/Math/Vector2.hpp"
#include "EngineQCommon/Math/Quaternion.hpp"
#include "EngineQCommon/Math/Utils.hpp"
#include "EngineQRenderer/Graphics/Mesh.hpp"
#include "EngineQRenderer/Graphics/Texture.hpp"

// This project
#include "ResourceManager.hpp"


namespace EngineQ
{
	using namespace Math;

	namespace Resources
	{
		PrefabGenerator::PrefabGenerator(ResourceManager& resourceManager) :
			resourceManager{ resourceManager }
		{
		}

		Resource<Graphics::Mesh> PrefabGenerator::GenerateCapsule(Real height, Real radius)
		{
			Vector3 color{ 0.5f };

			height *= 0.5f;
			int verticalSegments = 16;
			int segments = 32;

			std::vector<EngineQ::VertexPNTC> vertices;
			vertices.reserve(2 * verticalSegments * segments + 2);

			vertices.push_back(VertexPNTC(Vector3::GetUp() * radius + Vector3(0.0f, height, 0.0f), Vector3::GetUp(), Vector2::GetZero(), color));
			for (int i = 1; i < verticalSegments; ++i)
			{
				auto vec = Vector3::GetUp() * radius;

				Quaternion rotation1 = Quaternion::CreateFromEuler(Utils::DegToRad(90.0f * i / verticalSegments), 0.0f, 0.0f);

				auto levelVec = rotation1 * vec;

				for (int j = 0; j < segments; ++j)
				{
					Quaternion rotation2 = Quaternion::CreateFromEuler(0.0f, Utils::DegToRad(360.0f * j / segments), 0.0f);

					auto finalVec = rotation2 * levelVec;
					
					vertices.push_back(VertexPNTC(finalVec + Vector3(0.0f, height, 0.0f), finalVec, Vector2::GetZero(), color));
				}
			}

			for (int i = 0; i < verticalSegments; ++i)
			{
				auto vec = Vector3::GetForward() * radius;

				Quaternion rotation1 = Quaternion::CreateFromEuler(Utils::DegToRad(90.0f * i / verticalSegments), 0.0f, 0.0f);

				auto levelVec = rotation1 * vec;

				for (int j = 0; j < segments; ++j)
				{
					Quaternion rotation2 = Quaternion::CreateFromEuler(0.0f, Utils::DegToRad(360.0f * j / segments), 0.0f);
				
					auto finalVec = rotation2 * levelVec;
					
					vertices.push_back(VertexPNTC(finalVec - Vector3(0.0f, height, 0.0f), finalVec, Vector2::GetZero(), color));
				}
			}
			vertices.push_back(VertexPNTC(Vector3::GetDown() * radius - Vector3(0.0f, height, 0.0f), Vector3::GetDown(), Vector2::GetZero(), color));


			std::vector<unsigned int> indices;
			indices.reserve((12 * verticalSegments - 6) * segments);

			// Upper hemisphere cap
			int offset = 1;
			for (int i = 0; i < segments; ++i)
			{
				indices.push_back(0);
				indices.push_back(offset + i);
				indices.push_back(offset + (i + 1) % segments);
			}

			// Rest
			for (int i = 0; i < 2 * verticalSegments - 2; ++i)
			{
				for (int j = 0; j < segments; ++j)
				{
					indices.push_back(offset + i * segments + j);
					indices.push_back(offset + (i + 1) * segments + j);
					indices.push_back(offset + (i + 1) * segments + (j + 1) % segments);
				
					indices.push_back(offset + i * segments + j);
					indices.push_back(offset + (i + 1) * segments + (j + 1) % segments);
					indices.push_back(offset + i * segments + (j + 1) % segments);
				}
			}

			// Lower hemisphere cap
			offset = 1 + 2 * (verticalSegments - 1) * segments;
			int lastPos = vertices.size() - 1;
			for (int i = 0; i < segments; ++i)
			{
				indices.push_back(lastPos);
				indices.push_back(offset + (i + 1) % segments);
				indices.push_back(offset + i);
			}


			auto resource = Resource<Graphics::Mesh>(std::make_unique<EngineQ::Graphics::Mesh>(vertices, indices));
			this->resourceManager.HoldResource(resource);
			return resource;
		}

		Resource<Graphics::Mesh> PrefabGenerator::GenerateCube(Math::Real side)
		{
			side *= 0.5f;

			Math::Vector3 color{ 0.5f };

			std::vector<EngineQ::VertexPNTC> vertices = {
				{ Math::Vector3{ +side, -side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, Math::Vector2{ 1.0f, 0.0f }, color },
				{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, Math::Vector2{ 0.0f, 0.0f }, color },
				{ Math::Vector3{ +side, +side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, Math::Vector2{ 1.0f, 1.0f }, color },
				{ Math::Vector3{ -side, +side, -side }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, Math::Vector2{ 0.0f, 1.0f }, color },

				{ Math::Vector3{ +side, -side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, Math::Vector2{ 0.0f, 0.0f }, color },
				{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, Math::Vector2{ 0.0f, 1.0f }, color },
				{ Math::Vector3{ -side, -side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, Math::Vector2{ 1.0f, 0.0f }, color },
				{ Math::Vector3{ -side, +side, +side }, Math::Vector3{ 0.0f, 0.0f, 1.0f }, Math::Vector2{ 1.0f, 1.0f }, color },

				{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, Math::Vector2{ 1.0f, 0.0f }, color },
				{ Math::Vector3{ -side, +side, +side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, Math::Vector2{ 0.0f, 1.0f }, color },
				{ Math::Vector3{ -side, +side, -side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, Math::Vector2{ 1.0f, 1.0f }, color },
				{ Math::Vector3{ -side, -side, +side }, Math::Vector3{ -1.0f, 0.0f, 0.0f }, Math::Vector2{ 0.0f, 0.0f }, color },

				{ Math::Vector3{ +side, -side, -side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, Math::Vector2{ 0.0f, 0.0f }, color },
				{ Math::Vector3{ +side, +side, -side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, Math::Vector2{ 0.0f, 1.0f }, color },
				{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, Math::Vector2{ 1.0f, 1.0f }, color },
				{ Math::Vector3{ +side, -side, +side }, Math::Vector3{ 1.0f, 0.0f, 0.0f }, Math::Vector2{ 1.0f, 0.0f }, color },

				{ Math::Vector3{ +side, -side, -side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, Math::Vector2{ 1.0f, 1.0f }, color },
				{ Math::Vector3{ +side, -side, +side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, Math::Vector2{ 1.0f, 0.0f }, color },
				{ Math::Vector3{ -side, -side, -side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, Math::Vector2{ 0.0f, 1.0f }, color },
				{ Math::Vector3{ -side, -side, +side }, Math::Vector3{ 0.0f, -1.0f, 0.0f }, Math::Vector2{ 0.0f, 0.0f }, color },

				{ Math::Vector3{ +side, +side, +side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, Math::Vector2{ 1.0f, 1.0f }, color },
				{ Math::Vector3{ +side, +side, -side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, Math::Vector2{ 1.0f, 0.0f }, color },
				{ Math::Vector3{ -side, +side, -side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, Math::Vector2{ 0.0f, 0.0f }, color },
				{ Math::Vector3{ -side, +side, +side }, Math::Vector3{ 0.0f, 1.0f, 0.0f }, Math::Vector2{ 0.0f, 1.0f }, color },
			};

			std::vector<unsigned int> indices = {
				0, 1, 2,
				1, 3, 2,

				4, 5, 6,
				6, 5, 7,

				8, 9, 10,
				9, 8, 11,

				12, 13, 14,
				14, 15, 12,

				16, 17, 18,
				19, 18, 17,

				20, 21, 22,
				22, 23, 20
			};

			auto resource = Resource<Graphics::Mesh>(std::make_unique<EngineQ::Graphics::Mesh>(vertices, indices));
			this->resourceManager.HoldResource(resource);
			return resource;
		}

		Resource<Graphics::Mesh> PrefabGenerator::GenerateQuad(Math::Real side)
		{
			side *= 0.5f;

			Math::Vector3 color{ 0.5f };

			std::vector<EngineQ::VertexPNTC> vertices = {
				{ Math::Vector3{ +side, -side, 0.0f }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, Math::Vector2{ 0.0f, 1.0f }, color },
				{ Math::Vector3{ -side, -side, 0.0f }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, Math::Vector2{ 1.0f, 1.0f }, color },
				{ Math::Vector3{ +side, +side, 0.0f }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, Math::Vector2{ 0.0f, 0.0f }, color },
				{ Math::Vector3{ -side, +side, 0.0f }, Math::Vector3{ 0.0f, 0.0f, -1.0f }, Math::Vector2{ 1.0f, 0.0f }, color },
			};

			std::vector<unsigned int> indices = {
				0, 1, 2,
				1, 3, 2,
			};

			auto resource = Resource<Graphics::Mesh>(std::make_unique<EngineQ::Graphics::Mesh>(vertices, indices));
			this->resourceManager.HoldResource(resource);
			return resource;
		}

		Resource<Graphics::Texture> PrefabGenerator::GenerateNoiseTexture(int width, int height)
		{
			std::uniform_real_distribution<GLfloat> randomFloats(0.0f, 1.0f);
			std::default_random_engine generator;

			int size = width * height;
			std::vector<EngineQ::Math::Vector3f> vectors(size);

			for (auto& vec : vectors)
				vec = EngineQ::Math::Vector3f(
					randomFloats(generator) * 2.0f - 1.0f, 
					randomFloats(generator) * 2.0f - 1.0f, 
					0.0f).GetNormalized();

			Graphics::Configuration::TextureConfiguration config;

			config.InternalFormat = GL_RGB16F;
			config.Format = GL_RGB;
			config.DataType = GL_FLOAT;
			config.MinFilter = GL_NEAREST;
			config.MagFilter = GL_NEAREST;
			config.WrapS = GL_REPEAT;
			config.WrapT = GL_REPEAT;

			auto resource = Resource<Graphics::Texture>(std::make_unique<Graphics::Texture>(width, height, config, vectors.data()));
			this->resourceManager.HoldResource(resource);
			return resource;
		}
	}
}