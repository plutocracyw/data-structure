/*******************************************************************************
* FileName:         MySort.cpp
* Author:           Your_name
* Student Number:   Student_Number
* Date:             2023/05/26 09:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #16
*******************************************************************************/

#include "MySort.h"
#include <algorithm>

void MySort::bubbleSort(int* arr, int len){
    if(arr==nullptr || len<=0){
        return;
    }

    for (int i = 0; i < len - 1;i++){
        bool swapped = false;
        for (int j = 0; j < len - 1 - i;j++){
            if(arr[j]>arr[j+1]){
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if(!swapped){
            break;
        }
    }
}

int partition(int* arr, int low, int high){
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high;j++){
        if(arr[j]<pivot){
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortHelper(int* arr, int low, int high){
    if(low<high){
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}
void MySort::quickSort(int* arr, int len){
    if(arr==nullptr || len <=1)
        return;
    quickSortHelper(arr, 0, len - 1);
}

void heapify(int* arr, int len, int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < len && arr[left] > arr[largest]){
        largest = left;
    }
    if(right < len && arr[right] > arr[largest]){
        largest = right;
    }
    if(largest != i){
        std::swap(arr[i], arr[largest]);
        heapify(arr, len, largest);
    }
}

void MySort::heapSort(int* arr, int len){
    if(arr==nullptr || len <=1)
        return;

    for (int i = len / 2 - 1; i >= 0;i--){
        heapify(arr, len, i);
    }

    for (int i = len - 1; i > 0;i--){
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}