#include <iostream>
#include<vector>

using namespace std;
typedef long long LL;

const LL MOD = 998244353;
int n, m, sz;
vector<vector<LL>> degsP;

LL GCD(LL a, LL b, LL &x, LL &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    LL x1, y1;
    LL d = GCD(b % a, a, x1, y1);
    x = (y1 - ((b / a) * x1));
    y = x1;
    return d;
}

LL inversedEl(LL el) {
    LL x, y;
    if (GCD(el, MOD, x, y) != 1) {
        return 1;
    }
    return (x % MOD + MOD) % MOD;
}

void check(LL &elem) {
    if (elem < 0) {
        elem += MOD;
    }
}

void evaluateDegsP() {
    for (int k = 2; k < degsP.size(); k++) {
        for (int i = 0; i < sz + 1; i++) {
            LL mult = 0;
            for (int j = 0; j <= i; j++) {
                mult = (mult + ((j >= degsP[1].size() ? 0 : degsP[1][j]) *
                                (i - j >= degsP[k - 1].size() ? 0 : degsP[k - 1][i - j])) % MOD) % MOD;
                check(mult);
            }
            degsP[k].push_back(mult);
        }
    }
}

vector<LL> evaluateSqrt() {
    vector<LL> sqrt(sz + 2);
    sqrt[0] = 1;
    for (LL i = 1; i < sz + 1; i++) {
        sqrt[i] = (((MOD - sqrt[i - 1]) % MOD) * (((16 * i * i - 8 * i * i * i - 6 * i) + MOD) % MOD)) % MOD;
        sqrt[i] *= inversedEl(((i * i * 4 - 8 * i * i * i) + MOD) % MOD);
        sqrt[i] %= MOD;
        check(sqrt[i]);
    }
    return sqrt;
}

vector<LL> evaluateExp() {
    vector<LL> exp(sz + 2);
    exp[0] = 1;
    for (int i = 1; i < sz + 1; i++) {
        exp[i] = (exp[i - 1] * inversedEl(i)) % MOD;
        check(exp[i]);
    }
    return exp;
}

vector<LL> evaluateLog() {
    vector<LL> log(sz + 2);
    log[0] = 0;
    log[1] = 1;
    for (LL i = 2; i < sz + 1; i++) {
        log[i] = (((((MOD - log[i - 1]) % MOD) * (i - 1)) % MOD) * inversedEl(i)) % MOD;
        check(log[i]);
    }
    return log;

}

void getFunc(vector<LL> func) {

    for (int i = 0; i < m; i++) {
        LL term = 0;
        for (int j = 0; j < m; j++) {
            term = (term + (func[j] * degsP[j][i]) % MOD) % MOD;
            check(term);
        }
        cout << term << " ";
    }
    cout << "\n";
}

int main() {
    cout << (-5 % 7 + 7) * (-4 % 7 + 7) << "\n";
    cout << (-5 * -4) % 7;
    cin >> n >> m;
    sz = 100;
    degsP.resize(sz + 1);
    degsP[0].assign(sz + 1, 0);
    degsP[0][0] = 1;
    degsP[1].assign(sz + 1, 0);
    for (int i = 0; i < n + 1; i++) {
        cin >> degsP[1][i];
    }
    evaluateDegsP();
    getFunc(evaluateSqrt());
    getFunc(evaluateExp());
    getFunc(evaluateLog());
}