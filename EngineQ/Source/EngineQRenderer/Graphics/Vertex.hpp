#ifndef ENGINEQ_VERTEX_HPP
#define ENGINEQ_VERTEX_HPP

// Standard includes
#include <vector>

// Libraries
#include <GL/glew.h>

// Other projects
#include "EngineQCommon/Math/Vector3.hpp"
#include "EngineQCommon/Utilities/Metaprogramming.hpp"


namespace EngineQ
{
	template<typename TType>
	struct VertexTypeMap;
	
	template<>
	struct VertexTypeMap<float>
	{
		static constexpr GLenum value = GL_FLOAT;
	};

	template<typename TVertexType>
	struct VertexTypeType
	{
		using type = typename TVertexType::Type;
	};

	template<typename... TVertexTypes>
	class Vertex : public TVertexTypes...
	{
		static_assert(!Meta::HasDuplicateValues<GLuint, TVertexTypes::Location...>::value, "Vertex component must have unique locations");

	public:
		Vertex() = default;
		Vertex(const typename VertexTypeType<TVertexTypes>::type&... value) :
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

	struct VTex : public VertexComponent<Math::Vector2, Math::Real, 1>
	{
		Math::Vector2 textureCoordinates;

		VTex() = default;
		VTex(const Math::Vector2& textureCoordinates);
	};

	using VertexPNC = Vertex<VPos, VNorm, VCol>;
	using VertexPNTC = Vertex<VPos, VNorm, VTex, VCol>;
}

#endif // !ENGINEQ_VERTEX_HPP
