#include "XsHlsl.hlsl"

Texture2D Diffuse : register(t0);
SamplerState DefaultSampler : register(s0);

struct VertexIn
{
	float3 PosL : POSITION;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
	
	float2 Tex : TEXCOORD;
};

struct VertexOut
{
	float4 PosH : SV_POSITION;
	float2 Tex : TEXCOORD;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;

	vout.PosH = mul(float4(vin.PosL, 1.0f), modelToProject);
	vout.Tex = vin.Tex;

	return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	const float4 baseColor = Diffuse.Sample(DefaultSampler, pin.Tex);
	return baseColor * float4(lightColor, 1.0f);
};
