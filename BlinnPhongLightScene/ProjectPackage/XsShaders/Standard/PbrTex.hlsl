#include "../Include/XsHlsl.hlsl"

#define PI 3.14159265359f

cbuffer materialConstantBuffer0 : register(b3, space0)
{
	float roughness;
};

cbuffer materialConstantBuffer1 : register(b3, space1)
{
	float metallic;
};

Texture2D albedoTex : register(t0);
SamplerState defaultSampler : register(s0);

struct Varying
{
	float4 position : SV_POSITION;
	float3 worldPosition : POSITION;
	float3 worldNormal : NORMAL;
    float2 uv : TEXCOORD;
};

Varying Vertex(AppData a2v)
{
	Varying v2f;

	v2f.position = ModelToClipPos(a2v.position);
	v2f.worldPosition = ModelToWorldPos(a2v.position);
	v2f.worldNormal = ModelToWorldNormal(a2v.normal);
    v2f.uv = a2v.uv;

	return v2f;
}

float3 FresnelSchlick(float cosTheta, float3 fresnel0)
{
	return fresnel0 + (1.0 - fresnel0) * pow(1.0 - cosTheta, 5.0);
}

float NormalDistributionGGXTR(float3 normal, float3 halfDir, float fRoughness)
{
    float a = fRoughness * fRoughness;
    float aSqu = a * a;
    float NdotH = max(dot(normal, halfDir), 0.0f);
    float NdotHSqu = NdotH * NdotH;

    float denom = (NdotHSqu * (aSqu - 1.0f) + 1.0f);
    denom = PI * denom * denom;

    return aSqu / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;

    float denom = NdotV * (1.0 - k) + k;

    return NdotV / denom;
}

float GeometrySmith(float3 normal, float3 viewDir, float3 lightDir, float roughness)
{
    float NdotV = max(dot(normal, viewDir), 0.0);
    float NdotL = max(dot(normal, lightDir), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

float4 Fragment(Varying v2f) : SV_Target
{
    float3 worldNormal = normalize(v2f.worldNormal);
    float3 viewDir = normalize(GetWorldViewDirection(v2f.worldPosition));

    float3 albedo = albedoTex.Sample(defaultSampler, v2f.uv).rgb;
    float3 fresnel0 = float3(0.04f, 0.04f, 0.04f);
    fresnel0 = lerp(fresnel0, albedo, metallic);

    float3 worldLightDir = normalize(GetWorldLightDirection(v2f.worldPosition));
    float3 halfDir = normalize(worldLightDir + viewDir);
    
    float3 r = max(roughness, 0.01f);
    float brdfGrometry = GeometrySmith(worldNormal, viewDir, worldLightDir, r);
    float brdfDistribution = NormalDistributionGGXTR(worldNormal, halfDir, r);
    float brdfFresnel = FresnelSchlick(saturate(dot(halfDir, viewDir)), fresnel0);

    float lambert = saturate(dot(worldNormal, worldLightDir));

    float lightIntensity = GetLightIntensity(v2f.worldPosition);
    float3 radiance = lightColor;
                
    float3 color = ambient * albedo + lambert * radiance * lightIntensity * (albedo + brdfFresnel * brdfDistribution * brdfGrometry);
    return float4(color, 1.0f);
};
