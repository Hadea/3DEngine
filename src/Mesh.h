#pragma once
#include <string>
#include <iostream>

namespace Core
{
	enum class PrimitiveType : uint8_t
	{
		Plane,
		Cube,
		Sphere,
		Pyramid,
		Triangle,
		Capsule
	};


	class Mesh
	{
	public:
		Mesh(std::string pFileName);
		Mesh( PrimitiveType pPrimitiveType);
		~Mesh();

		float* Vertices = nullptr;

	};
}