#include "Engine/Drawables/Include/Mesh.h"
#include "Libraries/Assimp/Importer.hpp"

rave::Mesh& rave::Mesh::Load(Graphics& gfx, const Transform3& transform, const wchar_t* filename)
{
	Assimp::Importer importer;


	return *this;
}

void rave::Mesh::Bind(Graphics& gfx) const
{
}

void rave::Mesh::WriteTransform(Graphics& gfx, const Transform3& transform)
{
}
