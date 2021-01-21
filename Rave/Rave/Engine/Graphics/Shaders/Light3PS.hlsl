#include "Light.hlsli"
#include "Material.hlsli"

StructuredBuffer<Light> lights;
cbuffer MaterialBuffer
{
	Material material;
};

cbuffer CameraBuffer
{
	float3 camPos;
};

float4 main(float3 worldPos : Position, float3 normal : Normal) : SV_Target
{
	return CalculateLight(
		worldPos, 
		camPos, 
		normal, 
		material.diffuse.xyz, 
		material.specular.xyz, 
		material.specularIntensity, 
		material.specularPower, 
		lights[0]
	);
}