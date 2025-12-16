/*******************************************************************************
* FileName:         Graph.cpp
* Author:           Your_name
* Student Number:   Student_Number
* Date:             2025/12/15 09:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #13
*******************************************************************************/

#include "Graph.h"
#include <cstring>
#define INF 9999999

Graph::Graph(int max_v){
    if (max_v <= 0)
        max_v = 1;
    
    this->max_v=max_v;
    this->v = max_v;

    adj=new int*[max_v+1];
    for (int i = 1; i <= max_v;i++){
        adj[i] = new int[max_v + 1];

        for (int j = 1;j<=max_v;j++){
            if(i==j)
                adj[i][j] = 0;
            else
                adj[i][j] = INF;
        }
    }

    visited=new bool[max_v + 1];
}
Graph::~Graph(){
    for (int i = 1; i <= max_v;i++){
        delete[] adj[i];
    }
    delete[] visited;
    delete[] adj;
}

void Graph::addedge(int s, int t, int w){
    if(s>=1 && s<=v && t>=1 && t<=v){
        adj[s][t] = w;
    }

}

int Graph::getV(){
    return v;
}

int* Graph::dijkstra(){
    int* dist = new int[max_v + 1];

    // 初始化
    for(int i=1;i<=v;i++){
        dist[i] = adj[1][i];
        visited[i] = false;
    }
    visited[1] = true;
    dist[1] = 0;

    // 主循环
    for (int i = 1; i < v;i++){
        int min=INF;
        int u=-1;

        // 找到当前未访问节点中距离源点最近的节点u
        for (int j = 1; j <= v;j++){
            if(!visited[j] && dist[j]<min){
                min = dist[j];
                u = j;
            }
        }

        if(u==-1) break; // 所有节点均已访问，退出循环

        visited[u] = true;

        for (int k = 1; k <= v; k++){
            if(!visited[k] && dist[u] + adj[u][k] < dist[k] && adj[u][k] < INF){
                dist[k] = dist[u] + adj[u][k];
            }
        }
    }

    // 将不可达节点的距离设为-1
    for (int i = 1; i <= v;i++){
        if(dist[i]>=INF){
            dist[i] = -1;
        }
    }

    int *result = new int[v];
    for (int i = 1; i <= v; i++)
    {
        result[i - 1] = (dist[i] >= INF) ? -1 : dist[i];
    }

    delete[] dist;
    return result;
}