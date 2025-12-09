/*******************************************************************************
 * FileName:         Graph.h
 * Author:           Your_name
 * Student Number:   Student_Number
 * Date:             2023/04/22 11:24:55
 * Version:          v1.1
 * Description:      Data Structure Experiment #11
 *******************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

struct Edge
{
    int u, v, weight;
    Edge(int _u = 0, int _v = 0, int _w = 0) : u(_u), v(_v), weight(_w) {}
};

class Graph
{
private:
    int max_v;                         // 最大顶点编号（允许 1..max_v）
    int edge_num;                      // 边数
    std::vector<std::vector<int>> adj; // 邻接矩阵（1-based）
    std::vector<Edge> edges;           // 边集（用于 Kruskal）

    // 并查集用于 Kruskal
    std::vector<int> parent;
    std::vector<int> rankv;

    // 并查集操作
    int findset(int x);
    void unionset(int x, int y);

public:
    /*
     * 类的构造函数 
     * @name Graph(int) 
     * @param arg1 最大的定点数 
     * @return 
     */
    Graph(int max_v);

    /** 
     * 类的析构函数 
     * @name ~Graph() 
     * @param 
     * @return
     */
    ~Graph();

    /** * 
     * 向图中加入(s, t)， 权重为w的双向边 
     * @name addedge(int, int, int) 
     * @param arg1 边的顶点1 
     * @param arg2 边的顶点2 
     * @param arg3 边的权重 
     * @return void 
     */
    void addedge(int s, int t, int w);

    /** *
     * 询问这张图的最小生成树(prim算法实现)
     * @name int prim() 
     * @param 
     * @return int 最小生成树的权值 
     */
    int prim();

    /** * 
     *询问这张图的最小生成树(kruskal实现) 
     * @name int kruskal() 
     * @param 
     * @return int 最小生成树的权值 
     */
    int kruskal();
};

#endif
