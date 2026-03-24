#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> pref;
    int encCost, flatCost;
    unordered_map<long long, long long> memo;

    int getOnes(int l, int r) {
        return pref[r] - pref[l];
    }

    long long dfs(int l, int r) {
        long long key = ((long long)l << 32) | r;
        if (memo.count(key)) return memo[key];

        int len = r - l;
        int ones = getOnes(l, r);

        if (ones == 0) return memo[key] = flatCost;

        long long res = 1LL * len * ones * encCost;

        if (len % 2 == 0) {
            int mid = (l + r) / 2;
            res = min(res, dfs(l, mid) + dfs(mid, r));
        }

        return memo[key] = res;
    }

    long long minimumCost(string s, int e, int f) {
        encCost = e;
        flatCost = f;

        int n = s.size();
        pref.resize(n + 1, 0);

        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + (s[i] == '1');
        }

        return dfs(0, n);
    }
};