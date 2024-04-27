struct AppData
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float2 uv : TEXCOORD;
};

struct CompleteAppData
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	
	float2 uv0 : TEXCOORD;
	float2 uv1 : TEXCOORD1;
	float2 uv2 : TEXCOORD2;
	float2 uv3 : TEXCOORD3;
	float2 uv4 : TEXCOORD4;
};

cbuffer objectConstantBuffer0 : register(b0, space0)
{
	float4x4 modelToProject;
};

cbuffer objectConstantBuffer1 : register(b0, space1)
{
	float4x4 modelToWorld;
};

cbuffer objectConstantBuffer2 : register(b0, space2)
{
	float4x4 worldToModel;
};

float4 ModelToClipPos(float3 modelPosition)
{
	return mul(float4(modelPosition, 1.0f), modelToProject);
}

float3 ModelToWorldPos(float3 modelPosition)
{
	return mul(float4(modelPosition, 1.0f), modelToWorld);
}

float3 ModelToWorldDir(float3 modelDir)
{
	return normalize(mul(modelDir, (float3x3)modelToProject));
}

float3 ModelToWorldNormal(float3 modelNormal)
{
	return normalize(mul(modelNormal, (float3x3)transpose(worldToModel)));
}

cbuffer lightConstantBuffer0 : register(b1, space0)
{
	float3 ambient;
};

cbuffer lightConstantBuffer1 : register(b1, space1)
{
	int lightType;
};

cbuffer lightConstantBuffer2 : register(b1, space2)
{
	float3 lightPosition;
};

cbuffer lightConstantBuffer3 : register(b1, space3)
{
	float3 lightDirection;
};

cbuffer lightConstantBuffer4 : register(b1, space4)
{
	float3 lightColor;
};

cbuffer lightConstantBuffer5 : register(b1, space5)
{
	float lightIntensity;
};

cbuffer lightConstantBuffer6 : register(b1, space6)
{
	float lightRange;
};

cbuffer passConstantBuffer0 : register(b2, space0)
{
	float3 viewPosition;
};

float3 GetWorldLightDirection(float3 worldPos)
{
	if (lightType == 0)
	{
		return -lightDirection;
	}
	return lightPosition - worldPos;
}

float CalculateAttenuation(float distance, float range)
{
	return saturate((range - distance) / range);
}

float GetLightIntensity(float3 worldPos)
{
	if (lightType == 0)
	{
		return lightIntensity;
	}
	return lightIntensity * CalculateAttenuation(length(worldPos - lightPosition), lightRange);
}

float3 GetWorldViewDirection(float3 worldPos)
{
	return viewPosition - worldPos;
}
