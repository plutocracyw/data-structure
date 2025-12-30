/*******************************************************************************
 * FileName:         myHash.cpp
 * Author:           Your_name
 * Student Number:   Student_Number
 * Date:             2025/12/29 09:24:55
 * Version:          v1.0
 * Description:      Data Structure Experiment #15
 *******************************************************************************/

#include "myHash.h"
#include <cmath>
#include <iostream>

// 判断是否为质数
bool isPrime(int n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// 获取大于等于n的下一个质数
int MyHash::getNextPrime(int n)
{
    while (!isPrime(n))
    {
        n++;
    }
    return n;
}

MyHash::MyHash(int max_element)
{
    maxElements = max_element;
    currentElements = 0;

    // 根据提示，表长设置为max_element的整数倍，这里设为2倍
    tableSize = maxElements * 2;

    // 获取接近表长的质数作为mod
    prime = getNextPrime(tableSize);

    // 分配哈希表内存
    table = new HashNode[tableSize];
}

MyHash::~MyHash()
{
    delete[] table;
}

// 哈希函数：H(x) = x % prime
int MyHash::linearProbing(int key, bool forInsert)
{
    int index = abs(key) % prime % tableSize; // 使用绝对值确保索引为正

    if (forInsert)
    {
        // 插入操作：找到空位置或相同key的位置
        int startIndex = index;
        while (table[index].occupied)
        {
            // 如果找到相同的key，返回该位置
            if (table[index].key == key)
            {
                return index;
            }
            index = (index + 1) % tableSize;
            // 如果回到起点，表已满（理论上不会发生，因为装载因子<0.5）
            if (index == startIndex)
            {
                return -1;
            }
        }
    }
    else
    {
        // 查找操作：找到key或遇到空位置
        int startIndex = index;
        while (table[index].occupied)
        {
            if (table[index].key == key)
            {
                return index;
            }
            index = (index + 1) % tableSize;
            // 如果回到起点或遇到空位置，说明没找到
            if (index == startIndex || !table[index].occupied)
            {
                return -1;
            }
        }
    }

    return index;
}

void MyHash::setvalue(int key, int value)
{
    // 如果表已满，无法插入（理论上不会发生）
    if (currentElements >= maxElements)
    {
        return;
    }

    int index = linearProbing(key, true);

    if (index != -1)
    {
        if (!table[index].occupied)
        {
            // 新插入元素
            table[index].key = key;
            table[index].value = value;
            table[index].occupied = true;
            currentElements++;
        }
        else
        {
            // 更新已有元素
            table[index].value = value;
        }
    }
}

int MyHash::getvalue(int key)
{
    int index = linearProbing(key, false);

    if (index != -1 && table[index].occupied)
    {
        return table[index].value;
    }

    // 如果key不存在，返回默认值0
    return 0;
}