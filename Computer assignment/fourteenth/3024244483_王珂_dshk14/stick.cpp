/*
现在有 n 个小木棍，每个小木棍的长度为 lenᵢ从 n 个木棍中拿出 3 个，计算多少种取法可以使得三个木棍可以组成三角形？
输入:
第一行包含一个整数 n，第二行包含 n 个整数，表示木棍长度。
输出:
输出一个整数，表示可组成三角形的取法。
输入样例:
5
10 20 20 20 30
输出样例:
7
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> arr(n);

    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end());

    long long count = 0;
    for (int k = 2; k < n;k++){
        int i = 0;
        int j = k - 1;
        while(i < j){
            if(arr[i] + arr[j] > arr[k]){
                count += (j - i);
                j--;
            }
            else{
                i++;
            }
        }
    }

    cout<<count<<endl;
    return 0;
}