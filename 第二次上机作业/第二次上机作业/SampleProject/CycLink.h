//自行实现循环链表
#ifndef CYCLINK_H
#define CYCLINK_H

class CycLink
{
private:
    struct Cycnode{
        int value;
        Cycnode* next;
    };
    Cycnode* head;
    int len;

public:
    CycLink();
    int length() const;
    int getData(const int& location) const;
    void insert(const int &data, const int& location);
    bool remove(const int& location);
    void converse();
    void append(const CycLink& append_list);
    ~CycLink();
};
#endif // CYCLINK_H