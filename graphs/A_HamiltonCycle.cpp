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

void hamiltonCycle() {
    deque<int> q;
    for (int i = 0; i < n; i++) {
        q.push_back(i);
    }

    for (int i = 0; i < n * (n - 1); i++) {
        if (graph[q[0]][q[1]] != 1) {
            i = 2;
            while (graph[q[0]][q[i]] != 1 || graph[q[1]][q[i + 1]] != 1 && i < n * (n - 1)) {
                i++;
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
    for (int i = 0; i < n; i++) {
        graph[i].resize(n);
    }
    for (int i = 1; i < n - 1; i++) {
        int versh, child;
        cin >> versh >> child;
        graph[versh].push_back(child);
        graph[child].push_back(versh);
    }

    hamiltonCycle();
}