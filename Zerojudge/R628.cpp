#include <iostream>
#include <vector>
#include <algorithm>
using namespace std ;

const int MaxN = 2e5+1 ;
int N, num ;
int BIT[MaxN] = {} ;
pair<int,int> idx[100001] ;

int RangeQuery( int p )
{
    int ret = 0 ;
    while( 0 < p )
    {
        ret += BIT[ p ] ;
        p -= p & -p ;
    }
    return ret ;
}
void PointUpdate( int p, int x )
{
    while( p <= 2 * N )
    {
        BIT[ p ] += x ;
        p += p & -p ;
    }
}
int main()
{
    cin >> N ;
    for( int n = 1 ; n <= 2 * N ; n = n + 1 )
    {
        cin >> num ;
        if ( idx[ num ].first == 0 )
        {
            idx[ num ].first = n ;
        } 
        else
        {
            idx[ num ].second = n ;
        }
    }
    long ans = 0 ;
    for( int n = 1 ; n <= N ; n = n + 1 )
    {
        ans += RangeQuery( idx[n].second ) - RangeQuery( idx[n].first ) ;
        PointUpdate( idx[n].first, 1 ) ;
        PointUpdate( idx[n].second, 1 ) ;
    }
    cout << ans ;
}