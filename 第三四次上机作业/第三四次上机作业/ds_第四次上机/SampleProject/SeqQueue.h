/*******************************************************************************
* FileName:         SeqStack.h
* Author:           your_name
* Student Number:   3022244xxx
* Date:             2023/03/17 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #4
*                   待完成的SeqQueue.h文件
*******************************************************************************/

#ifndef SEQQUEUE_H
#define SEQQUEUE_H

#include "MyQueue.h"

class SeqQueue: public MyQueue{
private:
    int *queueData;
    int frontIndex;
    int rearIndex;
    int maxSize;

public:
    SeqQueue();
    virtual ~SeqQueue();
    void pop_front();
    void push_back(int data);
    int front() const;
};
#endif