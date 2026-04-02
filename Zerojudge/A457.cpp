#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MaxK = 1e5;
const long long MaxM = 2e9;
long long K, M;

struct REST{
    int first, second;
};
REST scores[MaxK];

int main(){
    cin >> K >> M;
    for(int i = 0; i < K; i++) cin >> scores[i].first;
    for(int i = 0; i < M; i++) cin >> scores[i].second;
    sort(scores, scores + K, [](const REST& lhs, const REST& rhs){
        return lhs.first < rhs.first;
    });
    for(int i = 0; i < K; i++) cout << scores[i].first << " " << scores[i].second << endl;
    long long max_y = scores[K - 1].second, ans = 0;
    cout << max_y << "\n";
    for(int i = K - 1; i > 0; i--){
      if(scores[i].second > max_y){
        max_y = scores[i].second;
        ans++;
      }
    }
    cout << ans;
}