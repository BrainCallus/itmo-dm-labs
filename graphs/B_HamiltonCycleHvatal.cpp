#include <iostream>
#include <vector>
#include<queue>

using namespace std;

int n;
vector<vector<int>> graph;

void pop(deque<int> &q) {
    while (!q.empty()) {
        cout << q.front() + 1 << " ";
        q.pop_front();
    }
}

void reversSubQueue(deque<int> &q, int i, int j) {
    for (int k = 0; k + i < j - k; k++) {
        int tmp = q[i + k];
        q[i + k] = q[j - k];
        q[j - k] = tmp;
    }
}

void hamiltonCycleHv() {
    deque<int> q;
    for (int i = 0; i < n; i++) {
        q.push_back(i);
    }

    for (int i = 0; i < n * (n - 1); ++i) {
        if (graph[q[0]][q[1]] != 1) {
            i = 2;
            while (i < n - 1 && (graph[q[0]][q[i]] != 1 || graph[q[1]][q[i + 1]] != 1)) {
                i++;
                if (i == n - 1 && (graph[q[0]][q[i]] != 1 || graph[q[1]][q[0]] != 1)) i++;
            }
            if (i >= n) {
                i = 2;
                while (graph[q[0]][q[i]] != 1) {
                    i++;
                }
            }
            reversSubQueue(q, 1, i);
        }
        q.push_back(q.front());
        q.pop_front();
    }
    pop(q);
}

int main() {
    cin >> n;
    graph.resize(n);
    for (int i = 0; i ^ n; i++) {
        graph[i].resize(n);
    }
    for (int i = 1; i ^ n; i++) {
        string matr;
        cin >> matr;
        for (int j = 0; j ^ matr.size(); j++) {
            graph[i][j] = (matr[j] == '1');
            graph[j][i] = graph[i][j];
        }
    }

    hamiltonCycleHv();
}