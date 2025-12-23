/*
编程题目1:
给定一个包含n个数字的有序数组，每次查询数组中大于等于数字q的第一个元素。保证q小于等于最大元素。
输入：
第一行包含两个数字，n，Q。表示数组中元素个数和查询个数。第二行包含n个数字，表示有序数组。接下来Q行每行一个整数q，表示询问元素。(n <= 1e6, q <= 1e5)
输出：
对于每个查询q，输出查询结果。
输入样例:
5 3
10 20 30 40 50
2
49
50
输出样例:
10
50
50
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, Q;
    cin>> n >> Q;
    vector<int> arr(n);

    for(int i = 0; i < n; i++){
        cin>> arr[i];
    }

    while(Q--){
        int q;
        cin >> q;

        int left = 0;
        int right = n; 

        while(left < right){
            int mid = left + (right - left) / 2;

            if(arr[mid] >= q){
                right = mid;
            }
            else{
                left = mid + 1;
            }
        }
        cout << arr[left] << "\n";
    }

    return 0;
}