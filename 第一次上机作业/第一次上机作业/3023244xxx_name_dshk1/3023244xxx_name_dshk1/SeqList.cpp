/*******************************************************************************
* FileName:         SeqList.cpp
* Author:           XXX
* Student Number:   3022218126
* Date:             2023/02/23 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #1
*                   作业在这个文件中完成，需要补全SeqList类的实现，
*                   给出了构造函数与析构函数的例子.
*                   写明必要的注释
*******************************************************************************/

#include "SeqList.h"

/*
    使用初始化列表来初始化const变量LIST_SIZE，
    并动态分配LIST_SIZE长度的数组。
*/
SeqList::SeqList(const int& listSize) :LIST_SIZE(listSize)
{
    seq = new int[LIST_SIZE];
    // equal to:  seq = (int*) malloc(sizeof(int) * LIST_SIZE);
    len = 0;
}

SeqList::~SeqList(){
    delete[] seq;
}

bool SeqList::isIn(const int& data){
}

int SeqList::length(){

}

int SeqList::getData(const int& location){
}

bool SeqList::insert(const int& data, const int& location){
}

bool SeqList::remove(const int& location){
}
