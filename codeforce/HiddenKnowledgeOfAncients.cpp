#include<bits/stdc++.h>
using namespace std;

int numBound(vector<int> &arr, int start, int k, int l, int r){
	int x, y; // x denotes the 1st index when we get exactly k distinct elements, y denotes the 1st indexwhen we get exactly k+1 distinct elements
	map<int, int> m;
	x = -1, y = -1;
	for(int i = start; i < arr.size(); ++i){
		m[arr[i]]++;
		if(m.size() == k && x = -1) x = i;
		if(m.size() == k+1){
			y = i;
			break;
		}
	}
	if( x = -1) return 0;
	if( y = -1) y = n;
	int startCheck = x + l;
	if(startCheck >= arr.size()) return 0;
	int endCheck = min(x + r, arr.size() - 1);
	if(y <= startCheck) return 0;
	return min(y, endCheck) - startCheck + 1;
}

int main(){
	ios::sync_with_studio(false);
	cin.tie(nullptr);
	int tt;
	cin>>tt;
	while(tt--){
		int n, k, l, r;
		cin >> n >> k >> l >> r; // n = total size of array, k = required number of distinct elements, l = least, r = max.
		vector<int> arr(n);
		for(int i = 0; i < n; ++i){
			cin>>arr[i];
		}
		int ans = 0;
		for(int i = 0; i < arr.size(); ++i) ans += numBound(arr, i, k, l, r);
		cout<<ans<<endl;
		
	}
	return 0;
}
