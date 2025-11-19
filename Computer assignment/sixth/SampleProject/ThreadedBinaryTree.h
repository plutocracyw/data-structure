/******************************************************
 * FileName:         ThreadedBinaryTree.h
 * Description:      实现前序、中序、后序线索二叉树
 ******************************************************/

#ifndef THREADEDBINARYTREE_H
#define THREADEDBINARYTREE_H

#include <vector>

class ThreadedBinaryTree
{
public:
    // 节点结构
    struct Node
    {
        int id;             // 节点编号
        Node *left, *right; // 左右指针
        bool ltag, rtag;    // 0=孩子指针, 1=线索指针
        Node(int _id) : id(_id), left(nullptr), right(nullptr),
                        ltag(0), rtag(0) {}
    };

private:
    Node *root;
    std::vector<Node *> nodes; // 通过 id 索引节点
    Node *pre;                 // 线索化过程中的前驱节点

private:
    // 建树辅助
    Node *buildTree(const std::vector<int> &l, const std::vector<int> &r, int id);

    // 线索化
    void preThread(Node *p);
    void inThread(Node *p);
    void postThread(Node *p);

public:
    /**
     * 构造函数
     * 给定每个节点 id 的左孩子编号、右孩子编号
     * 若为 -1 表示无孩子
     */
    ThreadedBinaryTree(const std::vector<int> &Lson,
                       const std::vector<int> &Rson);

    // 线索化操作
    void ToPThreadTree(); // 前序
    void ToMThreadTree(); // 中序
    void ToSThreadTree(); // 后序

    // 查询
    int GetLson(int id);
    int GetRson(int id);
};

#endif
