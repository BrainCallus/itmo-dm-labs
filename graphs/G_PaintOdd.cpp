#include<iostream>
#include <vector>
#include<queue>

using namespace std;

int n, m, maxDeg;
vector<vector<int>> graph;
vector<int> deg;


void paint() {
    vector<int> color(n + 1, 0);
    vector<int> usedColor(maxDeg + 1, 0);
    deque<int> q;
    q.push_back(1);
    color[1] = 1;
    usedColor[1]++;

    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (int i = 0; i < graph[v].size(); i++) {
            int u = graph[v][i];
            if (color[u] == 0) {
                vector<int> prom;
                prom.assign(maxDeg + 1, 0);
                for (int p: graph[u]) {
                    prom[color[p]]++;
                }
                int pointr = 1;
                while (pointr <= maxDeg) {
                    if (prom[pointr] == 0) {
                        break;
                    }
                    pointr++;
                }
                color[u] = pointr;
                usedColor[color[u]]++;
                q.push_back(u);
            }
        }
    }

    cout << maxDeg << "\n";
    for (int i = 1; i < color.size(); i++) {
        cout << color[i] << "\n";
    }

}

int main() {
    cin >> n >> m;
    graph.resize(n + 1);
    deg.resize(n + 1);
    maxDeg = -1;
    for (int i = 0; i < m; i++) {
        int v, child;
        cin >> v >> child;
        graph[v].push_back(child);
        int sz = graph[v].size();
        if (sz > maxDeg) {
            maxDeg = sz;
        }
        graph[child].push_back(v);
        sz = graph[child].size();
        if (sz > maxDeg) {
            maxDeg = sz;
        }
    }
    if (!maxDeg % 2) maxDeg++;

    paint();
}