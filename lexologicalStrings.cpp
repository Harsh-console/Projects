#include<bits/stdc++.h>
using namespace std;
int main(){
	map<string, int> m;
	int N;
	cin >> N;
	string temp;
	for(int i = 0; i < N; ++i){
		cin>>temp;
		/*
		for(auto k : m){
			if(k.first == temp) k.second += 1;
			continue;
		}*/
		m[temp] += 1;
	}
	cout<<"STRING -> FREQUENCY"<<endl;
	for( auto k : m){
		cout<<k.first<<" "<<k.second<<endl;
	}
	return 0;
}
