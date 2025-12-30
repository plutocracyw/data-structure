/*******************************************************************************
 * FileName:         myHash.h
 * Author:           Your_name
 * Student Number:   Student_Number
 * Date:             2025/12/29 09:24:55
 * Version:          v1.0
 * Description:      Data Structure Experiment #15
 *******************************************************************************/

#ifndef MYHASH_H
#define MYHASH_H

class MyHash
{
private:
    // 哈希表结构，包含键、值和一个标记是否被占用的标志
    struct HashNode
    {
        int key;
        int value;
        bool occupied; // 标记该位置是否被占用
        HashNode() : key(0), value(0), occupied(false) {}
    };

    HashNode *table;     // 哈希表数组
    int tableSize;       // 哈希表实际大小
    int maxElements;     // 最大元素个数
    int currentElements; // 当前元素个数
    int prime;           // 接近表长的质数

    // 获取下一个素数
    int getNextPrime(int n);
    // 线性探测解决冲突
    int linearProbing(int key, bool forInsert = true);

public:
    /**
     *  声明一个哈希表，哈希表中元素最多为max_element个。
        @name MyHash(int max_element)
        @param arg1  哈希表对最大元素个数
        @return
    */
    MyHash(int max_element);

    /**
     *  析构函数
        @name
        @param
        @return
    */
    ~MyHash();

    /**
     *  获取哈希表中键值为key的元素的值。
        @name int getvalue(int);
        @param  arg1 需要获取值的主键
        @return int 对应key值储存的结果
    */
    int getvalue(int key);

    /**
     *  将哈希表中键值为key的值设定为value。
        @name void setvalue(int, int);
        @param  arg1 需要设定的键值key
        @param  arg2 需要被设定的值value
        @return void
    */
    void setvalue(int key, int value);
};

#endif