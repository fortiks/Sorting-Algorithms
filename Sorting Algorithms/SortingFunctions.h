#pragma once
#include <vector>

enum class sortingInUse {
	bubbleSort

};

struct QuickSortState {
	int low, high;
};

bool bubbleSortStep(std::vector<int>& list, int& i, int& j, bool& swapped);

bool insertionSortStep(std::vector<int>& list, int& i); // best O(N)  Worst O(N^2)

bool QuickSortStep(std::vector<int>& list, int low, int high);