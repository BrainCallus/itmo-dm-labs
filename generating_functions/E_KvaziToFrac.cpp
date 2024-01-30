#include <iostream>
#include <vector>

using namespace std;
typedef long long LL;

const LL MOD = LLONG_MAX;
int r, d, degP;
vector<vector<LL>> degsQ;
vector<LL> kvaz, P;
vector<LL> a;

void evaluateDegsQ() {
    for (int k = 2; k < degsQ.size(); k++) {
        for (int i = 0; i < d + 3; i++) {
            LL mult = 0;
            for (int j = 0; j <= i; j++) {
                mult = (mult + ((j >= degsQ[1].size() ? 0 : degsQ[1][j]) *
                                (i - j >= degsQ[k - 1].size() ? 0 : degsQ[k - 1][i - j])) % MOD) % MOD;
            }
            degsQ[k].push_back(mult);
        }
    }
}

void evalA() {
    a.resize(d + 1);
    LL degR = 1;
    for (int i = 0; i < d + 1; i++) {
        LL degN = 1, sum = 0;
        for (long long j: kvaz) {
            sum += (j * degN) % MOD;
            sum %= MOD;
            degN *= i;
        }
        a[i] = (sum * degR) % MOD;
        degR *= r;
    }
}

void evalP() {
    degP = 0;
    P.resize(d + 1);
    for (int i = 0; i < d + 1; i++) {
        P[i] = a[i];
        for (int j = 1; j <= i; j++) {
            P[i] += degsQ[d + 1][j] * a[i - j];
        }
        if (P[i] != 0) {
            degP = i;
        }
    }
}


int main() {
    cin >> r >> d;
    kvaz.resize(d + 1);
    for (int i = 0; i <= d; i++) {
        cin >> kvaz[i];
    }
    degsQ.resize(d + 2);
    degsQ[0].assign(d + 3, 0);
    degsQ[1].assign(d + 3, 0);
    degsQ[0][0] = degsQ[1][0] = 1;
    degsQ[1][1] = -r;
    evaluateDegsQ();
    evalA();
    evalP();
    cout << degP << "\n";

    for (int i = 0; i <= degP; i++) {
        cout << P[i] << " ";
    }
    cout << "\n";
    cout << d + 1 << "\n";
    for (int i = 0; i <= d + 1; i++) {
        cout << degsQ[d + 1][i] << " ";
    }
}