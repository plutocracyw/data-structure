/*
题目要求将一个整数 n 表示成若干个 2 的幂的和，并且用括号形式表达幂指数。
n = 137 = 2^7 + 2^3 + 2^0
输出 ；2(2(2)+2+2(0))+2(2+2(0))+2(0)
约定
| 表达式    | 含义                         |
| :----- | :------------------------- |
| `2(0)` | 表示 `2^0 = 1`               |
| `2`    | 表示 `2^1 = 2`               |
| `2(k)` | 表示 `2^k`，其中 k 自身也要用相同的规则表示 |

*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

string solve(int n){
    if(n==0)
        return "0";
    if(n==1)
        return "2(0)";
    if(n==2)
        return "2";

    string res="";
    vector<int> bits;

    int k = 0;

    // 将 n 按二进制拆分
    while(n>0){
        if(n & 1)
            bits.push_back(k);
        n>>=1;
        k++;
    }

    //高到低拼接
    for (int i = bits.size() - 1; i >= 0; i--){
        int exp = bits[i];
        if (!res.empty())
            res += "+";
        if(exp==0)
            res += "2(0)";
        else if(exp==1)
            res += "2";
        else
            res += "2(" + solve(exp) + ")";
    }

    return res;
}

int main(){
    int n;
    cin >> n;
    cout << solve(n) << endl;
    return 0;
}