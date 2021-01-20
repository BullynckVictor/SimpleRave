cbuffer CBuf
{
	matrix transform;
	matrix worldTransform;
};

struct VSOut
{
	float3 worldPos : Position;
	float3 normal   : Normal;
	float4 pos		: SV_Position;
};

VSOut main(float3 pos : Position, float3 normal : Normal)
{
	VSOut vso;
	vso.pos		 = mul(float4(pos, 1.0f), transform);
	vso.worldPos = mul(float4(pos, 1.0f), worldTransform).xyz;
	vso.normal	 = mul(normal, (float3x3)worldTransform);
	return vso;
}