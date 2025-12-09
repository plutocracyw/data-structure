/*******************************************************************************
* FileName:         Graph.cpp
* Author:           Your_name
* Student Number:   Student_Number
* Date:             2023/04/29 09:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #12
*******************************************************************************/

#include "Graph.h"
#include<climits>
#include<queue>

Graph::Graph(int max_v){
    V = max_v;

    adj.resize(V+1);
    inDegree.resize(V+1, 0);

    ve.resize(V+1, 0);
    vl.resize(V+1, INT_MAX);
}

Graph::~Graph(){

}

void Graph::addedge(int s, int t, int w){
    if(s < 1 || s > V || t < 1 || t > V) return;

    adj[s].push_back(std::make_pair(t, w));
    inDegree[t]++;
    edges.push_back(Edge(s, t, w));
}

int Graph::getV(){
    return V;
}

int* Graph::topological(){
    int* result = new int[V];

    std::vector<int> inDeg = inDegree;
    std::queue<int> q;

    for(int i = 1; i <= V; i++){
        if(inDeg[i] == 0){
            q.push(i);
        }
    }

    int idx = 0;

    while(!q.empty()){
        int u = q.front();
        q.pop();
        result[idx++] = u;

        for(auto& neighbor : adj[u]){
            int v = neighbor.first;
            int w = neighbor.second;

            if(--inDeg[v] == 0){
                q.push(v);
            }

            if(ve[u] + w > ve[v]){
                ve[v] = ve[u] + w;
            }
        }

    }
    if(idx != V){
        delete[] result;
        return nullptr; // 图中有环，无法进行拓扑排序
    }

    return result;
    
}

int *Graph::ka()
{
    int *result = new int[V];

    std::vector<int> inDeg = inDegree;
    std::queue<int> q;

    for (int i = 1; i <= V; i++)
    {
        if (inDeg[i] == 0)
        {
            q.push(i);
        }
    }

    int idx = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        result[idx++] = u;

        for (auto &neighbor : adj[u])
        {
            int v = neighbor.first;
            if (--inDeg[v] == 0)
            {
                q.push(v);
            }
        }
    }

    if (idx != V)
    {
        delete[] result;
        return nullptr;
    }

    return result;
}
