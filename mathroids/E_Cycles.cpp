#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<pair<int, int>> elems;
vector<int> cycles;
vector<bool> setAviable;

bool comp(pair<int, int> &a, pair<int, int> &b) {
    return a.second > b.second;
}

void addForbidden() {
    while (!cycles.empty()) {
        int curSet = cycles.back();
        cycles.pop_back();
        for (int i = 0; i < n; i++) {
            if (!(curSet & (1 << i))) {
                curSet |= (1 << i);
                if (setAviable[curSet]) {
                    cycles.push_back(curSet);
                    setAviable[curSet] = false;
                }
                curSet &= ~(1 << i);
            }
        }
    }
}

void findMaxBase() {
    addForbidden();
    int maxBaseW = 0, curSet = 0;
    for (int i = 0; i < n; i++) {
        if (setAviable[curSet | (1 << elems[i].first)]) {
            maxBaseW += elems[i].second;
            curSet |= (1 << elems[i].first);
        }
    }
    cout << maxBaseW;
}

int main() {
    freopen("cycles.in", "r", stdin);
    freopen("cycles.out", "w", stdout);
    cin >> n >> m;
    int w;
    for (int i = 0; i < n; i++) {
        cin >> w;
        elems.emplace_back(i, w);
    }
    sort(elems.begin(), elems.end(), comp);
    setAviable.assign((1 << n), true);
    for (int i = 0; i < m; i++) {
        int sz;
        cin >> sz;
        int subsSum = 0;
        int el;
        for (int j = 0; j < sz; j++) {
            cin >> el;
            subsSum |= (1 << (--el));
        }
        setAviable[subsSum] = false;
        cycles.push_back(subsSum);
    }
    findMaxBase();
}