/*******************************************************************************
* FileName:         LinkStack.cpp
* Author:           Your_Name
* Student Number:   3022244xxx
* Date:             2022/03/16 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #3
*******************************************************************************/


#include "LinkStack.h"


LinkStack::LinkStack(){
    head = nullptr;
    length = 0;
}
LinkStack::~LinkStack(){
    StackNode* current = head;
    while(current != nullptr){
        StackNode* temp = current;
        current = current->next;
        delete temp;
    }
}

void LinkStack::push_back(int data){
    StackNode* newNode = new StackNode;
    newNode->value = data;
    newNode->next = head;
    head = newNode;
    length++;
}

int LinkStack::top() const{
    if(head == nullptr){
        return 0;
    }
    return head->value;
}

void LinkStack::pop(){
    if(head != nullptr){
        StackNode* temp = head;
        head = head->next;
        delete temp;
        length--;
    }
    return;
}