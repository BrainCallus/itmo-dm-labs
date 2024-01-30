#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<pair<int, vector<int>>> S;
bool hasEmpty;

bool hasSubSum(int val) {
    for (auto &i: S) {
        if (i.first == val) {
            return true;
        }
    }
    return false;
}

bool satisfyFirst() {
    return hasEmpty;
}

bool satisfySecond() {
    vector<int> exists(1 << n, false);
    for (int i = 0; i < (1 << n); i++) {
        exists[i] = hasSubSum(i);

        for (int j = 0; (1 << j) <= i; j++) {
            exists[i] &= exists[(i & (~(1 << j)))];
        }

    }
    for (auto &i: S) {
        if (!exists[i.first]) {
            return false;
        }
    }
    return true;
}


bool satisfyThird() {
    for (int i = 0; i < S.size(); i++) {
        for (int j = i; j < S.size(); j++) {
            vector<int> a = S[i].second;
            vector<int> b = S[j].second;
            if (a.size() == b.size()) {
                continue;
            }
            int sumA = S[i].first, sumB = S[j].first;
            if (a.size() < b.size()) {
                swap(a, b);
                swap(sumA, sumB);
            }
            bool hasAddition = false;
            vector<int> substr(n);
            for (int k: a) {
                substr[k] = true;
            }
            for (int k: b) {
                substr[k] = false;
            }
            for (int k = 0; k < n; k++) {
                if (substr[k]) {
                    hasAddition |= hasSubSum(sumB | (1 << k));
                }
            }
            if (!hasAddition) {
                return false;
            }
        }
    }

    return true;
}


int main() {
    freopen("check.in", "r", stdin);
    freopen("check.out", "w", stdout);
    hasEmpty = false;
    cin >> n >> m;
    S.resize(m);
    for (int i = 0; i < m; i++) {
        int sz;
        cin >> sz;
        if (sz == 0) {
            hasEmpty = true;
        }
        int subsSum = 0;
        int el;
        for (int j = 0; j < sz; j++) {
            cin >> el;
            subsSum = subsSum | (1 << (--el));
            S[i].second.push_back(el);
        }
        S[i].first = subsSum;
    }


    if (satisfyFirst() && satisfySecond() && satisfyThird()) {
        cout << "YES";
    } else {
        cout << "NO";
    }
}
