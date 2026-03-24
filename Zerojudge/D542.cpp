#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 500000 + 5;

long long BIT[MAXN];  
int bit, N;               

void bit_add(int idx, long long v) {
    while (idx <= bit) {
        BIT[idx] += v;
        idx += idx & -idx;
    }
}

long long bit_sum(int idx) {
    long long res = 0;
    while (idx > 0) {
        res += BIT[idx];
        idx -= idx & -idx;
    }
    return res;
}

int main() {
    while (cin >> N) {
        vector<long long> A(N);
        for (int n = 0; n < N; n++) cin >> A[n];
        vector<long long> B = A;
        sort(B.begin(), B.end());
        B.erase(unique(B.begin(), B.end()), B.end());
        vector<int> comp(N);
        for (int n = 0; n < N; n++) comp[n] = int(lower_bound(B.begin(), B.end(), A[n]) - B.begin()) + 1;
        bit = (int)B.size();
        for (int n = 0; n <= bit; n++) BIT[n] = 0;
        long long ans = 0;
        for (int n = N - 1; n >= 0; n--) {
            int x = comp[n];
            ans += bit_sum(x - 1); 
            bit_add(x, 1);
        }
        cout << ans << "\n";
    }
}
