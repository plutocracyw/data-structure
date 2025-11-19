/*
一共有编号为 1, 2, 3, …, n 的车厢按顺序进入调度站（栈）。
每节车厢都可以选择：

进栈（Push）

出栈（Pop）
最终每种不同的出栈顺序，都是一种“可能的车厢重排方案”。
你的任务是：

使用顺序栈（数组实现）；

用递归（或回溯）生成所有可能的出栈序列；

对输入 n（如 1, 2, 3, 4）输出所有合法的出栈结果。
*/

#include <iostream>
#include <vector>
using namespace std;

class SqStack
{
private:
    vector<int> data; // 保存栈元素
    unsigned int maxSize;
public:
    SqStack(unsigned int size) : maxSize(size) {}

    bool isFull()
    {
        return data.size() >= maxSize;
    }

    bool isEmpty()
    {
        return data.empty();
    }

    void push(int x)
    {
        if (!isFull())
        {
            data.push_back(x);
        }
    }

    int pop()
    {
        if (!isEmpty())
        {
            int x = data.back();
            data.pop_back();
            return x;
        }
        return -1;
    }

    int top()
    {
        if (!isEmpty())
        {
            return data.back();
        }
        return -1;
    }
};

// 生成所有可能的出栈序列
void generate(int n, int inNext, SqStack &s, vector<int> &output, int &count)
{
    // 若输入和栈都空，说明形成了一个完整的输出序列
    if (inNext > n && s.isEmpty())
    {
        // 输出结果
        ++count;
        cout << "Sequence " << count << ": ";
        for (unsigned int i = 0; i < output.size(); i++)
        {
            cout << output[i] << (i == output.size() - 1 ? '\n' : ' ');
        }
        return;
    }

    // 如果还有车厢没进栈，可以选择进栈
    if (inNext <= n)
    {
        s.push(inNext);
        generate(n, inNext + 1, s, output, count);
        s.pop(); // 回溯
    }

    // 如果栈不空，可以选择出栈
    if (!s.isEmpty())
    {
        output.push_back(s.top());
        s.pop();
        generate(n, inNext, s, output, count);
        s.push(output.back());
        output.pop_back();
    }
}

int main()
{
    int n;
    cout << "Please enter the number of cars: ";

    while (cin >> n)
    {
        if (n == -1)
        {
            cout << "Exiting program." << endl;
            break;
        }

        SqStack s(n);
        vector<int> output;
        int count = 0;

        cout << "All possible departure sequences are:\n";
        generate(n, 1, s, output, count);
        cout << "Total sequences: " << count << endl;
        cout << "Please enter the number of cars: ";
    }

    return 0;
}

/*
递归回溯算法适用于解决多种组合优化和搜索问题

1.排列组合问题
车厢调度：n个元素的出栈序列（卡特兰数问题）

全排列：生成所有可能的排列

组合问题：从n个元素中选k个的所有组合

子集问题：求集合的所有子集

2. 路径搜索问题
迷宫求解：找到从起点到终点的所有路径

八皇后问题：在棋盘上放置皇后使其互不攻击

数独求解：填充数字满足数独规则

图的遍历：深度优先搜索所有路径

3. 决策序列问题
括号生成：生成所有有效的括号组合

表达式求值：不同的运算顺序

任务调度：不同的执行顺序

资源分配：不同的分配方案


*/