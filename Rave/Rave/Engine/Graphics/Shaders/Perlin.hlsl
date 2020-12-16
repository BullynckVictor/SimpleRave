RWTexture2D<float4> tex;

[numthreads(1, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
	tex[DTid.xy] = float4(DTid.x, DTid.y, DTid.z, 1.0f);
}