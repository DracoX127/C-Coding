#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MaxK = 1e5;
const long long MaxM = 2e9;
long long K, M;

int RangeQuery(vector<int>& BIT, int p){
    int ret = 0;
    while(0 < p){
        ret += BIT[p];
        p -= p & -p;
    }
    return ret;
}

void PointUpdate(vector<int>& BIT, int p, int x){
    while(p <= K){
        BIT[p] += x;
        p += p & -p;
    }
}

struct REST{
    int first, second; // first score for restaurant[a], second score for restaurant[b]
};
REST scores[MaxK];

int main(){
    cin >> K >> M;
    for(int i = 0; i < K; i++) cin >> scores[i].first;
    for(int i = 0; i < K; i++) cin >> scores[i].second;

    // sort by second asc, then first asc
    sort(scores, scores + K, [](const REST& lhs, const REST& rhs){
        if(lhs.second != rhs.second) return lhs.second < rhs.second;
        return lhs.first < rhs.first;
    });

    vector<int> BIT(K + 1);
    long long ans = 0;

    // now treat first[] as the permutation order, but since we just need
    // relative inversions, we can traverse and count how many seen so far
    // have first > current first
    // we map positions 1..K in the current order to BIT indices
    for(int i = K - 1; i >= 0; i--){
        int pos = i + 1;
        ans += RangeQuery(BIT, pos - 1);
        PointUpdate(BIT, pos, 1);
    }

    cout << ans << "\n";
}
