#include <iostream>
#include<vector>
#include <algorithm>

using namespace std;

int n;
vector<pair<pair<int, int>, vector<int >>> leftLobe;
vector<int> matchingPair, prevMatch, indexes;
vector<bool> mark;

bool comp(const pair<pair<int, int>, vector<int >> &a, const pair<pair<int, int>, vector<int >> &b) {
    return a.first.second > b.first.second;
}

bool kun(int v) {
    if (!mark[v]) {
        mark[v] = true;
        for (int i = 0; i < leftLobe[indexes[v]].second.size(); i++) {
            int u = (leftLobe[indexes[v]].second)[i];
            if (matchingPair[u] == -1 || kun(matchingPair[u])) {
                matchingPair[u] = v;
                prevMatch[v] = u;
                return true;
            }
        }
    }

    return false;
}

void updateIndexes() {
    indexes.assign(n, -1);
    for (int i = 0; i < n; i++) {
        indexes[leftLobe[i].first.first] = i;
    }
}

void findMaxMatching() {
    matchingPair.assign(n, -1);
    prevMatch.assign(n, -1);
    updateIndexes();
    for (int i = 0; i < n; i++) {
        mark.assign(n, false);
        kun(leftLobe[i].first.first);
    }
    for (int i = 0; i < n; i++) {
        cout << prevMatch[i] + 1 << " ";
    }
}

int main() {
    freopen("matching.in", "r", stdin);
    freopen("matching.out", "w", stdout);
    cin >> n;
    leftLobe.resize(n);

    int w;
    for (int i = 0; i < n; i++) {
        cin >> w;
        leftLobe[i].first = {i, w};
    }
    for (int i = 0; i < n; i++) {
        int sz;
        cin >> sz;
        leftLobe[i].second.resize(sz);
        for (int j = 0; j < sz; j++) {
            cin >> leftLobe[i].second[j];
            leftLobe[i].second[j]--;
        }
    }
    sort(leftLobe.begin(), leftLobe.end(), comp);
    findMaxMatching();
}

