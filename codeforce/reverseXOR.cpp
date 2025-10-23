#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin>>tt;
    while(tt--){
        long long m;
        cin>>m;
        if(m == 0) {
            cout<<"YES"<<endl;
            continue;
        }
        vector<int> v(30);    
        bool state = true;
        for(int i = 0; i < 30; i++){
            if(m & (1<<i)) {
                v[i] = 1;
            }
            else v[i] = 0;
        }
            int n = log2(m) ;
            state = true;
            for(int i = 0; i < n/2; i++){
                if(v[n-i-1] != v[i]) {
                    state = false;
                    break;
                }
            }
            if(state){
                cout<<"YES"<<endl;
            }
            else cout<<"NO"<<endl;
    }
    return 0;
}
