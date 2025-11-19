#include "DuLink.h"
#include <cstddef>

DuLink::DuLink(){
    head = NULL;
}

DuLink::~DuLink(){
    DuNode *p = head;
    while (p != NULL)
    {
        DuNode *temp = p;
        p = p->next;
        delete temp;
    }
    head = NULL;
}

int DuLink::length() const{
    int len=0;
    DuNode* p=head;
    while(p != NULL){
        len++;
        p=p->next;    //移动指针直到链表末尾
    }
    return len;
}

int DuLink::getData(const int& location) const{
    DuNode* p=head;
    int index=0;
    while(p != NULL && index < location){
        p=p->next;
        index++;  //移动指针直到location位置
    }
    if(p != NULL){
        return p->value;
    }
    return -1; //如果location位置不存在，返回-1表示错误
}

void DuLink::insert(const int& data, const int& location){
    DuNode* q = new DuNode;
    q->value=data;
    q->next=NULL;
    q->prev=NULL;
    if(location==0)
    {
        q->next=head;
        if(head != NULL){
            head->prev=q;
        }
        head=q;
    }
    else{
        DuNode* p = head;
        int index = 0;
        while(p != NULL && index < location - 1){
            p = p->next;
            index++;  
        }
        if(p!=NULL){
            q->next = p->next;
            q->prev = p;
            if(p->next != NULL){
                p->next->prev = q;
            }
            p->next = q;
        }
        else{
            delete q;
        }
    }
    
}

bool DuLink::remove(const int &location){
    if(head==NULL){
        return false;
    }
    DuNode* p=head;
    if(location==0){
        head=head->next;
        if(head != NULL){
            head->prev=NULL;
        }
        delete p;
        return true;
    }
    else{
        int index=0;
        while(p != NULL && index < location){
            p=p->next;
            index++;
        }   
        if(p != NULL){
            p->prev->next=p->next;
            if(p->next != NULL){
                p->next->prev=p->prev;
            }
            delete p;
            return true;
        }
    }
}

void DuLink::converse(){
    DuNode* current = head;
    DuNode* temp = NULL;
    while (current != NULL)
    {
        // 交换next和prev指针
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        // 移动到下一个节点（原来的prev节点）
        current = current->prev;
    }
    if (temp != NULL)
    {
        head = temp->prev;
    }
}

void DuLink::append(const DuLink& append_list){
    DuNode *p = append_list.head;
    while (p != NULL)
    {
        insert(p->value, length());
        p = p->next;
    }
}