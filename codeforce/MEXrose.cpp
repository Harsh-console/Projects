#include<bits/stdc++.h>
using namespace std;
int main(){
	int tt;
	cin>>tt;
	while(tt--){
		int n, k;
		cin>>n>>k;
		int cnt = 0;
		int temp;
		int cnt_ = 0;
		vector<int> v(k);
		for(int i = 0; i < n; i++){
			cin>>temp;
			if(temp < k) v[temp] = 1;
			if(temp == k) cnt_++;
		}
		for(int val : v){
			if(!val) cnt++;
		}
		cout<<max(cnt, cnt_)<<endl;
	}
	return 0;
}
