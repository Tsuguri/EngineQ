#ifndef VERTEXHPP
#define VERTEXHPP
#include "Math/Vector3.hpp"
#include <vector>

namespace EngineQ
{

	class VertexPNC
	{
	public:

		Math::Vector3 position;
		Math::Vector3 normal;
		Math::Vector3 color;

		VertexPNC();
		VertexPNC(Math::Vector3 position);
		VertexPNC(Math::Vector3 position,Math::Vector3 normal);
		VertexPNC(Math::Vector3 position,Math::Vector3 normal, Math::Vector3 color);
		~VertexPNC();


		static constexpr int positionCount = 3;
		static const size_t positionOffset;
		static constexpr int normalCount = 3;
		static const size_t normalOffset;
		static constexpr int colorCount = 3;
		static const size_t colorOffset;
	};
}




#endif
