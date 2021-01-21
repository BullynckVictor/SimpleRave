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
static const float specularFactor = 1.0f;
static const float ambient = 0.07f;

float4 CalculateLight(
	const in float3 worldPos,
	const in float3 camPos,
	const in float3 normal, 
	const in float3 diffuseColor,
	const in float3 specularColor,
	const in float  specularIntensity,
	const in float  specularPower,
	const in Light light
)
{
	const float3 vToL    = light.position - worldPos;
	const float  distToL = length(vToL);
	const float3 dirToL  = vToL / distToL;
	const float3 n		 = normalize(normal);

	const float att = 1.0f / (light.constAttenuation + light.linAttenuation * distToL + light.quadAttenuation * distToL * distToL);
	const float diffuse = diffuseFactor * att * max(0.0f, dot(dirToL, n));

	const float3 dirToCam = worldPos - camPos;
	const float3 w = n * dot(dirToCam, n);
	const float3 r = dirToCam - w * 2.0f;

	const float specular = att * specularIntensity * specularFactor * pow(max(0, dot(normalize(r), normalize(camPos - worldPos))), specularPower);

	return float4(saturate((diffuse + ambient) * diffuseColor + specular * specularColor), 1.0f);
}