#include "../Include/XsHlsl.hlsl"

Texture2D diffuse : register(t0);
SamplerState defaultSampler : register(s0);

struct Varying
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

Varying Vertex(AppData a2v)
{
	Varying v2f;

	v2f.position = ModelToClipPos(a2v.position);
	v2f.uv = a2v.uv;

	return v2f;
}

float4 Fragment(Varying v2f) : SV_Target
{
	const float4 baseColor = diffuse.Sample(defaultSampler, v2f.uv);
	return baseColor * float4(lightColor, 1.0f);
};
