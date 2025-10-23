#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin>>tt;
    while(tt--){
        int n;
        cin>>n;
        vector<bool> v(100);
        int temp;
        for(int i = 0; i < n; ++i){
            cin>>temp;
            v[temp] = true;
        }
        for(int i = 0; i < 100; ++i){
            if(!v[i]) {
                cout<<i<<endl;
                break;
            }
        }
    }
}
