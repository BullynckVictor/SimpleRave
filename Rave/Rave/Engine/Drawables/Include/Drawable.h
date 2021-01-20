#pragma once
#include "Engine/Graphics/Include/ConstantBuffer.h"
#include "Engine/Graphics/Include/IndexBuffer.h"
#include "Engine/Graphics/Include/VertexBuffer.h"
#include "Engine/Graphics/Include/BufferView.h"
#include "Engine/Utilities/Include/Vector.h"
#include "Engine/Include/MemoryManager.h"
#include "Engine/Include/Transform.h"
#include "Engine/Drawables/Include/Material.h"

namespace rave
{
	typedef D3D11_PRIMITIVE_TOPOLOGY Topology;

	struct TVertex2
	{
		Vertex2 pos;
		Vertex2 tex;
	};

	struct NVertex3
	{
		Vertex3 pos;
		Vertex3 normal;
	};

	struct MatrixBuffer
	{
		Matrix view;
		Matrix world;
	};

	template<typename T>
	concept BindableConcept = requires(T t, Graphics gfx)
	{
		t.Bind(gfx);
	};
}