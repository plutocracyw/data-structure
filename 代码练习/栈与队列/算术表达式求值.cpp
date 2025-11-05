#include <iostream>
#include <string>
#include <cctype>
#include <stack>
using namespace std;

char ops[] = {'+', '-', '*', '/', '(', ')', '#'};
int prior[7][7] = {
    // +    -    *    /    (    )    #
    {'>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '>', '>'},
    {'<', '<', '<', '<', '<', '=', ' '},
    {'>', '>', '>', '>', ' ', '>', '>'},
    {'<', '<', '<', '<', '<', ' ', '='}};

int getOpIndex(char op)
{
    for (int i = 0; i < 7; ++i)
    {
        if (ops[i] == op)
            return i;
    }
    return -1;
}

char getPriorityOp(char op1, char op2)
{
    int i = getOpIndex(op1), j = getOpIndex(op2);
    if (i == -1 || j == -1)
        return ' ';
    return static_cast<char>(prior[i][j]);
}

int calculateExpression(string expr)
{
    stack<int> numStack;
    stack<char> opStack;
    opStack.push('#');
    expr += '#';

    int i = 0;
    // 关键：循环直到同时遇到 expr[i]=='#' 且 栈顶=='#'
    while (!(expr[i] == '#' && opStack.top() == '#'))
    {

        // 跳过空格
        if (expr[i] == ' ')
        {
            ++i;
            continue;
        }

        // 数字（多位）
        if (isdigit(static_cast<unsigned char>(expr[i])))
        {
            int num = 0;
            while (i < (int)expr.size() && isdigit(static_cast<unsigned char>(expr[i])))
            {
                num = num * 10 + (expr[i] - '0');
                ++i;
            }
            numStack.push(num);
        }
        else
        {
            char topOp = opStack.top();
            char currOp = expr[i];
            char priority = getPriorityOp(topOp, currOp);

            if (priority == '<')
            {
                opStack.push(currOp);
                ++i;
            }
            else if (priority == '>')
            {
                opStack.pop();
                if (numStack.size() < 2)
                {
                    cout << "failed, insufficient operands\n";
                    return 0;
                }
                int b = numStack.top();
                numStack.pop();
                int a = numStack.top();
                numStack.pop();
                int result = 0;
                switch (topOp)
                {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    if (b == 0)
                    {
                        cout << "failed, division by zero\n";
                        return 0;
                    }
                    result = a / b;
                    break;
                default:
                    cout << "failed, unknown operator: " << topOp << endl;
                    return 0;
                }
                numStack.push(result);
            }
            else if (priority == '=')
            {
                opStack.pop();
                ++i;
            }
            else
            {
                cout << "failed, invalid character or missing priority: '" << currOp << "'" << endl;
                return 0;
            }
        }
    }

    if (numStack.empty())
    {
        cout << "failed, no result\n";
        return 0;
    }
    return numStack.top();
}

int main()
{
    string expr;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expr);
    int result = calculateExpression(expr);
    cout << "Result: " << result << endl;
    return 0;
}
