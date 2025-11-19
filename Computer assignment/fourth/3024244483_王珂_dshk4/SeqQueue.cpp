#include "SeqQueue.h"



SeqQueue::SeqQueue(){
    maxSize = 100;
    queueData = new int[maxSize];
    frontIndex = 0;
    rearIndex = 0;
}

SeqQueue::~SeqQueue(){
    delete[] queueData;
}
void SeqQueue::pop_front(){
    if(frontIndex==rearIndex){
        return;
    }
    frontIndex = (frontIndex + 1) % maxSize;
}
void SeqQueue::push_back(int data){
    if((rearIndex+1)%maxSize == frontIndex){
        return;
    }
    queueData[rearIndex] = data;
    rearIndex = (rearIndex + 1) % maxSize;
}
int SeqQueue::front() const{
    if(frontIndex == rearIndex){
        return 0; 
    }
    return queueData[frontIndex];
}