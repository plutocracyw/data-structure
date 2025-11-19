/*******************************************************************************
* FileName:         LinkList.cpp
* Author:           Your_Name
* Student Number:   3022244xxx
* Date:             2023/02/26 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #2
*                   作业在这个文件中完成，需要补全LinkList类的实现，
*                   写明必要的注释
*******************************************************************************/

#include "LinkList.h"
#include <cstddef>

LinkList::LinkList(){
    head=NULL;
}

LinkList::~LinkList(){
    node *p = head;
    while (p != NULL)
    {
        node *temp = p;
        p = p->next;
        delete temp;
    }
    head = NULL;
}

int LinkList::length() const{
    int len=0;
    node* p=head;
    while(p != NULL){
        len++;
        p=p->next;    //移动指针直到链表末尾
    }
    return len;
}

int LinkList::getData(const int& location) const{
    node* p=head;
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

void LinkList::insert(const int& data, const int& location){
    node *q = new node;
    q->value = data;
    if(location==0){
        q->next = head;
        head = q;
    }
    else{
        node *p = head;
        int index = 0;
        while(p != NULL && index < location - 1){
            p = p->next;
            index++;  //移动指针直到location-1位置
        }
        if(p != NULL){
            q->next = p->next;
            p->next = q;
        }
        else{
            delete q; 
        }
    }
}

bool LinkList::remove(const int &location)
{
    if (head == NULL)
    {
        return false; // 空链表，无法删除
    }
    if (location < 0)
    {
        return false; // 位置无效（负数）
    }
    if (location == 0)
    {
        node *temp = head;
        head = head->next;
        delete temp;
        return true;
    }
    else
    {
        node *p = head;
        int index = 0;
        // 找到第location-1个节点
        while (p != NULL && index < location - 1)
        {
            p = p->next;
            index++;
        }
        // 若p不存在，或p的下一个节点不存在（即location超出范围），返回false
        if (p == NULL || p->next == NULL)
        {
            return false;
        }
        // 正常删除
        node *temp = p->next;
        p->next = temp->next;
        delete temp;
        return true;
    }
}
void LinkList::converse(){
    node* prev = NULL;
    node* current = head;
    node* after = NULL;
    while(current != NULL){
        after = current->next; //保存下一个节点
        current->next = prev; //反转当前节点的指针
        prev = current;
        current = after; // 移动prev和current指针
    }
    head = prev; //更新头指针
}

void LinkList::append(const LinkList& append_list){
    node *p = append_list.head;
    while (p != NULL)
    {
        insert(p->value, length());
        p = p->next;
    }
}