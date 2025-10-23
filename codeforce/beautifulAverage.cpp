#include<bits/stdc++.h>
using ll = long long;
#define INF  100000

using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin>>tt;
    while(tt--){
        int best = -INF;
        int n;
        cin>>n;
        int arr[n];
        for(int i = 0; i < n; ++i) cin>>arr[i];
        for(int i = 0; i < n; ++i){
            for(int j = i; j < n; ++j){
                int sum = 0;
                for(int k = i; k <= j; ++k){
                    sum += arr[k];
                }
                sum /= (j - i + 1);
                if(sum > best) best = sum;
            }
        }
        cout<<best<<endl;
    }
    return 0;
}
