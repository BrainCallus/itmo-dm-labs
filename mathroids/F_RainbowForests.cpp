#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

int n, m;
vector<bool> colorAvailable, inIntersection;
set<int> rainbowForest;
vector<int> ancestor, rang, constAnces;

struct Rib {
    int start, end, color;
};
vector<Rib> ribs;

void buildDSU() {
    ancestor = constAnces;
    rang.assign(n, 1);
}

int findDSU(int x) {
    if (x != ancestor[x]) {
        ancestor[x] = findDSU(ancestor[x]);
    }
    return ancestor[x];
}

void unite(int x, int y) {
    x = findDSU(x);
    y = findDSU(y);
    if (rang[x] < rang[y]) {
        swap(x, y);
    }
    ancestor[y] = x;
    if (rang[x] == rang[y] && x != y) {
        rang[x]++;
    }
}


set<int> getShortestPath(vector<vector<int>> newGraph) {
    vector<bool> mark(m + 1, false);
    mark[m] = true;
    queue<int> q;
    q.push(m);
    vector<int> prev(m + 1);
    prev[m] = -1;
    set<int> path;
    int last = -1;
    //
    bool flag = false;
    while (!q.empty() && !flag) {
        int versh = q.front();
        q.pop();
        for (int i = 0; i < newGraph[versh].size(); i++) {
            int child = newGraph[versh][i];
            if (!mark[child]) {
                q.push(child);
                mark[child] = true;
                prev[child] = versh;
            }
            if (inIntersection[child]) {
                last = child;
                flag = true;
                break;
            }
        }
    }
    while (last != -1) {
        path.insert(last);
        last = prev[last];
    }
    return path;
}

vector<vector<int>> buildNewGraph() {
    vector<int> depend, independ;
    vector<vector<int>> newGraph(m + 1);
    auto ptr = rainbowForest.begin();
    for (int i = 0; i < m; i++) {
        if (ptr != rainbowForest.end() && i == *(ptr)) {
            independ.push_back(i);
            colorAvailable[ribs[i].color] = false;
            ptr++;
        } else {
            depend.push_back(i);
        }
    }

    for (int i: depend) {
        if (colorAvailable[ribs[i].color]) {
            newGraph[m].push_back(i);
        }
        for (int j: independ) {
            if (ribs[i].color == ribs[j].color || colorAvailable[ribs[i].color]) {
                newGraph[j].push_back(i);
            }
        }
    }
    inIntersection.assign(m, false);
    for (int i = 0; i < independ.size(); i++) {
        buildDSU();
        for (int j = 0; j < independ.size(); j++) {
            if (independ[i] != independ[j]) {
                unite(ribs[independ[j]].start, ribs[independ[j]].end);
            }
        }
        for (int j: depend) {
            if (findDSU(ribs[j].start) != findDSU(ribs[j].end)) {
                newGraph[j].push_back(independ[i]);
            }
        }
        unite(ribs[independ[i]].start, ribs[independ[i]].end);
        for (int j: depend) {
            if (findDSU(ribs[j].start) != findDSU(ribs[j].end)) {
                inIntersection[j] = true;
            }
        }
    }
    return newGraph;
}

void buildRainbow() {
    rainbowForest.insert(0);
    bool isMax = false;
    while (!isMax) {
        colorAvailable.assign(100, true);
        buildNewGraph();
        set<int> path = getShortestPath(buildNewGraph());
        path.erase(m);
        if (path.empty()) {
            isMax = true;
        } else {
            vector<int> prom(path.size() + rainbowForest.size());
            auto ptr = set_symmetric_difference(rainbowForest.begin(), rainbowForest.end(),
                                                path.begin(), path.end(), prom.begin());
            rainbowForest = set<int>(prom.begin(), ptr);
        }

    }
    cout << rainbowForest.size() << "\n";
    for (int i: rainbowForest) {
        cout << i + 1 << " ";
    }
}

int main() {
    freopen("rainbow.in", "r", stdin);
    freopen("rainbow.out", "w", stdout);
    cin >> n >> m;
    ribs.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> ribs[i].start >> ribs[i].end >> ribs[i].color;
        ribs[i].start--;
        ribs[i].end--;
        ribs[i].color--;
    }
    for (int i = 0; i < n; i++) {
        constAnces.push_back(i);
    }
    buildRainbow();
}

