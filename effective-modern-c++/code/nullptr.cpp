#include<bits/stdc++.h>
using namespace std;

void f(int a){
    cout<<"this is int"<<endl;
}

void f(bool a){
    cout<<"this is bool"<<endl;
}

void f(void* a){
    cout<<"this is void*"<<endl;
}

int main(){
    f(0);
    //f(NULL);
    f(nullptr);
}