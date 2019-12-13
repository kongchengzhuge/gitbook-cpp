# 技术

## 条款25：将constructor和non-member function虚化

开始听到虚构造函数的时候，我也吃了一惊。相信第一次看到这个的人都会惊讶。

看完这个条款的时候，我才知道，这个的虚构造函数只是那种意思。并不是声明virtual Class()这种构造函数。

常见的就是定义一个函数，返回一个base class指针，这个指针可以指向派生类。这种函数就类似一种虚构造函数

对于virtual copy constructor就更有意思了。c++甚至接受了当derived class重新定义其base class的一个虚函数时，不一定要返回值一样，如果base class虚函数返回值是一个指针或者引用，指向base class，那么derived class的返回值也可以这个base class的derived class，可以看下面代码，实现virtual copy constructor

```c++
class NLComponent{
public:
    virtual NLComponent*clone() const = 0;
}

class TextBlock: public NLComponent{
public:
    virtual TextBlock*clone(){
        return new TextBlock(*this);
    }
}

class Graphic: public NLComponent{
public:
    virtual Graphic*clone(){
        return new Graphic(*this);
    }
}
```

可以看到，上面函数的返回值和普通虚函数的不同之处。

***

## 条款26：限制某个class所能产生的对象数量

首先，这个条款举出如果希望最多只有一个对象的例子，那就是使用static，保证程序执行中，只有一个对象被产生。

但是这个不好拓展，如果希望是10个，那static也没办法。

于是在对象里加入一个number计数。调用构造函数的时候判断，如果超过了给定的次数，就throw一个异常。

但是，如果这个类被继承了，那么继承类初始化的时候也会调用这个类的构造函数。解决办法是将构造函数设置为private，publib空间有个自定义的构造函数调用原来的。

最后，将这个计数类做成一个基类，让想要有计数功能的类继承它即可。这时候构造函数需要声明为protect，如果是private的话，是不能提供继承的。

***

## 条款27：要求或禁止对象产生于heap中

首先来看要求对象产生在heap中，这就需要每次创建和销毁对象都用new和delete，而不能直接调用构造和析构函数。我们直接将构造函数或者析构函数设置为private即可。鉴于数量而言，将析构函数设置为private比较好。

然后是判断对象是否在heap中，鉴于现在操作系统一般都是讲stack设置在heap上面。所以直接比较对象和本地变量的地址即可，下面这个代码可以得到一个对象是否在heap中

```c++
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
```

最后是禁止对象产生于heap中，要想在堆中产生对象，必须调用new operator，我们不能改变这个操作符的行为。但是我们可以重载operator new，只要将对象operator new声明为private的即可

***

## 条款28：智能指针

智能指针大概就是用RAII的方法来管理指针，防止忘记delete而造成内存泄漏。

会专门有一个章节放auto_ptr的实现，代码部分就不多说。

在智能指针的构造函数中，需要注意的是拷贝构造函数。这取决于智能指针是如何被设计的。如果是只允许一个指针拥有，那就将所有权转移，如果是用引用计数设计的，那就将引用计数加一。

智能指针还必须重载*和->操作符为了和原始指针保持一致。

下面讲述一些智能指针进阶的部分

### 判断智能指针是否为NULL

在c++中，可以判断指针是否为0来判断是否为NULL，也可以用！操作符。

用智能指针想要提供上述功能，可以提供一个void*的隐式转换，但是这样的话，不同类的智能指针也能比较。

还有一种情况时重载！操作符，返回值是bool。这里存在的唯一问题就是有人用这种调用方式

```c++
SmartPtr<Apple> pa;
SmartPtr<Orage> po;

if(!pa==!po){
    ...
}
```

不过一般的程序员应该不会写出这样的语句

### 将Smart Pointers转换为Dumb Points

这里可以加入隐式转换，但是不好。因为智能指针本来就是一层封装。随意就能转换为原始指针违背了设计初衷

后续还有一些讨论，可以看看代码是如何实现

***

## 条款29：Reference counting（引用计数）

这是之前讲的lazy evaluation中引用计数的专门条款讲解。

基础部分就不多赘述了，本质上就是加了一个计数器。下面提一点特殊情况

**Copy-on-Write（写时复制）**

想像一下如果string类型是用引用计数实现的。对于复制构造，我们只需要简单的将引用计数加一即可。

但是string类型提供了operator[]这个操作符，这是可能改变string内部数据的。在修改内容的时候，我们必须复制出一个新的字符串。但是c++不会告诉你我们是写还是读。所以我们必须保证进行 operator[] 操作的对象的引用计数必须为1.

但是这种方法还是存在漏洞，如果程序首先得到 []返回的值的地址。然后再进行copy操作，之后再修改值。这就会导致后面那个字符串中的值也被修改。进一步修改的方法是，再定义一个shareable变量，如果进行了 operatoror[]操作，就将它改为false，否则为true。在copy的还是，首先检查shareable变量

