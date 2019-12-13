#include<bits/stdc++.h>
using namespace std;

bool isInHeap(void*address){
    char c;
    return int(&c)>int(address);
}

int main(){
    int* inheap = new int(6);
    int c;

    cout<<isInHeap((void*)inheap)<<endl;
    cout<<isInHeap((void*)(&c))<<endl;
}
