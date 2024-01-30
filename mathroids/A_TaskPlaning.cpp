#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;
int n;
vector<pair<int, int>> delays;
vector<int> t;

vector<pair<int, int>> fill(vector<pair<int, int>> sourse, vector<pair<int, int>> target, int start, int finish) {
    for (int i = 0; i < finish; i++) {
        target[i] = sourse[i + start];
    }
    return target;

}

vector<pair<int, int>> merge(vector<pair<int, int>> a, vector<pair<int, int>> b) {
    int i = 0, j = 0;
    vector<pair<int, int>> c;
    c.resize(a.size() + b.size());
    while (i < a.size() || j < b.size()) {
        if (j == b.size() || i < a.size() && a[i].second < b[j].second) {
            c[i + j] = a[i];
            i++;
        } else {
            c[i + j] = b[j];
            j++;
        }
    }
    return c;
}

vector<pair<int, int>> mergeSort(vector<pair<int, int>> mas) {
    int len = mas.size();
    if (len <= 1) return mas;
    vector<pair<int, int>> l;
    l.resize(len / 2);
    vector<pair<int, int>> r;
    r.resize(len - len / 2);
    l = fill(mas, l, 0, len / 2);
    r = fill(mas, r, len / 2, len - len / 2);
    l = mergeSort(l);
    r = mergeSort(r);
    return merge(l, r);
}

int binUpper(int val) {
    int l = -1, r = t.size();
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (t[m] > val) {
            r = m;
        } else {
            l = m;
        }
    }
    return l;
}

LL minFine() {
    LL fine = 0;
    for (int i = n - 1; i >= 0; i--) {
        int ind = binUpper(delays[i].first);
        if (ind == -1) {
            fine += delays[i].second;
            t.erase(t.end() - 1);
        } else {

            t.erase(t.begin() + ind);
        }
    }
    return fine;
}

int main() {
    freopen("schedule.in", "r", stdin);
    freopen("schedule.out", "w", stdout);
    cin >> n;
    int d, w;
    for (int i = 1; i <= n; i++) {
        cin >> d >> w;
        delays.emplace_back(d, w);
        t.push_back(i);
    }
    delays = mergeSort(delays);

    cout << minFine();
}