#include <iostream>
#include<vector>

using namespace std;
typedef long long LL;

const LL MOD = 1000000007;
int m, k;
vector<bool> weights;

void calcTrees() {
    vector<LL> trie(m + 1), p(m + 1);
    p[0] = trie[0] = 1;
    for (int i = 1; i < m + 1; i++) {
        trie[i] = 0;
        for (int j = 1; j <= i; j++) {
            trie[i] = weights[j] ? (trie[i] + p[i - j]) % MOD : trie[i];
            p[i] = (p[i] + (trie[i - j] * trie[j]) % MOD) % MOD;
        }
        p[i] = (p[i] + trie[i]) % MOD;
        cout << trie[i] << " ";
    }
}

int main() {
    cin >> k >> m;
    weights.assign(m + 1, false);
    for (int i = 0; i < k; i++) {
        LL w;
        cin >> w;
        weights[w] = true;
    }
    calcTrees();
}