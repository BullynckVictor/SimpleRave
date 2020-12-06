Texture2D tex;

SamplerState samplr;

float4 main(float2 texCoord : TexCoord) : SV_Target
{
	return tex.Sample(samplr, texCoord);
}