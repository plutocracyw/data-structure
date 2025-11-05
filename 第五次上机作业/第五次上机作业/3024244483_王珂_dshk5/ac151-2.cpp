// 递归主符号法
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
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

class Parser{
    string s;
    int pos;

    // 读取下一个非空字符
    char peek(){
        while(pos<(int)s.size() && isspace(s[pos]))
            pos++;

        if(pos<(int)s.size())
            return s[pos];

        return '\0';
    }

    // 取出当前字符并前进
    char get(){
        char c = peek();
        pos++;
        return c;
    }

    long long expression(){
        long long value = term();

        while(true){
            char c = peek();
            if (c == '+' || c == '-')
            {
                get();
                long long rhs = term();
                if (c == '+')
                    value += rhs;
                else
                    value -= rhs;
            }
            else
                break;
        }

        return value;
    }

    long long term(){
        long long value = factor();

        while (true)
        {
            char c = peek();
            if (c == '*' || c == '/')
            {
                get();
                long long rhs = factor();
                if (c == '*')
                    value *= rhs;
                else
                    value /= rhs; 
            }
            else
                break;
        }
        return value;
    }

    long long factor(){
        return power();
    }

    long long power(){
        long long base = atom();
        if (peek() == '^')
        {
            get();
            long long exp = power();
            long long res = 1;
            while (exp--)
                res *= base;
            return res;
        }
        return base;
    }

    long long atom(){
        char c = peek();
        if (c == '-')
        { // 负号处理
            get();
            return -atom();
        }
        else if (c == '(')
        {
            get(); // '('
            long long val = expression();
            if (peek() == ')')
                get();
            return val;
        }
        else if (isdigit(c))
        {
            long long val = 0;
            while (isdigit(peek()))
            {
                val = val * 10 + (get() - '0');
            }
            return val;
        }
        return 0;
    }

public:
    Parser(const string &str) : s(str), pos(0) {}

    long long eval(){
        return expression();
    }
};

int main()
{
    string s;
    getline(cin, s);

    Parser parser(s);
    cout << parser.eval();
    return 0;
}