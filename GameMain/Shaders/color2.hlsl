cbuffer cbPerObject : register(b1)
{
	float4x4 gWorldViewProj;
};

Texture2D Diffuse : register(t0);
Texture2D Diffuse1 : register(t1);
SamplerState DefaultSampler : register(s0);

struct VertexIn
{
	float3 PosL : POSITION;
	float4 Color : COLOR;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
	
	float2 Tex : TEXCOORD;
	float2 Tex1 : TEXCOORD1;
};

struct VertexOut
{
	float4 PosH : SV_POSITION;
	float4 Color : COLOR;
	float2 Tex : TEXCOORD;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;

	//vout.PosH = float4(vin.PosL, 1.0f);
	vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
	vout.Color = vin.Color;
	vout.Tex = vin.Tex;

	return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	const float4 baseColor = Diffuse.Sample(DefaultSampler, pin.Tex);
	const float4 baseColor1 = Diffuse1.Sample(DefaultSampler, pin.Tex);

	return 0.5 * baseColor + 0.5 * baseColor1;
};
