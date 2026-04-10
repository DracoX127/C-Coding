#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MaxN = 2e5;
int N;
int A[MaxN];
int B[MaxN];

struct NODE{
    int a, b;
}; NODE node[MaxN];

int RangeQuery( vector<int>& BIT, int p )
{
    int ret = 0 ;
    while( 0 < p )
    {
        ret += BIT[ p ] ;
        p -= p & -p ;
    }
    return ret ;
}
void PointUpdate( vector<int>& BIT, int p, int x )
{
    while( p < BIT.size() )
    {
        BIT[ p ] += x ;
        p += p & -p ;
    }
}

void solve(){
    for(int i = 0; i < N; i++) cin >> node[i].a;
    for(int i = 0; i < N; i++) cin >> node[i].b;

    sort(node, node + N, [](NODE lhs, NODE rhs){
        return lhs.a > rhs.a;
    });

    for(int n = 0; n < N; n++){
        cout << node[n].a << " " << node[n].b << endl;
    }
}

int main(){
    while(cin >> N) solve();
}