/*******************************************************************************
* FileName:         Graph.h
* Author:           Name
* Student Number:   Student_id
* Date:             2023/04/29 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #12
*******************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include<vector>

class Graph{
private:
    int V;
    std::vector<std::vector<std::pair<int, int>>> adj;//邻接表法

    std::vector<int> inDegree; //入度表
    std::vector<int> ve; //事件最早发生时间
    std::vector<int> vl; //事件最晚发生时间

    struct Edge{
        int u;
        int v;
        int w;
        Edge(int _u, int _v, int _w):u(_u), v(_v), w(_w){}
    };

    std::vector<Edge> edges;//边集数组

public:
    /**
     *  类的构造函数
        @name Graph(int)
        @param  arg1 最大的定点数
        @return  
    */
    Graph(int max_v);

    /**
     *  类的析构函数
        @name ~Graph()
        @param 
        @return 
    */
    ~Graph();

    /**
     *  向图中加入(s, t)， 权重为w的单向
        @name addedge(int, int, int)
        @param  arg1 边的顶点1
        @param  arg2 边的顶点2
        @param  arg3 边的权重
        @return  void
    */
    void addedge(int s, int t, int w);

    /**
     *  询问图中节点的个数
        @name int getV()
        @param 
        @return  int 图中节点的个数
    */
    int getV();

   /**
    *  询问图拓扑排序的结果，并将结果储存在数组中
       @name int* topological()
       @param 
       @return  int* 拓扑排序的结果
   */
   int *topological();

   /**
    *  获取图中所有关键活动节点
       @name int* ka()
       @param 
       @return  int* 关键活动结果
   */
   int *ka();

};
#endif