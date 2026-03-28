#include <iostream>
#include <vector>
using namespace std;

const int MaxN = 3e5;
int N;

int RangeQuery(vector<int>& BIT, int p){
    int ret = 0;
    while(0 < p){
        ret += BIT[p];
        p -= p & -p;
    }
    return ret;
}

void PointUpdate(vector<int>& BIT, int p, int x){
    while(p <= N){
        BIT[p] += x;
        p += p & -p;
    }
}

int main(){
    cin >> N;
    vector<int> A(N);
    for(int i = 0; i < N; i++) cin >> A[i];

    vector<int> BIT(N + 1, 0); 
    long long ans = 0;
    for(int i = N - 1; i >= 0; i--){  
        ans += RangeQuery(BIT, A[i]);  
        PointUpdate(BIT, A[i] + 1, 1); 
    }

    cout << ans << "\n";

    for(int i = 0; i < N - 1; i++){
        ans += (long long)(N - 1 - 2 * A[i]);  
        cout << ans << "\n";
    }
}