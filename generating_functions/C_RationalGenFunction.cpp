#include <iostream>
#include<vector>

using namespace std;
typedef long long LL;

int k, degQ, degP;
vector<LL> Q;
vector<LL> P;
vector<LL> a;

void evalP() {
    degP = 0;
    P.resize(degQ);
    for (int i = 0; i < degQ; i++) {
        P[i] = a[i];
        for (int j = 1; j <= i; j++) {
            P[i] -= Q[j] * a[i - j];
        }
        if (P[i] != 0) {
            degP = i;
        }
    }
}

int main() {
    cin >> k;
    Q.resize(k + 1);
    a.resize(k);
    Q[0] = 1;
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }
    degQ = 0;
    for (int i = 1; i <= k; i++) {
        cin >> Q[i];
        if (Q[i] != 0) {
            degQ = i;
        }
    }
    evalP();
    cout << degP << "\n";
    for (int i = 0; i <= degP; i++) {
        cout << P[i] << " ";
    }
    cout << "\n";
    cout << degQ << "\n" << Q[0] << " ";
    for (int i = 1; i <= degQ; i++) {
        cout << -Q[i] << " ";
    }
}
