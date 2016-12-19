#include "Vertex.hpp"


namespace EngineQ
{
	VPos::VPos(const Math::Vector3& position) :
		position{ position }
	{
	}

	VNorm::VNorm(const Math::Vector3& normal) :
		normal{ normal }
	{
	}

	VCol::VCol(const Math::Vector3& color) :
		color{ color }
	{
	}

	VTex::VTex(const Math::Vector2& textureCoordinates) :
		textureCoordinates{ textureCoordinates }
	{
	}
}