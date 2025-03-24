#include "SortingFunctions.h"


bool bubbleSortStep(std::vector<int>& list, int& i, int& j, bool& swapped) // o(n^2)
{
    if (i < list.size() - 1) {
        if (j < list.size() - i - 1) {
            if (list[j] > list[j + 1]) {
                std::swap(list[j], list[j + 1]);
                swapped = true;
            }
            j++;
            return true;  // Continue sorting
        }
        if (!swapped) return false;  // Sorting finished
        j = 0;
        swapped = false;
        i++;
        return true;
    }
    return false; // Sorting finished
}


bool insertionSortStep(std::vector<int>& list, int& i) // O(N^2)
{
    int elementToInserrt;
    int k;
    if (i == 0)
    {
        i++;
        return true; // Continue sorting
    }
    if (i < list.size()) { 
        elementToInserrt = list[i];
        k = i - 1;

        while (k >= 0 && elementToInserrt < list[k])
        {
            list[k + 1] = list[k];
            k--;
           
        }
        list[k + 1] = elementToInserrt;
        i++;
        return true; // Continue sorting
    }
    return false; // Sorting finished
}

bool shellSortStep(std::vector<int>& list, int& n)
{
    if (n == 0)
    {
        return false; // Sorting finished
    }
    int distans = n / 2;
    
    for (int i = distans; i < list.size(); i++)
    {
        int temp = list[i];
        int j;
        for (j = i; j >= distans && list[j - distans] > temp; j -= distans) { // check j reach the beginning of the arrya or we find an element that is less then or equal to temp
            list[j] = list[j - distans];
        }
        list[j] = temp;
    }

    n = n / 2;
    return true; // Continue sorting
}



int Partition(std::vector<int>& arr, int low, int high) // lomuto Partition Algorithm
{
    int pivotElement = arr[high];
    
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivotElement)
        {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    // place the pivot at its correct position
    std::swap(arr[i + 1], arr[high]);

    return i + 1;  // Return pivot index
}

bool QuickSortStep(std::vector<int>& list, std::deque<QuickSortState>& quickSortStack) // O(n log n)
{
    if (quickSortStack.empty())
    {
        return false; // Sorting finished
    }

    QuickSortState quickSortState = quickSortStack.front();
   
    quickSortStack.pop_front();
    if (quickSortState.low < quickSortState.high)
    {
        int pi = Partition(list, quickSortState.low, quickSortState.high);

        quickSortStack.push_back({ pi + 1,  quickSortState.high });
        quickSortStack.push_back({ quickSortState.low, pi - 1 });
    }
   
    return true;
}

bool Mergsort(std::vector<int>& list, std::deque<QuickSortState>& mergSortStack)
{
    if (mergSortStack.empty())
    {
        return false; // Sorting finished
    }
    /* work to be done like adding merging while making sure I can render it GOOD LUCK Future me */ 
    QuickSortState mergSortState = mergSortStack.front();
    mergSortStack.pop_front();
    if (mergSortState.low < mergSortState.high)
    {
        int mid = (mergSortState.low + mergSortState.high) / 2;

        mergSortStack.push_back({ mid +1, mergSortState.high});
        mergSortStack.push_back({ mergSortState.low, mid });

    }

    return true; //  Continue sorting

       
}


