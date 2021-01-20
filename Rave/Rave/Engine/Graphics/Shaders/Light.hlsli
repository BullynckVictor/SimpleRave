struct Light
{
	float4	color;
	float3	position;
	uint	type;
	float3	direction;
	float	constAttenuation;
	float	linAttenuation;
	float	quadAttenuation;
	float	spotAngle;
	float	padding;
};

#define POINT_LIGHT		  0
#define SPOT_LIGHT		  1
#define DIRECTIONAL_LIGHT 2

static const float diffuseFactor = 1.0f;
static const float ambient = 0.07f;

float4 CalculateLight(const in float3 worldPos, const in float3 normal, const in float3 color, const in Light light)
{
	const float3 vToL    = light.position - worldPos;
	const float  distToL = length(vToL);
	const float3 dirToL  = vToL / distToL;

	const float att_c = light.constAttenuation;
	const float att_l = light.linAttenuation;
	const float att_q = light.quadAttenuation;

	const float att = 1.0f / (att_c + att_l * distToL + att_q * distToL * distToL);
	const float diffuse = diffuseFactor * att * max(0.0f, dot(dirToL, normal));

	return float4(saturate((diffuse + ambient) * color), 1.0f);
}