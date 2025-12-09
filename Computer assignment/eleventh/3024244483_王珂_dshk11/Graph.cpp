/*******************************************************************************
 * FileName:         Graph.cpp
 * Author:           Your_name
 * Student Number:   Student_Number
 * Date:             2023/04/22 09:24:55
 * Version:          v1.1
 * Description:      Data Structure Experiment #11
 *******************************************************************************/

#include "Graph.h"
#include <climits>
#include <algorithm>

Graph::Graph(int max_v)
{
    this->max_v = max_v;
    this->edge_num = 0;

    adj.resize(max_v + 1, std::vector<int>(max_v + 1, INT_MAX));

    for (int i = 1; i <= max_v; ++i)
    {
        adj[i][i] = 0;
    }

    parent.resize(max_v + 1);
    rankv.resize(max_v + 1, 0);

    for (int i = 1; i <= max_v; ++i)
    {
        parent[i] = i;
    }
}

Graph::~Graph()
{
}

void Graph::addedge(int s, int t, int w)
{
    if (s <= 0 || s > max_v || t <= 0 || t > max_v)
        return;

    adj[s][t] = w;
    adj[t][s] = w;

    edges.push_back(Edge(s, t, w));
    edge_num++;
}

int Graph::findset(int x)
{
    if (parent[x] != x)
    {
        parent[x] = findset(parent[x]);
    }
    return parent[x];
}

void Graph::unionset(int x, int y)
{
    int rootX = findset(x);
    int rootY = findset(y);

    if (rootX != rootY)
    {
        if (rankv[rootX] < rankv[rootY])
        {
            parent[rootX] = rootY;
        }
        else if (rankv[rootX] > rankv[rootY])
        {
            parent[rootY] = rootX;
        }
        else
        {
            parent[rootY] = rootX;
            rankv[rootX]++;
        }
    }
}

int Graph::prim()
{
    // Prim 使用 1..max_v
    std::vector<int> lowcost(max_v + 1, INT_MAX);
    std::vector<bool> visited(max_v + 1, false);

    // 从 1 号顶点开始（与 main.cpp 的用法一致）
    lowcost[1] = 0;
    int total_cost = 0;

    for (int i = 1; i <= max_v; ++i)
    {
        int u = -1;
        int minv = INT_MAX;

        // 找到未访问顶点中 lowcost 最小的顶点 u
        for (int j = 1; j <= max_v; ++j)
        {
            if (!visited[j] && lowcost[j] < minv)
            {
                minv = lowcost[j];
                u = j;
            }
        }

        if (u == -1)
        {
            // 图不连通，无法再选择顶点，返回已累加的 total_cost
            return total_cost;
        }

        visited[u] = true;
        total_cost += (minv == INT_MAX ? 0 : minv); // 第一次加入时 minv 可能为0

        // 用新加入顶点 u 更新其他顶点的 lowcost
        for (int v = 1; v <= max_v; ++v)
        {
            if (!visited[v] && adj[u][v] < lowcost[v])
            {
                lowcost[v] = adj[u][v];
            }
        }
    }

    return total_cost;
}

int Graph::kruskal()
{
    // Kruskal 需要排序边集
    std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
    { return a.weight < b.weight; });

    // reset 并查集（以防多次调用 kruskal）
    for (int i = 1; i <= max_v; ++i)
    {
        parent[i] = i;
        rankv[i] = 0;
    }

    int total_cost = 0;
    int edges_used = 0;

    for (const auto &edge : edges)
    {
        int u = edge.u;
        int v = edge.v;
        int weight = edge.weight;

        if (findset(u) != findset(v))
        {
            unionset(u, v);
            total_cost += weight;
            edges_used++;
            if (edges_used == max_v - 1)
                break;
        }
    }

    return total_cost;
}
