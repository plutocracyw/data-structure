#include <iostream>
#include <cstdio>

#include "Graph.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{
    Graph g(6);

    g.addedge(1, 2, 10);
    g.addedge(1, 3, 20);
    g.addedge(1, 4, 20);
    g.addedge(1, 5, 5);
    g.addedge(2, 3, 1);
    g.addedge(3, 4, 1);
    g.addedge(4, 5, 1);
    g.addedge(6, 1, 1);

    int len = g.getV();
    int *arr = g.dijkstra();

    int r_arr[6] = {0, 10, 11, 12, 5, -1};
    
    if(len == 6){
        cout << "Pass check point 1!" << endl;
    }

    int i;
    for(i = 0; i < len; i++){
        if(arr[i] != r_arr[i]) break;
    }
    if(i == len) cout << "Pass check point 2!" << endl;
    delete arr;
    // 在这里可以释放 dijkstra 分配的数组
    return 0;
}