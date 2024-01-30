#include <iostream>
#include<vector>
#include <algorithm>

using namespace std;

typedef uint64_t LL;
size_t n, m;
LL s, graphW;
vector<pair<int, pair<pair<int, int>, LL>>> ribs;
vector<bool> mark;
vector<int> ancestor;
vector<int> rang;

bool comp(pair<int, pair<pair<int, int>, LL>> ribs1, pair<int, pair<pair<int, int>, LL>> ribs2) {
    return ribs1.second.second > ribs2.second.second;
}

void build() {
    ancestor.resize(n);
    rang.resize(n);
    for (int i = 0; i < n; i++) {
        ancestor[i] = i;
        rang[i] = 1;
    }
}

int find(int x) {
    if (ancestor[x] != x) {
        ancestor[x] = find(ancestor[x]);
    }
    return ancestor[x];
}

void unionDSU(int x, int y) {
    x = find(x);
    y = find(y);
    if (rang[x] < rang[y]) {
        swap(x, y);
    }
    ancestor[y] = x;
    if (rang[x] == rang[y]) {
        rang[x]++;
    }
}

LL MaxST() {
    sort(ribs.begin(), ribs.end(), comp);
    build();
    LL spanTreeW = 0;
    for (int i = 0; i < m; i++) {
        int u = ribs[i].second.first.first;
        int v = ribs[i].second.first.second;
        LL w = ribs[i].second.second;
        if (find(u) != find(v)) {
            unionDSU(u, v);
            mark[ribs[i].first] = true;
            spanTreeW += w;
        }
    }
    return spanTreeW;
}

void addMax(LL maxSpTreeW) {
    int cur = 0;
    while (s + maxSpTreeW < graphW) {
        if (!mark[ribs[cur].first]) {
            mark[ribs[cur].first] = true;
            maxSpTreeW += ribs[cur].second.second;
        }
        cur++;
    }
}

void destruct() {
    vector<int> numbers;
    for (int i = 0; i < m; i++) {
        if (!mark[ribs[i].first]) {
            numbers.push_back(ribs[i].first + 1);
        }
    }
    sort(numbers.begin(), numbers.end());
    cout << numbers.size() << "\n";
    for (int number: numbers) {
        cout << number << " ";
    }
}

int main() {
    freopen("destroy.in", "r", stdin);
    freopen("destroy.out", "w", stdout);
    cin >> n >> m >> s;
    graphW = 0;
    mark.assign(m, false);
    int versh, child;
    LL w;
    for (int i = 0; i < m; i++) {
        cin >> versh >> child >> w;
        graphW += w;
        ribs.push_back({i, {{versh - 1, child - 1}, w}});
    }

    addMax(MaxST());
    destruct();
}

