#pragma once

#include "../../Core/Core.h"

namespace XusoryEngine
{
	DLL_CLASS(IShaderLoader)
	{
	public:
		IShaderLoader() = default;
		DELETE_COPY_OPERATOR(IShaderLoader);
		DELETE_MOVE_OPERATOR(IShaderLoader);
		virtual ~IShaderLoader() = default;

		virtual void LoadShader(Shader* shader, const std::wstring_view& path) = 0;
	};

	DLL_CLASS(DxShaderLoader) : public IShaderLoader
	{
	public:
		void LoadShader(Shader* shader, const std::wstring_view& path) override;
		CREATE_FACTORY(IShaderLoader, DxShaderLoader);
	};

	typedef FactoryBase<IShaderLoader> ShaderLoaderFactory;
	REGISTER_FACTORY(ShaderLoaderFactory, DxShaderLoader, TEXT("hlsl"));
}
