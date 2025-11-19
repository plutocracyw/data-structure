#include "LinkQueue.h"

LinkQueue::LinkQueue(){
    frontPtr = nullptr;
    rearPtr = nullptr;

}

LinkQueue::~LinkQueue(){
    while(frontPtr != nullptr){
        QNode* temp = frontPtr;
        frontPtr = frontPtr->next;
        delete temp;
    }

}

void LinkQueue::push_back(int data){
    QNode* newNode = new QNode;
    newNode->data = data;
    newNode->next = nullptr;

    if(rearPtr == nullptr){
        frontPtr = newNode;
    }else{
        rearPtr->next = newNode;
    }
    rearPtr = newNode;
}


void LinkQueue::pop_front(){
    if(frontPtr == nullptr){
        return;
    }
    QNode* temp = frontPtr;
    frontPtr = frontPtr->next;
    if(frontPtr == nullptr){
        rearPtr = nullptr;
    }
    delete temp;

}


int LinkQueue::front() const{
    if(frontPtr == nullptr){
        return 0;
    }
    return frontPtr->data;

}