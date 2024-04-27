#pragma once

#include "../XusoryEngine.h"

#include "OverloadMath/FVector2.h"
#include "OverloadMath/FVector3.h"
#include "OverloadMath/FVector4.h"
#include "OverloadMath/FMatrix3.h"
#include "OverloadMath/FMatrix4.h"

#include <DirectXMath.h>

using namespace XusoryEngine;
using namespace OvMaths;
using namespace DirectX;

class MathContrast : public Actor
{
	XS_OBJECT;

public:
	void OnStart() override
	{
		Contrast4();
	}

	void Contrast1()
	{
		Debug::LogInfo("以下是同等情况下Xusory数学库与Overload数学库的常用向量运算对比，运算均执行3亿次\n");
		Vector4 xusoryVector1;
		Vector4 xusoryVector2;
		Vector3 xusoryVector3;
		Vector3 xusoryVector4;
		FVector4 overloadVector1;
		FVector4 overloadVector2;
		FVector3 overloadVector3;
		FVector3 overloadVector4;

		Debug::LogInfo("四维向量的加法运算");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			xusoryVector1 += xusoryVector2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			overloadVector1 += overloadVector2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Overload数学库执行时间：", endTime - beginTime, "\n");


		Debug::LogInfo("四维向量的减法运算");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			xusoryVector1 -= xusoryVector2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			overloadVector1 -= overloadVector2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Overload数学库执行时间：", endTime - beginTime, "\n");
		

		Debug::LogInfo("四维向量与标量的乘法运算");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			xusoryVector1 *= 5;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			overloadVector1 *= 5;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Overload数学库执行时间：", endTime - beginTime, "\n");


		Debug::LogInfo("四维向量与标量的除法运算");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			xusoryVector1 /= 5;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			overloadVector1 /= 5;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Overload数学库执行时间：", endTime - beginTime, "\n");


		Debug::LogInfo("归一化四维向量");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			xusoryVector1.Dot(xusoryVector2);
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			FVector4::Dot(overloadVector1, overloadVector2);
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Overload数学库执行时间：", endTime - beginTime, "\n");


		Debug::LogInfo("求四维向量长度");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			xusoryVector1.Length();
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			FVector4::Length(overloadVector1);
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Overload数学库执行时间：", endTime - beginTime, "\n");


		Debug::LogInfo("三维向量的叉乘");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			Vector3::Cross(xusoryVector3, xusoryVector4);
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			FVector3::Cross(overloadVector3, overloadVector4);
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Overload数学库执行时间：", endTime - beginTime, "\n");
	}

	void Contrast2()
	{
		Debug::LogInfo("以下是同等情况下Xusory数学库与Overload数学库的常用矩阵运算对比，运算均执行1亿次\n");
		Matrix4x4 xusoryMatrix1;
		Matrix4x4 xusoryMatrix2;
		FMatrix4 overloadMatrix1;
		FMatrix4 overloadMatrix2;

		Debug::LogInfo("矩阵的加法运算");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			xusoryMatrix1 += xusoryMatrix2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			overloadMatrix1 += overloadMatrix2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Overload数学库执行时间：", endTime - beginTime, "\n");


		Debug::LogInfo("矩阵的减法运算");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			xusoryMatrix1 -= xusoryMatrix2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			overloadMatrix1 -= overloadMatrix2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Overload数学库执行时间：", endTime - beginTime, "\n");


		Debug::LogInfo("矩阵的乘法运算");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			xusoryMatrix1 *= xusoryMatrix2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			overloadMatrix1 *= overloadMatrix2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Overload数学库执行时间：", endTime - beginTime, "\n");


		Debug::LogInfo("求矩阵行列式");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			xusoryMatrix1.Determinant();
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			FMatrix4::Determinant(overloadMatrix1);
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Overload数学库执行时间：", endTime - beginTime, "\n");


		Debug::LogInfo("求转置矩阵");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			xusoryMatrix1.Transpose();
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			FMatrix4::Transpose(overloadMatrix1);
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Overload数学库执行时间：", endTime - beginTime, "\n");


		Debug::LogInfo("求逆矩阵");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			xusoryMatrix1.Inverse();
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			FMatrix4::Inverse(overloadMatrix1);
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Overload数学库执行时间：", endTime - beginTime, "\n");
	}

