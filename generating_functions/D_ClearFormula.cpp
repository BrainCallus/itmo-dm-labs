#include <iostream>
#include<vector>

using namespace std;
typedef long long LL;

const int MAXSZ = 10;
const LL MOD = LLONG_MAX;
int k, r;
vector<LL> P;
vector<vector<LL>> degsQ;
vector<pair<LL, LL>> coefs;

void check(LL &val) {
    if (val < 0) {
        val += MOD;
    }
}

LL GCD(LL a, LL b) {
    return b ? GCD(b, a % b) : a;
}

void evaluateDegsQ() {
    for (LL kk = 2; kk < degsQ.size(); kk++) {
        for (LL i = 0; i < 2 * MAXSZ + 1; i++) {
            LL mult = 0;
            for (LL j = 0; j <= i; j++) {
                mult = (mult + ((j >= degsQ[1].size() ? 0 : degsQ[1][j])
                                * (i - j >= degsQ[kk - 1].size() ? 0 : degsQ[kk - 1][i - j])) % MOD) % MOD;
            }
            degsQ[kk].push_back(mult);
        }
    }
}

void checkDenominetor(pair<LL, LL> &frac) {
    if (frac.second < 0) {
        frac.first = (-1 * frac.first) % MOD;
        frac.second = (-1 * frac.second) % MOD;
    }
}

pair<LL, LL> fracSum(pair<LL, LL> x, pair<LL, LL> y, bool minus) {

    LL gcd = GCD(x.second, y.second);
    LL top = (x.first * (y.second / gcd)) + ((minus ? -1 * y.first : y.first) * (x.second / gcd));
    LL bottom = x.second / gcd * y.second;
    gcd = GCD(top, bottom);
    return {top / gcd, bottom / gcd};
}

pair<LL, LL> multiply(pair<LL, LL> x, LL cnst) {
    LL gcd = GCD(x.first * cnst, x.second);
    return {x.first * cnst / gcd, x.second / gcd};
}

pair<LL, LL> divide(pair<LL, LL> x, LL cnst) {
    LL gcd = GCD(x.first, x.second * cnst);
    return {x.first / gcd, x.second * cnst / gcd};
}

void findCoefs() {
    coefs.resize(P.size());
    for (LL i = P.size() - 1; i >= 0; i--) {
        pair<LL, LL> sum = {P[i], 1};
        for (LL j = P.size() - 1; j > i; j--) {
            sum = fracSum(sum, multiply(coefs[j], degsQ[j][i]), true);
        }
        coefs[i] = divide(sum, degsQ[i][i]);
        checkDenominetor(coefs[i]);
    }
}

void precalcFac(vector<vector<LL>> &poly, vector<LL> &fac) {
    vector<LL> nextMul(2);
    nextMul[0] = 1;
    nextMul[1] = 1;
    fac[0] = 1;
    for (LL kk = 1; kk < poly.size(); kk++) {
        for (LL i = 0; i < 2 * MAXSZ + 1; i++) {
            LL mult = 0;
            for (LL j = 0; j <= i; j++) {
                mult = (mult + ((j >= nextMul.size() ? 0 : nextMul[j]) *
                                (i - j >= poly[kk - 1].size() ? 0 : poly[kk - 1][i - j])) % MOD) % MOD;
            }
            poly[kk].push_back(mult);
        }
        nextMul[0]++;
        fac[kk] = fac[kk - 1] * kk;
    }
}

void getKvazi() {
    vector<pair<LL, LL>> kvazi(k + 1);
    vector<vector<LL>> poly(k + 1);
    poly[0].assign(k + 2, 0);
    poly[0][0] = 1;
    vector<LL> fac(k + 1);
    precalcFac(poly, fac);

    for (LL i = k; i >= 0; i--) {
        pair<LL, LL> cur_coef = {0, 1};
        for (LL j = i; j <= k; j++) {
            cur_coef = fracSum(cur_coef, divide(multiply(coefs[k - j], poly[j][i]), fac[j]), false);
        }

        kvazi[i].first = cur_coef.first;
        kvazi[i].second = cur_coef.second;
        checkDenominetor(kvazi[i]);
    }
    for (auto &i: kvazi) {
        cout << i.first << "/" << i.second << " ";
    }
}


int main() {
    cin >> r >> k;
    P.resize(k + 1);
    for (LL i = 0; i <= k; i++) {
        cin >> P[i];
    }
    degsQ.resize(k + 2);
    degsQ[0].assign(MAXSZ, 0);
    degsQ[0][0] = 1;
    degsQ[1].assign(MAXSZ, 0);
    degsQ[1][0] = 1;
    degsQ[1][1] = -r;
    evaluateDegsQ();
    findCoefs();
    getKvazi();
}