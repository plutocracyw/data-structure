#include <iostream>
#include <string>
#include <cctype>
#include <stack>
using namespace std;

enum Priority
{
    LESS,
    GREATER,
    EQUAL,
    ERROR
};

Priority getPriority(char stackOp, char currOp)
{
    if (stackOp == '(' && currOp == ')')
        return EQUAL;
    if (stackOp == '#' && currOp == '#')
        return EQUAL;
    if (currOp == ')')
        return GREATER;
    if (currOp == '(')
        return LESS;
    if (stackOp == '(')
        return LESS;

    auto getLevel = [](char op) -> int
    {
        switch (op)
        {
        case '#':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return -1;
        }
    };

    int stackLevel = getLevel(stackOp);
    int currLevel = getLevel(currOp);

    if (stackLevel == -1 || currLevel == -1)
        return ERROR;

    return (stackLevel < currLevel) ? LESS : GREATER;
}

int performOperation(int a, int b, char op)
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
        if (b == 0)
            throw runtime_error("Division by zero");
        return a / b;
    default:
        throw runtime_error("Unknown operator");
    }
}

int calculateExpression(string expr)
{
    stack<int> numStack;
    stack<char> opStack;

    opStack.push('#');
    expr += '#';

    int i = 0;
    int exprLength = expr.length();

    while (!(expr[i] == '#' && opStack.top() == '#'))
    {
        if (expr[i] == ' ')
        {
            ++i;
            continue;
        }

        // 处理数字和负数
        if (isdigit(expr[i]) || (expr[i] == '-' && (i == 0 || expr[i - 1] == '(' || expr[i - 1] == '+' || expr[i - 1] == '-' || expr[i - 1] == '*' || expr[i - 1] == '/')))
        {
            int sign = 1;
            if (expr[i] == '-')
            {
                sign = -1;
                ++i;
            }
            int num = 0;
            while (i < exprLength && isdigit(expr[i]))
            {
                num = num * 10 + (expr[i] - '0');
                ++i;
            }
            numStack.push(sign * num);
            continue; // 修复关键：读取完数字后跳过下面的运算符处理
        }

        // 处理运算符
        char currentChar = expr[i];
        char topOperator = opStack.top();
        Priority priority = getPriority(topOperator, currentChar);

        switch (priority)
        {
        case LESS:
            opStack.push(currentChar);
            ++i;
            break;

        case GREATER:
        {
            opStack.pop();
            if (numStack.size() < 2)
                throw runtime_error("Insufficient operands");
            int rightOperand = numStack.top();
            numStack.pop();
            int leftOperand = numStack.top();
            numStack.pop();
            int result = performOperation(leftOperand, rightOperand, topOperator);
            numStack.push(result);
            break;
        }

        case EQUAL:
            opStack.pop();
            ++i;
            break;

        case ERROR:
            throw runtime_error("Syntax error");
        }
    }

    if (numStack.empty())
        throw runtime_error("No result found");

    return numStack.top();
}

int main()
{
    string expr;
    cout << "Enter an arithmetic expression: ";
    cin >> ws;
    getline(cin, expr);

    try
    {
        int result = calculateExpression(expr);
        cout << "Result: " << result << endl;
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
