#include <iostream>
#include <utility>
#include<vector>

using namespace std;
typedef long long LL;

class Parser {

private:
    int ind;
    int ANSWER_SZ;
    string expr;

    static LL CNK(LL n, LL k) {
        LL cnk = 1, i = n - k;
        while (i < n) {
            cnk *= ++i;
        }
        i = 1;
        while (i < k) {
            cnk /= ++i;
        }
        return cnk;
    }

    void printParsed(const vector<LL> &res) {
        for (long long re: res) {
            cout << re << " ";
        }
    }

    vector<LL> parseAll() {
        vector<LL> res(ANSWER_SZ);
        if (expr[ind] == 'B') {
            parseBase(res);
        } else {
            parseSuperStructure(res);
        }
        return res;
    }

    void parseSuperStructure(vector<LL> &res) {
        char type = expr[ind];
        ind += 2;
        vector<LL> first = parseAll();
        ++ind;
        switch (type) {
            case 'L': {
                parseSequence(first, res);
                break;
            }
            case 'S': {
                parseMultiSet(first, res);
                break;
            }
            case 'P': {
                parsePair(first, res);
                break;
            }
            default:
                break;
        }
    }

    void parseSequence(vector<LL> &first, vector<LL> &res) { // L
        res[0] = 1;
        for (int i = 1; i < ANSWER_SZ; i++) {
            LL sum = 0;
            for (int j = 1; j <= i; j++) {
                sum += res[i - j] * first[j];
            }
            res[i] = sum;
        }
    }

    void parseMultiSet(vector<LL> &first, vector<LL> &res) { // S
        res[0] = 1;
        vector<vector<LL>> matrix;
        matrix.assign(ANSWER_SZ, vector<LL>(ANSWER_SZ, 0));
        for (int i = 0; i < ANSWER_SZ; i++) {
            matrix[0][i] = 1;
        }
        for (int i = 1; i < ANSWER_SZ; i++) {
            for (int j = 1; j < ANSWER_SZ; j++) {
                LL sum = 0;
                for (int k = 0; k < i / j + 1; k++) {
                    sum += matrix[i - j * k][j - 1] * CNK(max(first[j] + k - 1, (LL) 0), k);
                }
                matrix[i][j] = sum;
            }
            res[i] = matrix[i][i];
        }

    }

    void parsePair(vector<LL> &first, vector<LL> &res) { // P
        vector<LL> second = parseAll();
        ++ind;
        for (int i = 0; i < ANSWER_SZ; i++) {
            LL sum = 0;
            for (int j = 0; j <= i; j++) {
                sum += first[j] * second[i - j];
            }
            res[i] = sum;
        }
    }

    void parseBase(vector<LL> &res) { //B
        res.assign(ANSWER_SZ, 0);
        res[1] = 1;
        this->ind++;
    }

public:

    Parser() {
        this->ind = 0;
        this->ANSWER_SZ = 0;
        this->expr = "";
    }

    ~Parser() {
        expr.clear();
        ind = 0;
        ANSWER_SZ = 0;
    }

    void parse(string description, int answ_sz) {
        this->ind = 0;
        this->ANSWER_SZ = answ_sz;
        this->expr = std::move(description);
        vector<LL> res(ANSWER_SZ);
        printParsed(parseAll());
    }
};

int main() {
    auto *parser = new Parser();
    string description;
    cin >> description;
    parser->parse(description, 7);
    parser->~Parser();
}
