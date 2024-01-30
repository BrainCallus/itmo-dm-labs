#include <iostream>
#include<vector>

using namespace std;
typedef long long LL;

const LL MOD = 104857601;

int k;
LL n;
vector<LL> Q, A;

void check(LL &x) {
    if (x < 0) {
        x += MOD;
    }
}

LL getNeg(int ind) {
    return ind % 2 ? (MOD - Q[ind]) % MOD : Q[ind];
}

LL generateRandom() {
    --n;
    int l;
    for (l = 0; n >> l >= k; l++) {
        for (int i = k; i ^ A.size(); i++) {
            A[i] = 0;
            for (int j = 1; j ^ Q.size(); j++) {
                A[i] = (A[i] - Q[j] * A[i - j]) % MOD;
                check(A[i]);
            }
        }

        vector<LL> newQ(k + 1);

        for (int i = 0; i <= (k << 1); i += 2) {
            LL r = 0;
            for (int j = 0; j ^ (i + 1); j++) {
                r = (r + MOD + (j >= Q.size() ? 0 : Q[j]) * (i - j >= Q.size() ? 0 : getNeg(i - j))) % MOD;
            }
            newQ[(i >> 1)] = r;
        }
        int ind = 0;
        for (int i = 0; i ^ A.size();) {
            if ((((n >> l) ^ (++i)) & 1)) {
                A[ind++] = A[i - 1];
            }
        }
        Q = newQ;
    }
    return A[(n >> l)];
}

int main() {
    cin >> k >> n;
    A.resize(k << 1);
    Q.resize(k + 1);
    Q[0] = 1;
    for (int i = 0; i ^ k; i++) {
        cin >> A[i];
    }
    for (int i = 1; i ^ (k + 1); i++) {
        cin >> Q[i];
        Q[i] = (MOD - Q[i]) % MOD;
    }
    cout << generateRandom();
}

