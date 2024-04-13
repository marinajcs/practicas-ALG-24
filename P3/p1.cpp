#include <vector>
#include <iostream>
#include <cstdlib>
#include <set>
#include <algorithm>
#include <tuple>

//#define DEBUG
using namespace std;

typedef tuple<int, int, int> PairAndValue;

vector<pair<int,int>> P1_Greedy(vector<vector<int>> P) {
    int n = P.size();
    vector<pair<int,int>> S;  //solución
    vector<PairAndValue> C;   //candidatos
    vector<bool> U(n, false); //usados
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int matchValue = P[i][j] * P[j][i];
            C.push_back(make_tuple(i, j, matchValue));
        }
    }

    sort(C.begin(), C.end(), [](const PairAndValue& a, const PairAndValue& b) {
        return get<2>(a) > get<2>(b);
    });
    
    auto it = C.begin();
    while (!C.empty() && S.size() < n/2) {
        int i = get<0>(*it);
        int j = get<1>(*it);
        if (!U[i] && !U[j]) {
            U[i] = U[j] = true;
            S.push_back({i, j});
        }
        it = C.erase(it);
    }

    return S;
}

int main(int argc, char *argv[]) {
    vector<pair<int,int>> S;
    vector<vector<int>> P = {
        {-1, 2, 3, 4, 5, 6},
        {3, -1, 5, 2, 9, 10},
        {8, 2, -1, 6, 7, 1},
        {4, 6, 3, -1, 5, 2},
        {6, 5, 10, 8, -1, 2},
        {5, 3, 4, 3, 6, -1}
    };

    S = P1_Greedy(P);

    //#ifdef DEBUG
    for (int i = 0; i < S.size(); i++) {
        cout << "Pareja " << i+1 << ": " << S[i].first << " y " << S[i].second << endl;
    }
    //#endif

    return 0;
}
