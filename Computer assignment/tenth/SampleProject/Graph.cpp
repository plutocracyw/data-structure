/*******************************************************************************
* FileName:         Graph.cpp
* Author:           Your_name
* Student Number:   Student_Number
* Date:             2025/12/01
* Version:          v1.0
* Description:      Data Structure Experiment #10
*******************************************************************************/

#include "Graph.h"
#include <vector>
#include <utility>


Graph::Graph(int v){
    max_v = v;
    adj.resize(max_v);  
}

Graph::~Graph(){

}

void Graph::addedge(int s, int t, int w){
    if(s >= 0 && s < max_v && t >= 0 && t < max_v){
        adj[s].push_back({t, w});
    }
}

int Graph::getInDegree(int v){
    if(v < 0 || v >= max_v){
        return -1;
    }
    int inDegree = 0;
    for (int i = 0; i < max_v; ++i) {
        for (const auto& edge : adj[i]) {
            if (edge.first == v) {
                ++inDegree;
            }
        }
    }
    return inDegree;
}

int Graph::getOutDegree(int v){
    if(v < 0 || v >= max_v){
        return -1;
    }
    return adj[v].size();
}

int Graph::access(int s, int t){
    if(s < 0 || s >= max_v || t < 0 || t >= max_v){
        return -1;
    }
    for (const auto& edge : adj[s]) {
        if (edge.first == t) {
            return edge.second;
        }
    }
    return -1;
}

int Graph::getDist(int s, int t){
    if(s < 0 || s >= max_v || t < 0 || t >= max_v){
        return -1;
    }
    int idx = 0;
    for (const auto& edge : adj[s]) {
        if (edge.first == t) {
            return idx;
        }
        ++idx;
    }
    return -1;
}