/*******************************************************************************
 * FileName:         BinTree.cpp
 * Author:           Your_name
 * Student Number:   Student_Number
 * Date:             2023/04/04 09:24:55
 * Version:          v1.0
 * Description:      Data Structure Experiment #8
 *******************************************************************************/

#include "BinTree.h"
#include <functional>

BinTree::BinTree()
{
    root = nullptr;
    max_id = 0;
}

BinTree::~BinTree()
{
    std::function<void(node *)> delete_subtree = [&](node *n)
    {
        if (n)
        {
            delete_subtree(n->left);
            delete_subtree(n->right);
            delete n;
        }
    };
    delete_subtree(root);
    root = nullptr; 
}

BinTree::node *BinTree::findNodeById(node *current, int id) const
{
    if (!current)
        return nullptr;
    if (current->id == id)
        return current;
    node *res = findNodeById(current->left, id);
    if (res)
        return res;
    return findNodeById(current->right, id);
}

void BinTree::insert(int val, int parent, int flg)
{
    node *new_node = new node(val, ++max_id);

    if (parent == 0)
    { // 根节点
        root = new_node;
        return;
    }

    node *parentNode = findNodeById(root, parent);
    if (!parentNode)
    {
        delete new_node;
        return;
    }

    new_node->parent = parentNode;
    if (flg == -1)
        parentNode->left = new_node;
    else if (flg == 1)
        parentNode->right = new_node;
}

int *BinTree::p_traversal() const
{
    if (!root)
        return nullptr;

    int count = countNode();
    int *arr = new int[count];
    int index = 0;

    std::function<void(node *)> preorder = [&](node *n)
    {
        if (n)
        {
            arr[index++] = n->val;
            preorder(n->left);
            preorder(n->right);
        }
    };
    preorder(root);
    return arr;
}

int *BinTree::m_traversal() const
{
    if (!root)
        return nullptr;

    int count = countNode();
    int *arr = new int[count];
    int idx = 0;

    std::function<void(node *)> inorder = [&](node *n)
    {
        if (!n)
            return;
        inorder(n->left);
        arr[idx++] = n->val;
        inorder(n->right);
    };
    inorder(root);
    return arr;
}

int *BinTree::s_traversal() const
{
    if (!root)
        return nullptr;

    int count = countNode();
    int *arr = new int[count];
    int idx = 0;

    std::function<void(node *)> postorder = [&](node *n)
    {
        if (!n)
            return;
        postorder(n->left);
        postorder(n->right);
        arr[idx++] = n->val;
    };
    postorder(root);
    return arr;
}

int BinTree::countNode() const
{
    std::function<int(node *)> count_helper = [&](node *n) -> int
    {
        if (!n)
            return 0;
        return 1 + count_helper(n->left) + count_helper(n->right);
    };
    return count_helper(root);
}

int BinTree::height() const
{
    std::function<int(node *)> height_helper = [&](node *n) -> int
    {
        if (!n)
            return 0;
        int left_height = height_helper(n->left);
        int right_height = height_helper(n->right);
        return 1 + (left_height > right_height ? left_height : right_height);
    };
    return height_helper(root);
}
