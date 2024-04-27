#include "../Include/XsHlsl.hlsl"

cbuffer materialConstantBuffer0 : register(b3, space0)
{
	float3 diffuse;
	float3 specular;
	float gloss;
};

struct Varying
{
	float4 position : SV_POSITION;
	float3 worldPosition : POSITION;
	float3 worldNormal : NORMAL;
};

Varying Vertex(AppData a2v)
{
	Varying v2f;

	v2f.position = ModelToClipPos(a2v.position);
	v2f.worldPosition = ModelToWorldPos(a2v.position);
	v2f.worldNormal = ModelToWorldNormal(a2v.normal);

	return v2f;
}

float4 Fragment(Varying v2f) : SV_Target
{
	const float lightIntensity = GetLightIntensity(v2f.worldPosition);

	const float3 lightDir = normalize(GetWorldLightDirection(v2f.worldPosition));
	const float3 diffuseColor = lightIntensity * lightColor * diffuse * max(0, dot(lightDir, v2f.worldNormal));

	const float3 viewDir = normalize(GetWorldViewDirection(v2f.worldPosition));
	const float3 halfDir = normalize(lightDir + viewDir);
	const float3 specularColor = lightIntensity * lightColor * specular * pow(max(0, dot(v2f.worldNormal, halfDir)), gloss);

	float3 color = ambient + diffuseColor + specularColor;
 
	return float4(color, 1.0f);
};
