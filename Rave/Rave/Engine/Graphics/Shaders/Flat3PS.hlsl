#include "Material.hlsli"

cbuffer MaterialBuffer
{
	Material material;
};

float4 main(float3 worldPos : Position, float3 normal : Normal) : SV_Target
{
	return float4(1.0f, 1.0f, 1.0f, 1.0f);
	return material.diffuse;
}