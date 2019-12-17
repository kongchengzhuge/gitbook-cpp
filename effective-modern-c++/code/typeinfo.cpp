#include<bits/stdc++.h>
using namespace std;

template<typename T>
class TD;

class Widget{

};

int main(){
    int x;
    int* y;
    const int c=5;
    const int* d=&x;
    const char* const e="adsf";
    int& f=x;
    const int& g=x;
    auto func=[](int a,int b){return a==b;};
    auto func_auto=[](auto a,auto b){return a==b;};
    function<bool(const std::unique_ptr<Widget>&,
                const std::unique_ptr<Widget>&)>
        dereFUPLess = [](const std::unique_ptr<Widget>&p1,
                const std::unique_ptr<Widget>&p2){return *pa<*p2;};

    vector<bool> vb{true,true,true};
    auto& vb_res=vb[0];

    auto null=NULL;
    auto nptr=nullptr;

    TD<decltype(x)> xType;
    TD<decltype(y)> yType;
    TD<decltype(c)> cType;
    TD<decltype(d)> dType;
    TD<decltype(e)> eType;
    TD<decltype(f)> fType;
    TD<decltype(g)> gType;
    TD<decltype(func)> funcType;
    TD<decltype(func_auto)> func_autoType;
    TD<decltype(vb_res)> vb_resType;
    TD<decltype(null)> nullType;
    TD<decltype(nptr)> nptrType;
}