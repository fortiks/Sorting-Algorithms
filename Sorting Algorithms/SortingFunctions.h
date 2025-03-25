#pragma once
#include <vector>
#include <deque>

enum class sortingInUse {
	bubbleSort

};

struct QuickSortState {
	int low, high;
};

bool bubbleSortStep(std::vector<int>& list, int& i, int& j, bool& swapped);

bool insertionSortStep(std::vector<int>& list, int& i); // best O(N)  Worst O(N^2)

bool shellSortStep(std::vector<int>& list, int& n);

bool QuickSortStep(std::vector<int>& list, std::deque<QuickSortState>& quickSortStack); // O(nlogn)

bool Mergsort(std::vector<int>& list, std::deque<QuickSortState>& mergSortStack); // not done

// for fun algorithms algoritms
bool miracleSort(std::vector<int>& list, int& i, int& j, bool& swapped, int& n, std::deque<QuickSortState>& quickSortStack);
bool bogoSortStep(std::vector<int>& list);