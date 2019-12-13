#include<bits/stdc++.h>
using namespace std;

int main(){
    string s1="abcdefg";
    string s2=s1;
    
    cout<<(s1.data()==s2.data())<<endl;

    char* s = const_cast<char*>(static_cast<const char*>(s1.c_str()));
    s[0]='x';
    s[1]='x';
    cout<<s1<<'-'<<s2<<endl;
}