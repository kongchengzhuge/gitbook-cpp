#include<bits/stdc++.h>
using namespace std;

class Parent{
public:
    Parent(){
        function1();
        function2();
    }
    ~Parent(){
        function1();
        function2();
    }
    void function1(){
        cout<<"this is p func1"<<endl;
    }
    
    virtual void function2(){
        cout<<"this is p func2"<<endl;
    }
    
};

class Child:public Parent{
public:
    Child(){
        function1();
        function2();
    }
    ~Child(){
        function1();
        function2();
    }
    void function1(){
        cout<<"this is c func1"<<endl;
    }
    virtual void function2(){
        cout<<"this is c func2"<<endl;
    }
};

int main(){
    Parent parent;
    Child child;
    Parent* p=&child;
    p->function2();
    return 0;
}