/*******************************************************************************
* FileName:         Haffman.cpp
* Author:           Your_name
* Student Number:   Student_Number
* Date:             2025/11/16
* Version:          v1.1
* Description:      Data Structure Experiment #7
*******************************************************************************/

#include "Huffman.h"
#include <queue>
#include <stdexcept>

struct NodeCmp{
    bool operator()(HNode* a, HNode* b) const{
        return a->weight > b->weight;
    }
};

// 深度优先遍历，建立编码表
void HuffmanTree::buildCode(HNode *node, const string &path)
{
    if (!node)
        return;

    // 叶子节点：保存编码
    if (!node->left && !node->right)
    {
        codeTable[node->ch] = path;
        return;
    }

    buildCode(node->left, path + "0");
    buildCode(node->right, path + "1");
}

// 递归释放整个树
void HuffmanTree::freeTree(HNode *node)
{
    if (!node)
        return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

HuffmanTree::HuffmanTree(const int* Table){
    std::priority_queue<HNode *, std::vector<HNode *>, NodeCmp> pq;

    for (int i = 0; i < 26;i++){
        if(Table[i]>0){
            pq.push(new HNode(Table[i], char('a' + i)));
        }
    }

    if(pq.size()==1){
        HNode *only = pq.top();
        pq.pop();
        root = new HNode(only->weight, '\0', only, nullptr);
        buildCode(root, "");
        return;
    }

    while(pq.size()>1){
        HNode* left = pq.top();
        pq.pop();
        HNode* right = pq.top();
        pq.pop();
        HNode* parent = new HNode(left->weight + right->weight, '\0', left, right);
        pq.push(parent);
    }
    root = pq.top();
    buildCode(root, "");
}

HuffmanTree::~HuffmanTree(){
    freeTree(root);
}

string HuffmanTree::Encode(string message){
    string result;

    for(char c: message){
        if(c < 'a' || c > 'z'){
            throw std::invalid_argument("Input message contains invalid character.");
        }
        result += codeTable[c];
    }
    return result;
}

string HuffmanTree::Decode(string message){
    string result;
    HNode* current = root;

    for(char bit: message){
        if(bit == '0'){
            current = current->left;
        } else if(bit == '1'){
            current = current->right;
        } else{
            continue;
        }

        if(current->ch != '\0'){
            result += current->ch;
            current = root;
        }
    }
    return result;
}