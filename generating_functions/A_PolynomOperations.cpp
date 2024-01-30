#include <iostream>
#include<vector>

using namespace std;
typedef long long LL;

const LL MOD = 998244353;
int n, m;
vector<LL> coefsP;
vector<LL> coefsQ;

void addition() {
    cout << max(n, m) << "\n";
    for (int i = 0; i <= max(n, m); i++) {
        cout << ((i >= coefsP.size() ? 0 : coefsP[i]) + (i >= coefsQ.size() ? 0 : coefsQ[i])) % MOD << " ";
    }
    cout << "\n";

}

void multiplication() {
    cout << n + m << "\n";
    for (int i = 0; i <= n + m; i++) {
        LL mult = 0;
        for (int j = 0; j <= i; j++) {
            mult = (mult + (j >= coefsP.size() ? 0 : coefsP[j]) * (i - j >= coefsQ.size() ? 0 : coefsQ[i - j])) % MOD;
        }
        cout << mult << " ";
    }
    cout << "\n";
}

void division() {
    vector<int> antiQ(1001);
    antiQ[0] = 1;
    for (int i = 1; i < antiQ.size(); i++) {
        LL ant = 0;
        for (int j = 1; j <= i; j++) {
            ant = (ant + (j >= coefsQ.size() ? 0 : coefsQ[j]) * (antiQ[i - j]) + MOD) % MOD;
        }
        antiQ[i] = (MOD - ant) % MOD;
    }
    for (int i = 0; i < 1000; i++) {
        LL div = 0;
        for (int j = 0; j <= i; j++) {
            div = (div + (j >= coefsP.size() ? 0 : coefsP[j]) * (antiQ[i - j])) % MOD;
        }
        cout << div << " ";
    }
}

int main() {
    cin >> n >> m;
    coefsP.resize(n + 1);
    coefsQ.resize(m + 1);
    for (int i = 0; i < n + 1; i++) {
        cin >> coefsP[i];
    }
    for (int i = 0; i < m + 1; i++) {
        cin >> coefsQ[i];
    }
    addition();
    multiplication();
    division();
}


