/*******************************************************************************
* FileName:         SPMatrix.cpp
* Author:           Your_name
* Student Number:   3022244XXX
* Date:             2023/03/30 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #6
*
*******************************************************************************/

#include "SPMatrix.h"
#include <iostream>
#include <algorithm>

int SPMatrix::findPosition(int i, int j) const{
    int left = 0;
    int right = num_elements - 1;
    while(left <= right){
        int mid = left + right / 2;
        if(data[mid].row == i && data[mid].col == j){
            return mid;
        }
        else if(data[mid].row < i || (data[mid].row == i && data[mid].col < j)){
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    return -1;
}

void SPMatrix::insertElement(int i, int j, int val){
    if(num_elements >= max_elements){
        resize(max_elements * 2);
    }

    int pos = 0;
    while(pos < num_elements && (data[pos].row < i || (data[pos].row == i && data[pos].col < j))){
        pos++;
    }

    for(int k = num_elements; k > pos; k--){
        data[k] = data[k - 1];
    }
    data[pos].row = i;
    data[pos].col = j;
    data[pos].val = val;
    num_elements++;
}

void SPMatrix::removeElement(int pos){
    if(pos < 0 || pos >= num_elements){
        return;
    }

    for(int k = pos; k < num_elements - 1; k++){
        data[k] = data[k + 1];
    }
    num_elements--;
}

void SPMatrix::sortElements(){
    std::sort(data, data + num_elements, [](const Triple& a, const Triple& b){
        if(a.row != b.row){
            return a.row < b.row;
        }
        return a.col < b.col;
    });
}

void SPMatrix::resize(int new_max){
    Triple* new_data = new Triple[new_max];
    for(int i = 0; i < num_elements; i++){
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    max_elements = new_max;
}

SPMatrix::SPMatrix(int r, int c){
    rows = r;
    cols = c;
    max_elements = 100;
    data = new Triple[max_elements];
    num_elements = 0;
}

SPMatrix::SPMatrix(int r, int c, int max_element){
    rows = r;
    cols = c;
    max_elements = max_element;
    data = new Triple[max_elements];
    num_elements = 0;
}

int SPMatrix::get(int i, int j)const{
    int pos = findPosition(i, j);
    if(pos != -1){
        return data[pos].val;
    }
    return 0;
}

void SPMatrix::set(int i, int j, int val){
    int pos = findPosition(i, j);
    if(pos != -1){
        if(val == 0){
            removeElement(pos);
        }
        else{
            data[pos].val = val;
        }
    }
    else{
        if(val != 0){
            insertElement(i, j, val);
        }
    }
}

void SPMatrix::rotate(){
    SPMatrix temp(cols, rows, max_elements);

    for(int i = 0; i < num_elements; i++){
        temp.insertElement(data[i].col, data[i].row, data[i].val);
    }

    std::swap(rows, cols);
    delete[] data;
    data = temp.data;
    num_elements = temp.num_elements;
    max_elements = temp.max_elements;
    temp.data = nullptr;
    temp.num_elements = 0;
}

SPMatrix SPMatrix::operator+(const SPMatrix& b){
    if(rows != b.rows || cols != b.cols){
        throw std::invalid_argument("Matrix dimensions must agree for addition.");
    }

    SPMatrix result(rows, cols, max_elements+b.max_elements);

    int i = 0, j = 0;
    while(i < num_elements && j < b.num_elements){
        if(data[i].row < b.data[j].row || (data[i].row == b.data[j].row && data[i].col < b.data[j].col)){
            result.insertElement(data[i].row, data[i].col, data[i].val);
            i++;
        }
        else if(data[i].row > b.data[j].row || (data[i].row == b.data[j].row && data[i].col > b.data[j].col)){
            result.insertElement(b.data[j].row, b.data[j].col, b.data[j].val);
            j++;
        }
        else{
            int summed_val = data[i].val + b.data[j].val;
            if(summed_val != 0){
                result.insertElement(data[i].row, data[i].col, summed_val);
            }
            i++;
            j++;
        }
    }

    while(i < num_elements){
        result.insertElement(data[i].row, data[i].col, data[i].val);
        i++;
    }

    while(j < b.num_elements){
        result.insertElement(b.data[j].row, b.data[j].col, b.data[j].val);
        j++;
    }

    return result;
}

SPMatrix SPMatrix::operator-(const SPMatrix& b){
    if(rows != b.rows || cols != b.cols){
        throw std::invalid_argument("Matrix dimensions must agree for subtraction.");
    }

    SPMatrix result(rows, cols, max_elements+b.max_elements);

    int i = 0, j = 0;
    while(i < num_elements && j < b.num_elements){
        if(data[i].row < b.data[j].row || (data[i].row == b.data[j].row && data[i].col < b.data[j].col)){
            result.insertElement(data[i].row, data[i].col, data[i].val);
            i++;
        }
        else if(data[i].row > b.data[j].row || (data[i].row == b.data[j].row && data[i].col > b.data[j].col)){
            result.insertElement(b.data[j].row, b.data[j].col, -b.data[j].val);
            j++;
        }
        else{
            int diff_val = data[i].val - b.data[j].val;
            if(diff_val != 0){
                result.insertElement(data[i].row, data[i].col, diff_val);
            }
            i++;
            j++;
        }
    }

    while(i < num_elements){
        result.insertElement(data[i].row, data[i].col, data[i].val);
        i++;
    }

    while(j < b.num_elements){
        result.insertElement(b.data[j].row, b.data[j].col, -b.data[j].val);
        j++;
    }

    return result;
}

SPMatrix SPMatrix::operator*(const SPMatrix& b){
    if(cols != b.rows){
        throw std::invalid_argument("Matrix dimensions must agree for multiplication.");
    }

    SPMatrix result(rows, b.cols, max_elements * b.max_elements);

    for(int i = 0; i < num_elements; i++){
        for(int j = 0; j < b.num_elements; j++){
            if(data[i].col == b.data[j].row){
                int r = data[i].row;
                int c = b.data[j].col;
                int val = data[i].val * b.data[j].val;
                int existing_pos = result.findPosition(r, c);
                if(existing_pos != -1){
                    result.data[existing_pos].val += val;
                    if(result.data[existing_pos].val == 0){
                        result.removeElement(existing_pos);
                    }
                }
                else{
                    result.insertElement(r, c, val);
                }
            }
        }
    }

    return result;
}

SPMatrix::~SPMatrix(){
    delete[] data;
}