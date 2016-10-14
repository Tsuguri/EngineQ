#include <iostream>

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

template<typename... TVertexType>
struct Vertex : public TVertexType...
{
	Vertex() = default;
	Vertex(const typename TVertexType::type& ... value) :
		TVertexType{ value }...
	{
	}
};

struct VPos
{
	using type = Vector3;

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

	Vector3 color;

	VCol() = default;
	VCol(const Vector3& color) :
		color{ color }
	{
	}
};


int main(int argc, char** argv)
{
	std::cout << "Test\n";

	Vertex<VPos, VNorm, VCol> vertex{ Vector3{0, 0, 0}, Vector3{1, 1, 1}, Vector3{2, 2, 2} };
	
	

	return 0;
}