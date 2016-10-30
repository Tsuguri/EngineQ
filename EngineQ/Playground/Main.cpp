#include <iostream>

//#include <Libraries/GL/glew.h>



struct Vector3
{
	float X = 0.0f;
	float Y = 0.0f;
	float Z = 0.0f;

	Vector3() = default;
	Vector3(float x, float y, float z) :
		X{ x }, Y{ y }, Z{ z }
	{
	}
};


using GLuint = unsigned int;
using GLint = int;
using GLenum = int;
using GLboolean = unsigned short;
using GLsizei = std::size_t;
using GLvoid = void;

#define GL_FLOAT 123
#define GL_FALSE 0

void glEnableVertexAttribArray(GLuint index)
{
	std::cout << "Enabled " << index << std::endl;
}

void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer)
{
	std::cout << "VertexAtribPointer: " << index << " " << size << " " << type << " " << normalized << " " << stride << " " << reinterpret_cast<std::size_t>(pointer) << std::endl << std::endl;
}

/*
template<typename... TVertexType>
class Vertex : public TVertexType...
{
public:
	Vertex() = default;
	Vertex(const typename TVertexType::type& ... value) :
		TVertexType{ value }...
	{
	}

	static void Setup()
	{
		Meta::Invoker<void(*)(), &Vertex::Enable<TVertexType>...>::Invoke();
	}

private:
	template<typename TType>
	static void Enable()
	{
		constexpr GLuint index = Meta::TypeIndex<TType, TVertexType...>::value;
		constexpr GLint size = sizeof(typename TType::type) / sizeof(typename TType::underlyingType);
		constexpr GLenum type = TypeMap<typename TType::underlyingType>::value;
		constexpr GLsizei stride = sizeof(Vertex);
		const GLvoid* pointer = reinterpret_cast<const GLvoid*>(Meta::SumN<index, std::size_t, sizeof(TVertexType)...>::value);

		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, type, GL_FALSE, stride, pointer);
	}

	template<typename TType>
	struct TypeMap;

	template<>
	struct TypeMap<float>
	{
		static constexpr GLenum value = GL_FLOAT;
	};
};

struct VPos
{
	using type = Vector3;
	using underlyingType = float;

	Vector3 position;

	VPos() = default;
	VPos(const Vector3& position) :
		position{ position }
	{
	}
};

struct VNorm
{
	using type = Vector3;
	using underlyingType = float;

	Vector3 normal;
	
	VNorm() = default;
	VNorm(const Vector3& normal) :
		normal{ normal }
	{
	}
};

struct VCol
{
	using type = Vector3;
	using underlyingType = float;

	Vector3 color;

	VCol() = default;
	VCol(const Vector3& color) :
		color{ color }
	{
	}
};
*/

namespace Utilities
{
	constexpr bool IsDigit(char c)
	{
		return '0' <= c && c <= '9';
	}

	constexpr bool IsLetter(char c)
	{
		return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
	}

	constexpr bool IsNameFirstChar(char c)
	{
		return IsLetter(c) || c == '_';
	}

	constexpr bool IsNameChar(char c)
	{
		return IsNameFirstChar(c) || IsDigit(c);
	}
}

#include <string>

std::string TranslateName(const std::string& originalName)
{
	std::string newName = originalName;

	std::size_t lastPos = 0;
	std::size_t pos = newName.find("__");
	while (pos != std::string::npos)
	{
		// Nothing after
		if (pos + 2 == newName.size())
			break;

		// Array
		if (Utilities::IsDigit(newName[pos + 2]))
		{
			newName[pos] = '[';
			lastPos = newName.size();

			for (std::size_t i = pos + 2; i < newName.size(); ++i)
			{
				if (!Utilities::IsDigit(newName[i]))
				{
					lastPos = i;
					break;
				}

				newName[i - 1] = newName[i];
			}

			newName[lastPos - 1] = ']';
		}
		// Struct
		else
		{
			newName[pos] = '.';
			for (std::size_t i = pos + 2; i < newName.size(); ++i)
				newName[i - 1] = newName[i];

			newName.resize(newName.size() - 1);
			lastPos = pos + 1;
		}

		pos = newName.find("__", lastPos);
	}

	return newName;
}

int main(int argc, char** argv)
{
	std::cout << "Test\n";

//	Vertex<VPos, VNorm, VCol> vertex{ Vector3{0, 0, 0}, Vector3{1, 1, 1}, Vector3{2, 2, 2} };
	

	std::cout << TranslateName("someName__some__other__324__name__123") << std::endl;

	return 0;
}