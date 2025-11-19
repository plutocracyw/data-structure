/*******************************************************************************
* FileName:         LinkStack.h
* Author:           XXX
* Student Number:   30222XXXXX
* Date:             2023/03/16 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #3
*******************************************************************************/
#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "MyStack.h"

class LinkStack: public MyStack{
    private:
    struct StackNode{
        StackNode* next;
        int value;
    };
    StackNode* head;
    int length;
    public:
        LinkStack();
        virtual ~LinkStack(); 
        void push_back(int data);
        int top() const;
        void pop();
};

#endif