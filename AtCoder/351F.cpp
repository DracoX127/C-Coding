#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MaxN = 4e5;
int N, A[MaxN];

/// Fenwick Tree query: sum from 1 → p
long long RangeQuery(vector<long long>& BIT, int p){
    long long ret = 0;
    while(p > 0){
        ret += BIT[p];
        p -= p & -p;
    }
    return ret;
}

/// Fenwick Tree update: add x at position p
void PointUpdate(vector<long long>& BIT, int p, long long x){
    while(p < (int)BIT.size()){
        BIT[p] += x;
        p += p & -p;
    }
}

int main(){
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> A[i];
    }

    /// pool = (value, index)
    vector<pair<int,int>> pool;
    for(int i = 0; i < N; i++){
        pool.push_back(make_pair(A[i], i + 1)); // 1-based index
    }

    /// sort descending by value
    sort(pool.begin(), pool.end(), greater<pair<int,int>>());

    /// two BITs:
    /// count of elements, and sum of elements
    vector<long long> BIT_cnt(N + 1), BIT_sum(N + 1);

    long long ans = 0;

    /// process from largest → smallest
    for(int i = 0; i < N; i++){
        int val = pool[i].first;
        int idx = pool[i].second;

        /// query suffix [idx, N]
        long long cnt = RangeQuery(BIT_cnt, N) - RangeQuery(BIT_cnt, idx - 1);
        long long sum = RangeQuery(BIT_sum, N) - RangeQuery(BIT_sum, idx - 1);

        /// contribution
        ans += sum - cnt * val;

        /// add current element into BIT
        PointUpdate(BIT_cnt, idx, 1);
        PointUpdate(BIT_sum, idx, val);
    }

    cout << ans << "\n";
}

// No comments version ==================
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MaxN = 4e5;
int N, A[MaxN];

long long RangeQuery(vector<long long>& BIT, int p){
    long long ret = 0;
    while(p > 0){
        ret += BIT[p];
        p -= p & -p;
    }
    return ret;
}

void PointUpdate(vector<long long>& BIT, int p, long long x){
    while(p < (int)BIT.size()){
        BIT[p] += x;
        p += p & -p;
    }
}

int main(){
    cin >> N;
    for(int i = 0; i < N; i++) cin >> A[i];
    vector<pair<int,int>> pool;
    for(int i = 0; i < N; i++){
        pool.push_back(make_pair(A[i], i + 1)); 
    }
    sort(pool.begin(), pool.end(), greater<pair<int,int>>());
    vector<long long> BIT_cnt(N + 1), BIT_sum(N + 1);
    long long ans = 0;
    for(int i = 0; i < N; i++){
        int val = pool[i].first;
        int idx = pool[i].second;
        long long cnt = RangeQuery(BIT_cnt, N) - RangeQuery(BIT_cnt, idx - 1);
        long long sum = RangeQuery(BIT_sum, N) - RangeQuery(BIT_sum, idx - 1);
        ans += sum - cnt * val;
        PointUpdate(BIT_cnt, idx, 1);
        PointUpdate(BIT_sum, idx, val);
    }

    cout << ans << "\n";
}