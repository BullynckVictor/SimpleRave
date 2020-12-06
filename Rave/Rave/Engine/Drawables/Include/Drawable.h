#pragma once
#include "Engine/Graphics/Include/ConstantBuffer.h"
#include "Engine/Graphics/Include/IndexBuffer.h"
#include "Engine/Graphics/Include/VertexBuffer.h"
#include "Engine/Utilities/Include/Vector2D.h"
#include "Engine/Include/MemoryManager.h"
#include "Engine/Include/Transform.h"

namespace rave
{
	typedef D3D11_PRIMITIVE_TOPOLOGY Topology;

	struct TVertex
	{
		Vertex pos;
		Vertex tex;
	};
}