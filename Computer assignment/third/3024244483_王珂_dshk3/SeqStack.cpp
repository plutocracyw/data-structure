/*******************************************************************************
* FileName:         SeqStack.cpp
* Author:           Your_Name
* Student Number:   3022244xxx
* Date:             2023/03/17 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #3
*******************************************************************************/
#include "SeqStack.h"

SeqStack::SeqStack(){
    SeqList = new int[MAX_ELEMENTS];
    data_top = -1;

}
SeqStack::~SeqStack(){
    delete[] SeqList;
}
void SeqStack::push_back(int data){
    if(data_top < MAX_ELEMENTS - 1){
        SeqList[++data_top] = data;
    }
}
int SeqStack::top() const{
    if(data_top >= 0){
        return SeqList[data_top];
    }
    return 0;
}
void SeqStack::pop(){
    if(data_top >= 0){
        --data_top;
    }
    return ;
}