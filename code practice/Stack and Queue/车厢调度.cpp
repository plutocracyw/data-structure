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

struct SqStack{
    vector<int> data;    //保存栈元素
    int maxSize;
    SqStack(int size): maxSize(size) {}

    bool isFull(){
        return data.size() >= maxSize;
    }

    bool isEmpty(){
        return data.empty();
    }

    void push(int x){
        if(!isFull()){
            data.push_back(x);
        }
    }

    int pop(){
        if(!isEmpty()){
            int x=data.back();
            data.pop_back();
            return x;
        }
        return -1;
    }

    int top(){
        if(!isEmpty()){
            return data.back();
        }
        return -1;
    }
};

// 生成所有可能的出栈序列
void generate(int n,int inNext,SqStack &s,vector<int>&output,int &count){
    // 若输入和栈都空，说明形成了一个完整的输出序列
    if(inNext>n && s.isEmpty()){
        //输出结果
        ++count;
        cout<<"Sequence "<<count<<": ";
        for(int i=0;i<output.size();i++){
            cout << output[i] << (i == output.size() - 1 ? '\n' : ' ');
        }
        return;
    }

    //如果还有车厢没进栈，可以选择进栈
    if(inNext <= n){
        s.push(inNext);
        generate(n,inNext+1,s,output,count);
        s.pop(); //回溯
    }

    //如果栈不空，可以选择出栈
    if(!s.isEmpty()){
        output.push_back(s.top());
        s.pop();
        generate(n,inNext,s,output,count);
        s.push(output.back());
        output.pop_back();
    }
}


int main(){
    int n;
    cout<<"Please enter the number of cars: ";

    while(cin>>n){
        if(n==-1) {
            cout<<"Exiting program."<<endl;
            break;
        }

        SqStack s(n);
        vector<int> output;
        int count = 0;

        cout<<"All possible departure sequences are:\n";
        generate(n,1,s,output,count);
        cout<<"Total sequences: "<<count<<endl;
        cout<<"Please enter the number of cars: ";
    }

    return 0;
}