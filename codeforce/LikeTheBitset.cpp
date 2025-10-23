#include<bits/stdc++.h>
using namespace std;
int main(){
	int tt;
	cin>>tt;
	while(tt--){
		// x + x*(10^i) = n
		// n = x(1 + 10^i)
		long long n;
		cin>>n;
		int cnt = 0;
		vector<long long> arr;
		long long num = 2;
		for(int i = 1; i < 21; ++i){
			num--;
			num*=10;
			num++;
			if(n % num == 0 and num ) {
				cnt++;
				arr.push_back(n / num); 
			}
		}
		cout<<cnt<<endl;
		if(cnt){
			for(int i = arr.size() - 1; i >= 0; --i){
				cout<<arr[i]<<endl;
			}
		}
	}
	return 0;
}
