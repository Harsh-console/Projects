#include<bits/stdc++.h>
using namespace std;

void convertBinary(vector<int> &v, int n, int length){
	for(int i = 0; i < length; ++i){
		if(n & (1<<i)) v.push_back(1);
		else v.push_back(0);
	}
}

void print(vector<int> arr){
	for(int i = 0; i < arr.size(); ++i){
		cout<<arr[i]<<" ";
	}
}

int main(){
	int tt;
	cin>>tt;
	while(tt--){
		int x, y, z;
		cin>>x>>y>>z;
		bool ans = true;
		vector<int> X;
		vector<int> Y;
		vector<int> Z;
		convertBinary(X, x, 64);
		convertBinary(Y, y, 64);
		convertBinary(Z, z, 64);
		for(int i = 0; i < 64; ++i){
			if(((X[i] == 0) + (Y[i] == 0) + (Z[i] == 0)) == 1) ans = false;
		}
		if(ans) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;

	}
	return 0;
}
