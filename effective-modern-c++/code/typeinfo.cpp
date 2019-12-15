#include<bits/stdc++.h>
using namespace std;

template<typename T>
class TD;

int main(){
    int x;
    int* y;
    const int c=5;
    const int* d=&x;
    const char* const e="adsf";
    int& f=x;
    const int& g=x;

    TD<decltype(x)> xType;
    TD<decltype(y)> yType;
    TD<decltype(c)> cType;
    TD<decltype(d)> dType;
    TD<decltype(e)> eType;
    TD<decltype(f)> fType;
    TD<decltype(g)> gType;
    //TD<decltype(x)> xType;
}