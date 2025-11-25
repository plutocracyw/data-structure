/*******************************************************************************
* FileName:         Haffman.h
* Author:           Name
* Student Number:   3024244XXX
* Date:             2025/11/16 
* Version:          v1.1
* Description:      Data Structure Experiment #7
*******************************************************************************/

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <string>
#include <unordered_map>
using std::string;

struct HNode{
    int weight;
    char ch;
    HNode* left;
    HNode* right;
    HNode(int w = 0, char c = '\0', HNode *l = nullptr, HNode *r = nullptr) : weight(w), ch(c), left(l), right(r) {}
};

class HuffmanTree{
private:
    HNode* root;

    std::unordered_map<char, string> codeTable;

    void buildCode(HNode* node, const string& str);// 生成编码表
    void freeTree(HNode* node); // 释放树内存
public:
    /**
     *  构造函数
        @name HuffmanTree(const int* Table)
        @param arg1 数字出现的频度表
        @return
        注意： 要求树的左孩子为权制较小的编码，左孩子的二进制编号为0
    */
    HuffmanTree(const int* Table);

    /**
     *  析构函数
        @name ~HuffmanTree()
        @param 
        @return
    */
    ~HuffmanTree();

    /**
     *  获取message的霍夫曼编码
        @name string Encode(string)
        @param  arg1 待编码待字符串
        @return 对应的霍夫曼编码
    */
    string Encode(string message);


    /**
     *  获取message的霍夫曼解码
        @name string Decode(stirng)
        @param 
        @return 解码出的内容
    */
    string Decode(string message);
};

#endif