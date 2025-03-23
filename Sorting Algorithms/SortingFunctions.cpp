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
    if (i < list.size()) { // list.size() - 1 vector start form 0 
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

int Partition(std::vector<int>& arr, int low, int high) // lomuto Partition Algorithm
{
    int pivotElement = arr[high];
    
    int i = low - 1;

    for (int j = low; j < high-1; j++)
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

bool QuickSortStep(std::vector<int>& list, int low, int high) // O(n log n)
{

    // not done!! need to figure out how to split it probly with an struct that hold the low and high where 
    // 1 I call it two time each loop for rendering   Tested (will not work )
    /*   2  next idea create an std::vector that hold all all quickSort states that I will pop once every turn
  
       std::vector<QuickSortState> quickSortStack
       QuickSortState quickSortState =  quickSortStack.pop() 
       int pi = Partition(list, low, high);
       quickSortStack.push({ pi + 1, high });
       quickSortStack.push({ low, pi - 1 }); 

     */
    // NOT DONE JUST A theory that I will explore when I feel like it
       
    if (low < high)
    {
        int pi = Partition(list, low, high);
        
    }

    return false;
}


