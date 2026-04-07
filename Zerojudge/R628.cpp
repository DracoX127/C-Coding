#include <iostream>
#include <vector>
using namespace std;

const int MaxN = 1e5 + 1; // maximum possible N
int N, num[MaxN], pos[MaxN]; 
// num[i] = value at index i
// pos[x] = index where value x appears (reverse lookup)

// Query prefix sum from 1 to p in BIT (Fenwick Tree)
int RangeQuery(vector<int>& BIT, int p){
    int ret = 0; // stores prefix sum result
    while(p > 0){
        ret += BIT[p];        // add current BIT node value
        p -= p & -p;          // move to parent (Fenwick Tree jump)
    }
    return ret; // sum from index 1 to p
}

// Add x to position p in BIT (Fenwick Tree)
void PointUpdate(vector<int>& BIT, int p, int x){
    while(p <= N){
        BIT[p] += x;          // add x at position p
        p += p & -p;          // move to next affected node
    }
}

int main(){
    cin >> N; // read number of elements
    // read input and build reverse position mapping
    for(int i = 1; i <= N; i++){
        cin >> num[i];        // value at position i
        pos[num[i]] = i;      // store where each value is located
    }
    vector<int> BIT(N+1, 0); // Fenwick Tree initialized to 0
    // initially, all positions are "alive" (value = 1)
    for(int i = 1; i <= N; i++){
        PointUpdate(BIT, i, 1); // mark position i as active
    }
    long long ans = 0; // total steps / cost
    int cur = pos[1]; // start from position of value 1
    // count how many active elements from 1 to cur
    ans += RangeQuery(BIT, cur) - 1;
    // remove current position (mark as 0)
    PointUpdate(BIT, cur, -1);
    // iterate from value 1 to N-1, moving to next value
    for(int i = 1; i < N; i++){
        int nxt = pos[i+1]; // position of next value
        if(cur < nxt) {
            // move forward: count active elements between cur and nxt
            ans += RangeQuery(BIT, nxt) - RangeQuery(BIT, cur);
        }
        else {
            // wrap around case:
            // from cur -> N, then 1 -> nxt
            ans += RangeQuery(BIT, N) - RangeQuery(BIT, cur) 
                 + RangeQuery(BIT, nxt);
        }
        // remove next position (mark visited)
        PointUpdate(BIT, nxt, -1);

        cur = nxt; // update current position
    }
    cout << ans << "\n"; // output final answer
}


// ===============================================
#include <iostream>
#include <vector>
using namespace std;

const int MaxN = 1e5 + 1; 
int N, num[MaxN], pos[MaxN]; 

int RangeQuery(vector<int>& BIT, int p){
    int ret = 0;
    while(p > 0){
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
    for(int i = 1; i <= N; i++){
        cin >> num[i];      
        pos[num[i]] = i;     
    }
    vector<int> BIT(N+1, 0); 
    for(int i = 1; i <= N; i++){
        PointUpdate(BIT, i, 1);
    }
    long long ans = 0; 
    int cur = pos[1]; 
    ans += RangeQuery(BIT, cur) - 1;
    PointUpdate(BIT, cur, -1);
    for(int i = 1; i < N; i++){
        int nxt = pos[i+1];
        if(cur < nxt) {
            ans += RangeQuery(BIT, nxt) - RangeQuery(BIT, cur);
        }
        else {
            ans += RangeQuery(BIT, N) - RangeQuery(BIT, cur) + RangeQuery(BIT, nxt);
        }
        PointUpdate(BIT, nxt, -1);

        cur = nxt; 
    }
    cout << ans << "\n"; 
}