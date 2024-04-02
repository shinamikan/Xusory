cbuffer objectConstantBuffer0 : register(b0, space0)
{
	float4x4 modelToProject;
};

cbuffer objectConstantBuffer1 : register(b0, space1)
{
	float4x4 modelToWorld;
};

float4 ObjectToProjectPos(float3 modelPosition)
{
	return mul(float4(modelPosition, 1.0f), modelToProject);
}

float4 ObjectToProjectPos(float4 modelPosition)
{
	return mul(modelPosition, modelToProject);
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

float3 GetLightDirection(float3 worldPos)
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
	return CalculateAttenuation(length(worldPos - lightPosition), lightRange);
}
