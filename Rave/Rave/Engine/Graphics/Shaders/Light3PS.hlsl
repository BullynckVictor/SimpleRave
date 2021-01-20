#include "Light.hlsli"
#include "Material.hlsli"

StructuredBuffer<Light> lights;
cbuffer MaterialBuffer
{
	Material material;
};

float4 main(float3 worldPos : Position, float3 normal : Normal) : SV_Target
{
	return CalculateLight(worldPos, normal, material.diffuse.xyz, lights[0]);
}