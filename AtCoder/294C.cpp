#include <iostream>
#include <vector>
using namespace std;

const int MaxN = 1e5 + 1;
int N, M, A[MaxN], B[MaxN], C[MaxN * 2];

int main(){
    cin >> N >> M;
    for(int n = 1; n <= N; n++) cin >> A[n];
    for(int n = 1; n <= M; n++) cin >> B[n];
    int pa = 1, pb = 1;
    for(int pc = 1; pc <= N + M; pc++){
        if((A[pa] < B[pb] && pa <= N) || pb == M + 1){
            C[pc] = A[pa];
            A[pa] = pc;
            pa++;
        }
        else{
            C[pc] = B[pb];
            B[pb] = pc;
            pb++;
        }
    }
    for(int n = 1; n <= N; n++) cout << A[n] << " " ;
    cout << "\n" ;
    for(int n = 1; n <= M; n++) cout << B[n] << " " ;
}