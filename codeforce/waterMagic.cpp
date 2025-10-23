#include<bits/stdc++.h>
using namespace std;
int main(){
    int tt;
    cin>>tt;
    while(tt--){
        int n;
        cin>>n;
        int arr[n][n];
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                cin>>arr[i][j];
            }
        }
        int ans = 0;
        for(int i = 0; i < 2*n - 1; ++i){
            vector<int> tempV;
            for(int j = 0; j <= i; ++j){
                tempV.push_back(arr[i - j][j]);
            }
            auto it = min_element(tempV.begin(), tempV.end());
            if(*it < 0) ans += (-1)*(*it);
        }
        cout<<">>"<<ans<<endl;
    }
}
