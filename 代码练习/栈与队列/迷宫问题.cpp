//很典型的迷宫问题，先用栈非递归来解决一次
#include <iostream>
#include <stack>
using namespace std;

#define MAX 10

struct Pos
{
    int x, y; // 坐标
};

int maze[MAX][MAX] = {
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 1, 0, 1},
    {0, 0, 0, 0, 1, 0, 0, 1, 0, 1},
    {1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 1, 1},
    {1, 1, 1, 0, 0, 0, 1, 1, 1, 1},
    {0, 0, 1, 1, 1, 1, 1, 0, 0, 1},
    {1, 1, 1, 0, 0, 1, 1, 1, 1, 1}};

// 方向数组：右、下、左、上
int dirs[4][2] = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

bool visited[MAX][MAX] = {false};

// 检查是否可以走
bool canMove(int x, int y)
{
    return (x >= 0 && x < MAX && y >= 0 && y < MAX && maze[x][y] == 1 && !visited[x][y]);
}

// 输出路径
void printPath(stack<Pos> path)
{
    stack<Pos> temp;
    while (!path.empty())
    {
        temp.push(path.top());
        path.pop();
    }
    cout << "Path found:\n";
    while (!temp.empty())
    {
        Pos p = temp.top();
        temp.pop();
        cout << "(" << p.x << "," << p.y << ")";
        if (!temp.empty())
            cout << " -> ";
    }
    cout << endl;
}

bool solveMaze(Pos start, Pos end)
{
    stack<Pos> st;
    st.push(start);
    visited[start.x][start.y] = true;

    while (!st.empty())
    {
        Pos cur = st.top();

        if (cur.x == end.x && cur.y == end.y)
        {
            printPath(st);
            return true;
        }

        bool moved = false;
        for (int i = 0; i < 4; i++)
        {
            int nx = cur.x + dirs[i][0];
            int ny = cur.y + dirs[i][1];
            if (canMove(nx, ny))
            {
                visited[nx][ny] = true;
                st.push({nx, ny});
                moved = true;
                break; // 继续往前走
            }
        }

        if (!moved)
        {
            st.pop(); // 无路可走则回退
        }
    }

    cout << "No path found.\n";
    return false;
}

int main()
{
    Pos start = {0, 0};
    Pos end = {9, 9};

    cout << "Maze solver using stack:\n";
    solveMaze(start, end);

    return 0;
}
