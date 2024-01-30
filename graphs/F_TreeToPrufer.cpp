#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> graph;
vector<int> pryuf;
vector<int> parent;
vector<int> deg;

void dfs(int v) {
    for (int i = 0; i < graph[v].size(); i++) {
        int u = graph[v][i];
        if (parent[v] != u) {
            parent[u] = v;
            dfs(u);
        }
    }
}

void makePryuf() {
    parent.resize(n + 1);
    parent[n] = -1;
    dfs(n);
    int pointr = -1;

    for (int i = 1; i <= n; ++i) {
        deg[i] = graph[i].size();
        if (deg[i] == 1 && pointr == -1) {
            pointr = i;
        }

    }

    int leaf = pointr;
    for (int i = 0; i < n - 2; ++i) {
        int par = parent[leaf];
        pryuf.push_back(par);
        --deg[par];
        if (deg[par] == 1 && par < pointr) {
            leaf = par;
        } else {
            ++pointr;
            while (pointr <= n && deg[pointr] != 1) {
                ++pointr;
            }
            leaf = pointr;
        }
    }
    for (int i: pryuf) {
        cout << i << " ";
    }
}

int main() {
    cin >> n;
    graph.resize(n + 1);
    deg.resize(n + 1);
    if (n < 3) {
        exit(0);
    }

    for (int i = 0; i < n - 1; i++) {
        int versh, child;
        cin >> versh >> child;
        graph[versh].push_back(child);
        graph[child].push_back(versh);
    }

    makePryuf();
}

