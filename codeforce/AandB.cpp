#include<bits/stdc++.h>
using namespace std;
long long cal(vector<int> &pos){
    int n = pos.size();
    if(n <= 1) return 0;
    int median = pos[n/2];
    long long moves = 0;
    for(int i = 0; i < n; i++){
        moves += abs(pos[i] - (median - (n/2 - i)));
    }
    return moves;
}

using namespace std;
int main(){
    int tt;
    cin>>tt;
    while(tt--){
        int n;
        cin>>n;
        string s;
        cin>>s;
        vector<int> posA, posB;
        for(int i = 0; i < n; ++i){
            if(s[i] == 'a') posA.push_back(i);
            else posB.push_back(i);
        }
        long long ans = min(cal(posA), cal(posB));
        cout<<ans<<endl;
    }
    return 0;
}
