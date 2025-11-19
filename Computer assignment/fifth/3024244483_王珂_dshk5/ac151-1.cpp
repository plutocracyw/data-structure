//栈模拟表达式求值
/*
给出一个表达式,其中运算符仅包含+,-,*,/,^（加 减 乘 整除 乘方）要求求出表达式的最终值。

数据可能会出现括号情况，还有可能出现多余括号情况。

数据保证不会出现大于或等于231
的答案。

数据可能会出现负数情况。

数据保证不会出现指数为负数的情况。

数据保证指数运算不会连续出现，例如 2^2^3。

输入格式
输入仅一行，即为表达式。

输出格式
输出仅一行，既为表达式算出的结果。

输入样例：
(2+2)^(1+1)
输出样例：
16
*/
#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

int priority(char op)
{
    if (op == '^')
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

long long calc(long long a, long long b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '^':
    {
        long long res = 1;
        while (b--)
            res *= a;
        return res;
    }
    }
    return 0;
}

long long eval(const string &exp)
{
    stack<long long> num;
    stack<char> op;
    int n = exp.size();

    for (int i = 0; i < n; i++)
    {
        char c = exp[i];
        if (isspace(c))
            continue;

        if (isdigit(c))
        {
            long long val = 0;
            while (i < n && isdigit(exp[i]))
            {
                val = val * 10 + (exp[i] - '0');
                i++;
            }
            num.push(val);
            i--;
        }
        else if (c == '(')
        {
            op.push(c);
        }
        else if (c == ')')
        {
            while (!op.empty() && op.top() != '(')
            {
                if (num.size() < 2)
                    break;
                long long b = num.top();
                num.pop();
                long long a = num.top();
                num.pop();
                char t = op.top();
                op.pop();
                num.push(calc(a, b, t));
            }
            if (!op.empty() && op.top() == '(')
                op.pop();
        }
        else
        {
            if (c == '-' && (i == 0 || exp[i - 1] == '(' || exp[i - 1] == '+' || exp[i - 1] == '-' || exp[i - 1] == '*' || exp[i - 1] == '/' || exp[i - 1] == '^'))
            {

                // 如果是负号后面直接跟数字
                if (i + 1 < n && isdigit(exp[i + 1]))
                {
                    i++;
                    long long val = 0;
                    while (i < n && isdigit(exp[i]))
                    {
                        val = val * 10 + (exp[i] - '0');
                        i++;
                    }
                    num.push(-val);
                    i--;
                    continue;
                }
                else if (i + 1 < n && exp[i + 1] == '(')
                {
                    num.push(0);
                    op.push('-');
                    continue;
                }
                else
                {
                    num.push(0);
                }
            }

            while (!op.empty() && op.top() != '(' && (priority(op.top()) > priority(c) || (priority(op.top()) == priority(c) && c != '^')))
            {
                if (num.size() < 2)
                    break;
                long long b = num.top();
                num.pop();
                long long a = num.top();
                num.pop();
                char t = op.top();
                op.pop();
                num.push(calc(a, b, t));
            }
            op.push(c);
        }
    }

    while (!op.empty())
    {
        char t = op.top();
        op.pop();
        if (t == '(')
            continue;
        if (num.size() < 2)
            break;
        long long b = num.top();
        num.pop();
        long long a = num.top();
        num.pop();
        num.push(calc(a, b, t));
    }

    if (num.empty())
        return 0;
    return num.top();
}

int main()
{
    string s;
    getline(cin, s);
    cout << eval(s);
    return 0;
}
