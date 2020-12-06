cbuffer CBuff
{
	matrix mat;
};

struct VSOut
{
	float2 tex : TexCoord;
	float4 pos : SV_Position;
};

VSOut main(float2 pos : Position, float2 tex : TexCoord)
{
	VSOut vso;
	vso.tex = tex;
	vso.pos = mul(float4(pos.x, pos.y, 0.0f, 1.0f), mat);
	return vso;
}