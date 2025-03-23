// buffers
#include "VertexBufferD3D11.h"
#include "ConstantBufferD3D11.h"
#include "StructuredBufferD3D11.h"


#include "InputLayoutD3D11.h"
#include "ShaderD3D11.h"
#include "WindowHelper.h"
#include "D3D11Setup.h"
#include "IMGuiHelper.h"
#include "SortingFunctions.h"


#include <Windows.h>

// time
#include <chrono>
#include <thread> 


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	const UINT WIDTH = 1024;
	const UINT HEIGHT = 576;
	HWND window;

	if (!SetupWindow(hInstance, WIDTH, HEIGHT, nCmdShow, window))
	{
		MessageBoxW(NULL, L"Failed to setup window!", L"Error", MB_ICONERROR);
		return -1;
	}


	ID3D11Device* device;
	ID3D11DeviceContext* immediateContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* rtv;
	ID3D11Texture2D* dsTexture;
	ID3D11DepthStencilView* dsView;
	D3D11_VIEWPORT viewport;

	if (!SetupD3D11(WIDTH, HEIGHT, window, device, immediateContext, swapChain, rtv, dsTexture, dsView, viewport))
	{
		MessageBoxW(NULL, L"Failed to setup d3d11!", L"Error", MB_ICONERROR);
		return -1;
	}

	SetupImGui(window, device, immediateContext);
	

	ShaderD3D11 pixelShader;
	pixelShader.Initialize(device,
		ShaderType::PIXEL_SHADER, L"..\\x64\\Debug\\PixelShader.cso");

	ShaderD3D11 vertexShader;
	vertexShader.Initialize(device,
		ShaderType::VERTEX_SHADER, L"..\\x64\\Debug\\VertexShader.cso");

	InputLayoutD3D11 inputLayout;
	inputLayout.AddInputElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
	inputLayout.FinalizeInputLayout(device, vertexShader.GetShaderByteData(), vertexShader.GetShaderByteSize());

	DirectX::XMFLOAT3 position[6] = {
		// First Triangle
		{ -0.5f,  0.5f, 0.0f}, // Top Left
		{  0.5f,  0.5f, 0.0f}, // Top Right
		{  0.5f, -0.5f, 0.0f}, // Bottom Right

		// Second Triangle
		{  0.5f, -0.5f, 0.0f}, // Bottom Right
		{ -0.5f, -0.5f, 0.0f}, // Bottom Left
		{ -0.5f,  0.5f, 0.0f}  // Top Left
	};
		
	

	VertexBufferD3D11 vertexBuffer(device, sizeof(DirectX::XMFLOAT3), 6, position);

	std::vector<int> numberList;
	for (int i = 0; i < 50; i++)
	{
		numberList.push_back(rand() % 100 + 1);
	}

	float minHeightScale = 0.1f;  // Smallest size (for heightFactor = 1)
	float maxHeightScale = 1.8f;  // Largest size (for heightFactor = 100)
	int testNumber = numberList[0];
	float scaleY = minHeightScale + (testNumber - 1) / (100.0f - 1) * (maxHeightScale - minHeightScale);
	float translateY = (scaleY - minHeightScale) * 0.5f - 0.98;  
	DirectX::XMMATRIX transform = DirectX::XMMatrixScaling(0.1, scaleY, 0) * DirectX::XMMatrixTranslation(-0.8, translateY, 0);
	DirectX::XMMATRIX updatedMatrix = transform;
	ConstantBufferD3D11 constantVsBuffer(device, sizeof(DirectX::XMMATRIX), &transform);
	float screenWidth = 1.98f;  // Assuming NDC (-1 to 1), so total width is 2
	bool start = 0;
	

	// sorting variables 
	int i = 0, j = 0;
	bool swapped = false;
	
	int sortingAlgorithmInUSe = 0;

	MSG msg = { };
	std::chrono::duration<float> dt; // time
	auto startTime = std::chrono::high_resolution_clock::now();
	
	float speed = 1.0f;
	auto endTime = std::chrono::high_resolution_clock::now();
	while (!(GetKeyState(VK_ESCAPE) & 0x8000) && msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		StartImGuiFrame();
		ImGuiModifying(start, numberList, i, j, swapped, sortingAlgorithmInUSe);

		

		// === Render === 
		float clearColour[4] = { 0, 0, 0, 0 };
		immediateContext->ClearRenderTargetView(rtv, clearColour);
		immediateContext->ClearDepthStencilView(dsView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
		ID3D11Buffer* VertexBuffer = vertexBuffer.GetBuffer();
		UINT stride = vertexBuffer.GetVertexSize();
		UINT offset = 0;
		immediateContext->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
		immediateContext->IASetInputLayout(inputLayout.GetInputLayout());
		immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		vertexShader.BindShader(immediateContext);
		pixelShader.BindShader(immediateContext);

		float gapSize = 0.01f;  // Adjust this for the desired gap size
		float rectWidth = (screenWidth) / numberList.size(); // 0.2 for the sides

		// 
		if (start == true)
		{
			if (sortingAlgorithmInUSe ==  0)
			{
				start = bubbleSortStep(numberList, i, j, swapped);

			}
			else if (sortingAlgorithmInUSe == 1)
			{
				start = insertionSortStep(numberList, i);
			}
			

			
			
		}
	
		for (int i = 0; i < numberList.size(); i++)
		{
			updatedMatrix = transform;
			scaleY = minHeightScale + (numberList[i] - 1) / (100.0f - 1) * (maxHeightScale - minHeightScale); // learp between max and min
			translateY = (scaleY - minHeightScale) * 0.5f; // scale upwards only
			float xPos = -1.0f + (i * rectWidth + gapSize) + (rectWidth / 2.0f); // Centered positions  (rectWidth / 2.0f) so that it does not go outside

			updatedMatrix = DirectX::XMMatrixScaling(rectWidth, scaleY, 0) * DirectX::XMMatrixTranslation(xPos, translateY - 0.92, 0);
			updatedMatrix = DirectX::XMMatrixTranspose(updatedMatrix);
			constantVsBuffer.UpdateBuffer(immediateContext, &updatedMatrix, sizeof(updatedMatrix));

			ID3D11Buffer* ConstantBuffer = constantVsBuffer.GetBuffer();
			immediateContext->VSSetConstantBuffers(0, 1, &ConstantBuffer);
			immediateContext->RSSetViewports(1, &viewport);
			immediateContext->OMSetRenderTargets(1, &rtv, dsView);

			immediateContext->Draw(6, 0);
		}
		
		EndImGuiFrame();
		swapChain->Present(1, 0);

		endTime = std::chrono::high_resolution_clock::now();
		
	}

	dsView->Release();
	dsTexture->Release();
	rtv->Release();
	swapChain->Release();
	immediateContext->Release();
	device->Release();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	return 0;
}