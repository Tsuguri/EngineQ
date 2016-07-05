#include "Vertex.hpp"
namespace EngineQ
{
	const size_t VertexPNC::positionOffset = offsetof(VertexPNC, position);
	const size_t VertexPNC::normalOffset = offsetof(VertexPNC, normal);
	const size_t VertexPNC::colorOffset = offsetof(VertexPNC, color);

	EngineQ::VertexPNC::VertexPNC() : position{ 0.0f }, normal{ 0.0f }, color{ 0.5f }
	{
	}

	VertexPNC::VertexPNC(Math::Vector3 position) : position{position}, normal{0.0f},color{0.5f}
	{
	}

	VertexPNC::VertexPNC(Math::Vector3 position, Math::Vector3 normal) : position{position}, normal{normal}, color{0.5f}
	{
	}

	VertexPNC::VertexPNC(Math::Vector3 position, Math::Vector3 normal, Math::Vector3 color): position{position}, normal{normal},color{color}
	{
	}

	VertexPNC::~VertexPNC()
	{
	}
}
