#include <iostream>
#include<vector>
#include<map>

using namespace std;
vector<int> pryuf;
vector<int> deg;
int n;

void makeTree() {
    int sz = pryuf.size();
    deg.assign(n + 1, 1);
    deg[0] = 0;
    for (int i = 0; i < sz; i++) {
        deg[pryuf[i]]++;
    }

    int pointr = 0;
    while (pointr < n + 1 && deg[pointr] != 1) {
        pointr++;
    }
    int leaf = pointr;

    vector<pair<int, int>> tree;
    for (int i = 0; i < sz; i++) {
        int v = pryuf[i];
        tree.emplace_back(leaf, v);
        deg[leaf]--;
        if (--deg[v] == 1 && v < pointr) {
            leaf = v;
        } else {
            pointr++;
            while (pointr < n && deg[pointr] != 1) {//
                pointr++;
            }
            leaf = pointr;
        }
    }
    for (int i = 1; i < n; i++) {
        if (deg[i] == 1) {
            tree.emplace_back(i, n);
        }
    }
    for (auto &i: tree) {
        cout << i.first << " " << i.second << "\n";
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n - 2; i++) {
        int pryufc;
        cin >> pryufc;
        pryuf.push_back(pryufc);
    }
    makeTree();
}


