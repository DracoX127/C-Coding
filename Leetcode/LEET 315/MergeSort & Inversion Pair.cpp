#include <vector>
using namespace std;

class Solution {
public :
    vector<int> buff ;
    vector<int>  pos ;
    vector<int>  ans ;
    void MergeSort( int L, int R, vector<int>& nums ) {
        // 範圍裡面剩下一個數字時停止遞迴，範圍裡的數列由小到大排序
        if ( L == R ) 
            return ;
        // 範圍裡面有２個以上的數字時分成左右各半處理
        int M = ( L + R ) / 2 ;
        MergeSort(   L, M, nums ) ;
        MergeSort( M+1, R, nums ) ; 
        // BackTacking 回溯時合併左右半邊排序好的部分
        int pL = L ;
        int pR = M+1 ;
        for( int n = L ; n <= R ; n = n + 1 )
        {
            if ( ( pR == R+1 ) || ( pL <= M && nums[ pL ] <= nums[ pR ] ) )
            {
                buff[ n ] = nums[ pL ] ;
                pL = pL + 1 ;
            }
            else
            {
                buff[ n ] = nums[ pR ] ;
                pR = pR + 1 ;
            }
        } 
        for( int n = L ; n <= R ; n = n + 1 )
        {
            nums[ n ] = buff[ n ] ;
        }
    }
    vector<int> countSmaller( vector<int>& nums ) {
        buff.resize( nums.size() ) ;
         pos.resize( nums.size() ) ;
         ans.resize( nums.size() ) ;
        for( int n = 0 ; n < nums.size() ; n = n + 1 )
        {
            pos[ n ] = n ;
            ans[ n ] = 0 ;
        }
        MergeSort( 0, nums.size()-1, nums ) ;
        return ans ;
    }
} ;