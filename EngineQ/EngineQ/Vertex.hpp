#ifndef ENGINEQ_VERTEX_HPP
#define ENGINEQ_VERTEX_HPP

#include <vector>

#include "Libraries/GL/glew.h"

#include "Math/Vector3.hpp"
#include "Utilities/Metaprogramming.hpp"

namespace EngineQ
{
	template<typename TType>
	struct VertexTypeMap;
	
	template<>
	struct VertexTypeMap<float>
	{
		static constexpr GLenum value = GL_FLOAT;
	};


	template<typename... TVertexTypes>
	class Vertex : public TVertexTypes...
	{
	public:
		Vertex() = default;
		Vertex(const typename TVertexTypes::Type&... value) :
			TVertexTypes{ value }...
		{
		}

		static void Setup()
		{
			Meta::Invoker<void(*)(), &Vertex::Enable<TVertexTypes>...>::Invoke();
		}

	private:
		template<typename TType>
		static void Enable()
		{
			constexpr std::size_t index = Meta::TypeIndex<TType, TVertexTypes...>::value;
			constexpr GLuint location = TType::Location;
			constexpr GLint size = sizeof(typename TType::Type) / sizeof(typename TType::UnderlyingType);
			constexpr GLenum type = VertexTypeMap<typename TType::UnderlyingType>::value;
			constexpr GLsizei stride = sizeof(Vertex);
			const GLvoid* pointer = reinterpret_cast<const GLvoid*>(Meta::SumN<index, std::size_t, sizeof(TVertexTypes)...>::value);

			glEnableVertexAttribArray(location);
			glVertexAttribPointer(location, size, type, GL_FALSE, stride, pointer);
		}
	};



	template<typename TType, typename TUnderlyingType, GLuint TLocation>
	struct VertexComponent
	{
		using Type = TType;
		using UnderlyingType = TUnderlyingType;
		static constexpr GLuint Location = TLocation;
	};

	struct VPos : public VertexComponent<Math::Vector3, Math::Real, 0>
	{
		Math::Vector3 position;

		VPos() = default;
		VPos(const Math::Vector3& position);
	};

	struct VNorm : public VertexComponent<Math::Vector3, Math::Real, 3>
	{
		Math::Vector3 normal;

		VNorm() = default;
		VNorm(const Math::Vector3& normal);
	};

	struct VCol : public VertexComponent<Math::Vector3, Math::Real, 2>
	{
		Math::Vector3 color;

		VCol() = default;
		VCol(const Math::Vector3& color);
	};



	using VertexPNC = Vertex<VPos, VNorm, VCol>;
}

#endif // !ENGINEQ_VERTEX_HPP
