/*******************************************************************************
* FileName:         MySort.cpp
* Author:           Your_name
* Student Number:   Student_Number
* Date:             2023/06/03 09:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #17
*******************************************************************************/

#include "MySort.h"
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>

void merge(int *arr, int left, int mid, int right){
    int n1 = mid-left+1;
    int n2 = right-mid;

    int* leftArr = new int[n1];
    int* rightArr = new int[n2];

    for(int i=0; i<n1; i++)
        leftArr[i] = arr[left+i];
    for(int j=0; j<n2; j++)
        rightArr[j] = arr[mid+1+j];

    int i=0, j=0, k=left;
    while(i<n1 && j<n2){
        if(leftArr[i] <= rightArr[j]){
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while(j<n2){
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

void mergeSortHelper(int *arr, int left, int right){
    if(left < right){
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSort(int *arr, int len){
    if(len <= 1 || arr == nullptr) 
        return;
    mergeSortHelper(arr, 0, len - 1);
}

int getDigit(int number, int d){
    return (number>>(d*4)) & 0xF;
}

int countingSortByDigit(int* arr, int len, int d){
    const int RADIX = 16;
    std::vector<int> count(RADIX, 0);
    std::vector<int> output(len);

    for(int i=0; i<len; i++){
        int digit = getDigit(arr[i], d);
        count[digit]++;
    }

    for(int i=1; i<RADIX; i++){
        count[i] += count[i-1];
    }

    for(int i=len-1; i>=0; i--){
        int digit = getDigit(arr[i], d);
        output[count[digit]-1] = arr[i];
        count[digit]--;
    }

    for(int i=0; i<len; i++){
        arr[i] = output[i];
    }
}

void cardSort(int* arr, int len){
    if(len <= 1 || arr == nullptr) 
        return;

    int maxVal=arr[0];
    for(int i=1; i<len; i++){
        if(arr[i] > maxVal)
            maxVal = arr[i];
    }

    const int TOTAL_DIGITS = 8; // Since we are using 32-bit integers and base 16
    for(int d=0; d<TOTAL_DIGITS; d++){
        countingSortByDigit(arr, len, d);
    }
    
}