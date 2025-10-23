#include<iostream>
using namespace std;
int main(){
    int a = 0;
    for(int i = 0; i < 10; ++i){
        if(i > 4){
            a = i;
            break;
        }
    }
    cout<<a;
    return 0;
}
