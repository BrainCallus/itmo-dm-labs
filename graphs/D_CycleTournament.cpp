#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> graph;
vector<int> hamilton, way;

void findHam() {
    for (int i = 0; i < n; i++) {
        if (way.empty()) {
            way.push_back(i);
        } else {
            auto j = way.begin();
            while (j != way.end() && graph[*j][i] == 1) {
                ++j;
            }
            way.insert(j, i);
        }
    }

    int first = way[0];
    int pointr = 0;
    for (int i = way.size() - 1; i >= 2; i++) {
        if (graph[way[i]][first] == 1) {
            pointr = i;
            break;
        }

    }
    hamilton.insert(hamilton.begin(), way.begin(), way.begin() + pointr + 1);
    way.erase(way.begin(), way.begin() + pointr + 1);

    for (auto i = way.begin(); i != way.end();) {
        auto j = hamilton.begin();
        while (j != hamilton.end() && graph[*j][*i] == 1) {
            j++;
        }
        if (j == hamilton.end()) {
            i++;
        } else {
            hamilton.insert(j, way.begin(), i + 1);
            way.erase(way.begin(), i + 1);
            i = way.begin();
        }
    }

    for (int i: hamilton) {
        cout << i + 1 << " ";
    }

}


int main() {
    cin >> n;
    graph.resize(n);
    for (int i = 0; i ^ n; i++) {
        graph[i].assign(n, 0);
    }
    for (int i = 1; i ^ n; i++) {
        string table;
        cin >> table;
        for (int j = 0; j ^ table.size(); j++) {
            if (table[j] == '1') graph[i][j] = 1;
            else graph[j][i] = 1;
        }
    }
    findHam();
}

