#include <iostream>
#include <vector>
using namespace std;

const int MaxN = 3e5; // max array size (not strictly used here)
int N; // size of array

// Returns sum of elements from index 1 to p in BIT
int RangeQuery(vector<int>& BIT, int p){
    int ret = 0;
    while(0 < p){
        ret += BIT[p];       // add current node value
        p -= p & -p;         // move to parent in BIT
    }
    return ret;
}

// Adds x to position p in BIT
void PointUpdate(vector<int>& BIT, int p, int x){
    while(p <= N){
        BIT[p] += x;         // update current node
        p += p & -p;         // move to next responsible node
    }
}

int main(){
    cin >> N;              // read array size
    vector<int> A(N);
    for(int i = 0; i < N; i++) cin >> A[i];  // read array

    vector<int> BIT(N + 1, 0);  // Fenwick Tree, 1-based index
    long long ans = 0;           // stores total inversions

    // Loop from right to left to count initial inversions
    for(int i = N - 1; i >= 0; i--){  
        ans += RangeQuery(BIT, A[i]);      // count how many numbers <= A[i] are to the right
        PointUpdate(BIT, A[i] + 1, 1);     // mark A[i] as seen for future queries
    }

    cout << ans << "\n";        // print initial inversion count

    // Update inversion count for each rotation (first element to end)
    for(int i = 0; i < N - 1; i++){
        ans += (long long)(N - 1 - 2 * A[i]);  // net change of inversions after moving A[i] to end
        cout << ans << "\n";                    // print updated inversion count
    }
}

/*
Main logic: Count inversions by scanning the array from right to left using a Fenwick Tree (BIT). 
For each element, use the BIT to find how many smaller or equal numbers are already to its right 
(add to the inversion count), then mark this element as seen in the BIT. 
After that, simulate rotations efficiently: moving the first element to the end changes inversions by 
(N - 1 - 2 * A[i]) each time, so update the count directly without recomputing everything.
*/