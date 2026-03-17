#include <vector>
using namespace std;

class Solution {
public:
    vector<int> BIT;
    int RangeQuery(int p){
        int ret = 0;
        while(0 < p){
            ret += BIT[p];
            p -= p & -p;
        }
        return ret;
    }
    void PointUpdate(int p, int x){
        while(p <= 20001){
            BIT[p] += x;
            p += p & -p;
        }
    }
    vector<int> countSmaller(vector<int>& nums) {
        BIT.resize(20002);
        const int N = nums.size();
        for(int n = N - 1; n >= 0; n--){
            int x = nums[n] + 10001;
            nums[n] = RangeQuery(x - 1);
            PointUpdate(x, 1);
        }
        return nums;
    }
};