#include "ImGuiHelper.h"

void SetupImGui(HWND windowHandle, ID3D11Device* device, ID3D11DeviceContext* context)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(device, context);
}

void StartImGuiFrame()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}



void EndImGuiFrame()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

int numberInList = 50;
void ImGuiModifying(bool& start, std::vector<int>& numberList, 	// sorting variables 
	int& i,int& j, bool& swapped, int& selectedOption, std::deque<QuickSortState>& quickSortStack, int& n)
{
	bool begun = ImGui::Begin("Modifiers");
	
	if (begun)
	{
		if (ImGui::Button("Start")) start = true;

		if (ImGui::Button("Stop")) start = false;

		ImGui::InputInt("Number in List", &numberInList);
		
		const char* options[] = { "BubbleSort", "InsertionSort", "ShellSort", "QuickSort", "MiracleSort", "BogoSort"};
		static int selectedSort = 0;
		
		// Show the dropdown when the button is clicked
		ImGui::Combo("Options", &selectedSort, options, IM_ARRAYSIZE(options));

		if (!start)
		{
			selectedOption = selectedSort;
		}

		if (ImGui::Button("Reset"))
		{
			selectedOption = selectedSort;
			start = false;
			i = 0;
			j = 0;
			swapped = false;
			numberList.clear();
			for (int i = 0; i < numberInList; i++)
			{
				
				numberList.push_back(rand() % 100 + 1);
			}
			quickSortStack.clear();
			quickSortStack.push_back({ 0, numberInList-1});
			n = numberInList;
		}
	}

	
	ImGui::End();
}
