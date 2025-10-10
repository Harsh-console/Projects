#include<bits/stdc++.h>
using namespace std;
int main(){
	int tt;
	cin>>tt;
	while(tt--){
		int n;
		cin>>n;
		vector<int> arr(n);
		map<int, int> m;
		for(int i = 0; i < n; ++i){
			cin>>arr[i];
			m[arr[i]]++;
		}
		cout<<m.size()<<endl;
	}
	return 0;
}
