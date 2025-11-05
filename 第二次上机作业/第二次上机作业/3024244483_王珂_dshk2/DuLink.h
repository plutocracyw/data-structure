// 自行实现双向链表
#ifndef DULIST_H
#define DULIST_H

class DuLink
{
private:
    struct DuNode{
        int value;
        DuNode* next;
        DuNode* prev;
    };
    DuNode* head;
    int len;

public:
    DuLink();
    int length() const;
    int getData(const int& location) const;
    void insert(const int &data, const int& location);
    bool remove(const int& location);
    void converse();
    void append(const DuLink& append_list);
    ~DuLink();
};

#endif // DULIST_H