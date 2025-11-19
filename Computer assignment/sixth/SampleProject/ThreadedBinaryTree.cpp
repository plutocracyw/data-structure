#include "ThreadedBinaryTree.h"

// ------------------------------------
// 构造树
// ------------------------------------
ThreadedBinaryTree::Node *ThreadedBinaryTree::buildTree(
    const std::vector<int> &Lson,
    const std::vector<int> &Rson,
    int id)
{
    if (id == -1)
        return nullptr;
    Node *p = nodes[id];
    p->left = buildTree(Lson, Rson, Lson[id]);
    p->right = buildTree(Lson, Rson, Rson[id]);
    return p;
}

ThreadedBinaryTree::ThreadedBinaryTree(
    const std::vector<int> &Lson,
    const std::vector<int> &Rson)
{
    int n = Lson.size();
    nodes.resize(n);

    for (int i = 0; i < n; i++)
        nodes[i] = new Node(i);

    root = buildTree(Lson, Rson, 0);
    pre = nullptr;
}

// ------------------------------------
// 前序线索化
// ------------------------------------
void ThreadedBinaryTree::preThread(Node *p)
{
    if (!p)
        return;

    if (!p->left)
    {
        p->left = pre;
        p->ltag = 1;
    }

    if (pre && !pre->right)
    {
        pre->right = p;
        pre->rtag = 1;
    }
    pre = p;

    if (p->ltag == 0)
        preThread(p->left);
    if (p->rtag == 0)
        preThread(p->right);
}

void ThreadedBinaryTree::ToPThreadTree()
{
    pre = nullptr;
    preThread(root);
}

// ------------------------------------
// 中序线索化
// ------------------------------------
void ThreadedBinaryTree::inThread(Node *p)
{
    if (!p)
        return;
    inThread(p->left);

    if (!p->left)
    {
        p->left = pre;
        p->ltag = 1;
    }
    if (pre && !pre->right)
    {
        pre->right = p;
        pre->rtag = 1;
    }
    pre = p;

    inThread(p->right);
}

void ThreadedBinaryTree::ToMThreadTree()
{
    pre = nullptr;
    inThread(root);
}

// ------------------------------------
// 后序线索化
// ------------------------------------
void ThreadedBinaryTree::postThread(Node *p)
{
    if (!p)
        return;
    postThread(p->left);
    postThread(p->right);

    if (!p->left)
    {
        p->left = pre;
        p->ltag = 1;
    }
    if (pre && !pre->right)
    {
        pre->right = p;
        pre->rtag = 1;
    }
    pre = p;
}

void ThreadedBinaryTree::ToSThreadTree()
{
    pre = nullptr;
    postThread(root);
}

// ------------------------------------
// 获取左孩子编号
// ------------------------------------
int ThreadedBinaryTree::GetLson(int id)
{
    Node *p = nodes[id];
    return (p->ltag == 0 && p->left) ? p->left->id : -1;
}

// ------------------------------------
// 获取右孩子编号
// ------------------------------------
int ThreadedBinaryTree::GetRson(int id)
{
    Node *p = nodes[id];
    return (p->rtag == 0 && p->right) ? p->right->id : -1;
}
