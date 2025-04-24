
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <fstream>
#include <cmath>
using namespace std;


// A point in a Maze (Needed for QNode)
struct Point { 
    int x, y; 
    Point(int x_, int y_) : x(x_), y(y_) {} 
};

// A QNode (Needed for BFS)
struct QNode { 
    Point p; 
    int d; 
    QNode(Point p_, int d_) : p(p_), d(d_) {} 
};


bool isValid(int x, int y, int r, int c) {
    return x >= 0 && x < r && y >= 0 && y < c;
}

int BFS(vector<vector<int>>& mat, Point start, Point target) {
    int start = mat.size(), width = mat[0].size();
    
    // If Source and targetination are valid
    if (!mat[start.x][start.y] || !mat[target.x][target.y]) return -1;

    // Do BFS using Queue and Visited
    vector<vector<bool>> vis(start, vector<bool>(width, false));
    queue<QNode> q;
    q.push(QNode(start, 0));
    vis[start.x][start.y] = true;
    while (!q.empty()) {
        
        // Pop an item from queue
        QNode node = q.front(); q.pop();
        Point p = node.p;
        int d = node.d;

        // If we reached the targetination
        if (p.x == target.x && p.y == target.y) return d;
        
        // Try all four adjacent
        int dx[] = {-1, 0, 0, 1};
        int dy[] = {0, -1, 1, 0};
        for (int i = 0; i < 4; i++) {
            int nx = p.x + dx[i], ny = p.y + dy[i];
            if (isValid(nx, ny, start, width) && mat[nx][ny] && !vis[nx][ny]) {
                vis[nx][ny] = true;
                q.push(QNode(Point(nx, ny), d + 1));
            }
        }
    }
    return -1;
}

int main() {
    vector<vector<int>> mat = {
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
        {1, 0, 1, 1, 1, 1, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 1, 0, 0, 1}
    };

    cout << BFS(mat, Point(0, 0), Point(3, 4));
}