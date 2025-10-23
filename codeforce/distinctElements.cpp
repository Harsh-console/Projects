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
        map<int, int> m;
        int b[n]{0};
        for(int i = 0; i < n; ++i) {
            cin>>b[i];
            m[b[i]]++;
        }
        int a[n];
        a[0] = 1;
        int t, d;
        for(auto val : m){
            if(val.second > 1) d = val.first;
        }
        for(int i = 0; i < n; ++i){
            t = b[i] - (2*b[i-1]);
            if(t == 1){
                a[i] = a[i-1] + 1; 
            }
            else if(t == 0){
                a[i] = d;
            }
            else{
                for(auto val : m) if(val.second == 1){
                    a[i] = val.first;
                    break;
                }
            }
        }
        for(int i = 0; i < n; ++i){
            cout<<a[i]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
