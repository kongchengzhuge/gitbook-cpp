#include<bits/stdc++.h>
using namespace std;

int sz(int(&b)[13]){
    return sizeof(b)/sizeof(b[0]);
}

template<typename T,std::size_t S>
constexpr int SZ(T(&)[S]){
    return S;
}

template<typename Container,typename Index>
auto authAndAccess(Container&c,Index i)
->decltype(c[i])
{
    return c[i];
}

int main(){
    int b[13]{1,2,3,4,5,6,7,8,9,10,11,12,13};
    cout<<sz(b)<<endl;
    cout<<SZ(b)<<endl;
}