	void Contrast3()
	{
		Debug::LogInfo("以下是同等情况下Xusory数学库与微软DirectX数学库的常用向量运算对比，运算均执行3亿次\n");
		Vector4 xusoryVector1;
		Vector4 xusoryVector2;
		Vector3 xusoryVector3;
		Vector3 xusoryVector4;
		XMVECTOR directXVector1{};
		XMVECTOR directXVector2{};

		Debug::LogInfo("四维向量的加法运算");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			xusoryVector1 += xusoryVector2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			directXVector1 += directXVector2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("DirectX数学库执行时间：", endTime - beginTime, "\n");


		Debug::LogInfo("四维向量的减法运算");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			xusoryVector1 -= xusoryVector2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			directXVector1 -= directXVector2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("DirectX数学库执行时间：", endTime - beginTime, "\n");


		Debug::LogInfo("四维向量的乘法运算");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			xusoryVector1 *= xusoryVector2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			directXVector1 *= directXVector2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("DirectX数学库执行时间：", endTime - beginTime, "\n");


		Debug::LogInfo("四维向量的除法运算");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			xusoryVector1 /= xusoryVector2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			directXVector1 /= directXVector2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("DirectX数学库执行时间：", endTime - beginTime, "\n");


		Debug::LogInfo("归一化四维向量");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			xusoryVector1.Dot(xusoryVector2);
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			XMVectorEqual(directXVector1, directXVector2);
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("DirectX数学库执行时间：", endTime - beginTime, "\n");


		Debug::LogInfo("求四维向量长度");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			xusoryVector1.Length();
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			XMVector4Length(directXVector1);
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("DirectX数学库执行时间：", endTime - beginTime, "\n");


		Debug::LogInfo("三维向量的叉乘");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			Vector3::Cross(xusoryVector3, xusoryVector4);
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 3e+8; i++)
		{
			XMVector3Cross(directXVector1, directXVector2);
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("DirectX数学库执行时间：", endTime - beginTime, "\n");
	}

	void Contrast4()
	{
		Debug::LogInfo("以下是同等情况下Xusory数学库与微软DirectX数学库的常用向量运算对比，运算均执行1亿次\n");
		Matrix4x4 xusoryMatrix1;
		Matrix4x4 xusoryMatrix2;
		XMMATRIX directXMatrix1{};
		XMMATRIX directXMatrix2{};

		Debug::LogInfo("矩阵的加法运算");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			xusoryMatrix1 += xusoryMatrix2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			directXMatrix1 += directXMatrix2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("DirectX数学库执行时间：", endTime - beginTime, "\n");


		Debug::LogInfo("矩阵的减法运算");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			xusoryMatrix1 -= xusoryMatrix2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			directXMatrix1 -= directXMatrix2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("DirectX数学库执行时间：", endTime - beginTime, "\n");


		Debug::LogInfo("矩阵的乘法运算");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			xusoryMatrix1 *= xusoryMatrix2;
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			directXMatrix1 = XMMatrixMultiply(directXMatrix1, directXMatrix2);
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("DirectX数学库执行时间：", endTime - beginTime, "\n");


		Debug::LogInfo("求矩阵行列式");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			xusoryMatrix1.Determinant();
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			XMMatrixDeterminant(directXMatrix1);
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("DirectX数学库执行时间：", endTime - beginTime, "\n");


		Debug::LogInfo("求转置矩阵");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			xusoryMatrix1.Transpose();
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			XMMatrixTranspose(directXMatrix1);
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("DirectX数学库执行时间：", endTime - beginTime, "\n");


		Debug::LogInfo("求逆矩阵");
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			xusoryMatrix1.Inverse();
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Xusory数学库执行时间：", endTime - beginTime);

		auto det = XMMatrixDeterminant(directXMatrix1);
		beginTime = PerformanceTime::GetTime();
		for (UINT i = 0; i < 1e+8; i++)
		{
			XMMatrixInverse(&det, directXMatrix1);
		}
		endTime = PerformanceTime::GetTime();
		Debug::LogInfo("Overload数学库执行时间：", endTime - beginTime, "\n");
	}

private:
	DOUBLE beginTime;
	DOUBLE endTime;
};
