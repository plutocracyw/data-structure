#include "CycLink.h"
#include <cstddef>

CycLink::CycLink(){
    head = NULL;
}

CycLink::~CycLink(){
    if (head == NULL)
        return;
    Cycnode *p = head->next;
    head->next = NULL; //打破循环
    while (p != NULL)
    {
        Cycnode *temp = p;
        p = p->next;
        delete temp;
    }
    head = NULL;
}

int CycLink::length() const{
    if (head == NULL)
        return 0;
    int len=1; //从head开始计数
    Cycnode* p=head->next;
    while(p != head){
        len++;
        p=p->next;    //移动指针直到回到head
    }
    return len;
}

int CycLink::getData(const int& location) const{
    if (head == NULL)
        return -1; //空链表
    Cycnode* p=head;
    int index=0;
    while(index < location){
        p=p->next;
        index++;  //移动指针直到location位置
        if (p == head) //回到head，说明location超出范围
            return -1;
    }
    return p->value;
}

void CycLink::insert(const int& data, const int& location){
    Cycnode* q = new Cycnode;
    q->value=data;
    if(head==NULL){
        //空链表，插入第一个节点
        head=q;
        q->next=head; //指向自己形成循环
    }
    else if(location==0){
        //在头部插入
        Cycnode* tail=head;
        while(tail->next != head){
            tail=tail->next; //找到尾节点
        }
        q->next=head;
        head=q;
        tail->next=head; //更新尾节点的next指向新head
    }
    else{
        Cycnode* p = head;
        int index = 0;
        while(index < location - 1){
            p = p->next;
            index++;
            if (p == head) //回到head，说明location超出范围，插入到末尾
                break;
        }
        q->next=p->next;
        p->next=q;
    }
}

bool CycLink::remove(const int &location){
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
        // 删除头节点
        if (head->next == head)
        {
            // 只有一个节点
            delete head;
            head = NULL;
        }
        else
        {
            Cycnode *tail = head;
            while (tail->next != head)
            {
                tail = tail->next; // 找到尾节点
            }
            Cycnode *temp = head;
            head = head->next;
            tail->next = head; // 更新尾节点的next指向新head
            delete temp;
        }
        return true;
    }
    else
    {
        Cycnode *p = head;
        int index = 0;
        // 找到第location-1个节点
        while (index < location - 1)
        {
            p = p->next;
            index++;
            if (p == head) // 回到head，说明location超出范围
                return false;
        }
        // 若p的下一个节点是head，说明location超出范围
        if (p->next == head)
        {
            return false;
        }
        // 正常删除
        Cycnode *temp = p->next;
        p->next = temp->next;
        delete temp;
        return true;
    }
}

void CycLink::converse(){
    if (head == NULL || head->next == head)
        return; // 空链表或只有一个节点，无需翻转

    Cycnode *prev = head;
    Cycnode *current = head->next;
    Cycnode *nextNode;

    while (current != head)
    {
        nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    }
    // 最后处理head节点
    head->next = prev;
    head = prev; // 更新head指向新的头节点
}

void CycLink::append(const CycLink &append_list){
    if (append_list.head == NULL)
        return; // 追加的链表为空，无需操作

    if (head == NULL)
    {
        // 当前链表为空，直接将append_list赋值给当前链表
        head = append_list.head;
    }
    else
    {
        // 找到当前链表的尾节点
        Cycnode *tail1 = head;
        while (tail1->next != head)
        {
            tail1 = tail1->next;
        }
        // 找到追加链表的尾节点
        Cycnode *tail2 = append_list.head;
        while (tail2->next != append_list.head)
        {
            tail2 = tail2->next;
        }
        // 连接两个链表
        tail1->next = append_list.head;
        tail2->next = head;
    }
}