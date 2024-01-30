#include<iostream>
#include<algorithm>
#include<list>

using namespace std;

int n;
list<int> lamp;

bool ask(int i, int j) {
    cout.flush() << 1 << " " << i << " " << j << "\n";
    string answ;
    cin >> answ;
    return (answ._Equal("NO"));
}


int main() {
    cin >> n;
    if (n == 0) {
        cout << 0;
        exit(0);
    }
    for (int i = 1; i <= n; i++) {
        lamp.push_back(i);
    }

    lamp.sort(ask);

    cout << 0 << " ";
    for (int i = 0; i < n; i++) {
        cout.flush() << lamp.back() << " ";
        lamp.pop_back();
    }
    return 0;
}