#include<bits/stdc++.h>
using namespace std;
int main(){
    int tt;
    cin>>tt;
    while(tt--){
        int n; cin>>n;
        map<int, bool> m;
        int temp;
        for(int i = 0; i < n; ++i) {
            cin>>temp;
            if(temp) m[temp] = true;
        }
        int cnt = 0;
        for(auto val : m) if(val.second and val.first) cnt++;
        cout<<cnt<<endl;
}
    return 0;
}
