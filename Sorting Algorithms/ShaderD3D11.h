#pragma once
#include <d3d11_4.h>
#include <array>
#include <string>



enum class ShaderType
{
	VERTEX_SHADER,
	HULL_SHADER,
	DOMAIN_SHADER,
	GEOMETRY_SHADER,
	PIXEL_SHADER,
	COMPUTE_SHADER
};

class ShaderD3D11
{
private:

	ShaderType type;

	union
	{
		ID3D11VertexShader* vertex = nullptr;
		ID3D11HullShader* hull;
		ID3D11DomainShader* domain;
		ID3D11GeometryShader* geometry;
		ID3D11PixelShader* pixel;
		ID3D11ComputeShader* compute;
	} shader;

	ID3DBlob* shaderBlob = nullptr;

public:
	ShaderD3D11() = default;
	~ShaderD3D11();
	ShaderD3D11(ID3D11Device* device, ShaderType shaderType, const void* dataPtr, size_t dataSize);
	ShaderD3D11(ID3D11Device* device, ShaderType shaderType, std::wstring csoPath);

	ShaderD3D11(const ShaderD3D11& other) = delete;
	ShaderD3D11& operator=(const ShaderD3D11& other) = delete;
	ShaderD3D11(ShaderD3D11&& other) = delete;
	ShaderD3D11& operator=(ShaderD3D11&& other) = delete;

	void Initialize(ID3D11Device* device, ShaderType shaderType, const void* dataPtr, size_t dataSize);
	void Initialize(ID3D11Device* device, ShaderType shaderType, std::wstring csoPath);


	ID3D11ComputeShader* GetComputeShader();
	const void* GetShaderByteData() const;
	size_t GetShaderByteSize() const;

	void BindShader(ID3D11DeviceContext* context) const;
};