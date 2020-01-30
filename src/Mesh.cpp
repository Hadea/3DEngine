#include "Mesh.h"





Core::Mesh::Mesh(std::string pFileName)
{
    OutputDebugString("loading Mesh");
	//TODO: Hausaufgabe :D
}

Core::Mesh::Mesh(PrimitiveType pPrimitiveType)
{
    OutputDebugString("loading primitive mehs");
	switch (pPrimitiveType)
	{
    case Core::PrimitiveType::Plane:
        //                          X     Y    Z       R  G  B  A
        Vertices = new float[28] {  0.8f, -0.8f, 0.0f, 1, 0, 0, 1,
                                   -0.8f, -0.8f, 0.0f, 0, 1, 0, 1,
                                    0.8f,  0.8f, 0.0f, 0, 0, 1, 1,
                                   -0.8f,  0.8f, 0.0f, 0, 0, 0, 1 };
        
        /*
        break;
    case Core::PrimitiveType::Cube:
        break;
    case Core::PrimitiveType::Sphere:
        break;
    case Core::PrimitiveType::Pyramid:
        break;
    case Core::PrimitiveType::Triangle:
        break;
    case Core::PrimitiveType::Capsule:
        break;*/
    default:
        std::cout << "Not yet implemented :(";
        break;
	}
}

Core::Mesh::~Mesh()
{
	if(Vertices != nullptr) delete[] Vertices;
}
