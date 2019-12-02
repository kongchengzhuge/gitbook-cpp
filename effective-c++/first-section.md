# 让自己习惯c++

## 条款01：视c++为一个语言联邦

开始c++的出现只是在c上加了一点面向对象的特性，但是当语言逐渐成熟，它变得更加无拘无束，开始加入新的东西，主要有4种语言：

* C
  * 以C语言为基础
  * 很多东西来自C语言
* Object-Oriented C++：
  * class（构造和析构函数）
  * 封装
  * 继承
  * 多态
  * virtul函数 
* Template C++：
  * 模板元编程也是一种崭新的编程范式 
* STL
  * template程序库

***

## 条款02：尽量以const，enmu，inline替换#define

define是一种预处理器，不进入符号表。所以如果用define定义出错，是很难调试的。

如果想定义一种不可变的常量，使用const是没问题的。

如果想声明一种类专属的不可变常量，使用static const即可。这种对类专属的替换，define是坐不到的。如果编译器不支持，可以使用enmu

还有一种情况就是使用define定义一些简单的函数，这些函数直接替换，会没有调用开销。但是会存在很多问题。首先需要用括号将变量括起来，但这还不能完全解决问题。这时候，用inline就行，也是没有开销的。

***

## 条款03：尽可能使用const

* 将某些东西声明为const可以帮助编译器侦查出错误用法。const可以被施加于任何地方，对象，参数，返回值，成员函数本体。
  * 参数是经常碰到的地方，使用const引用
  * 返回值使用const修饰是为了不被改变，比如operator + 返回一个对象，如果不用const修饰，下面这种语法是可以通过的
  
  ```c++
   (a + b) = c
  ``` 
  
  * 成员函数加const是保证成员函数不会改变成员的值。这里需要注意的是，const函数可以算是一种重载

* 当const函数和非const函数有着实质性等价实现的时候，令非const函数调用const函数可以避免代码量过多，利如下转型方法调用

```c++
class TextBlock{
    public:
    ...
    const char& operator[](std::size_t position) const{
        ...
        return text[position];
    }
    char& operator[](std::size_t position){
        return 
            const_cast<char&>(
                static_cast<const TextBlock>(*this)
                    [position]
            );
    }
    ...
};
```

***

## 条款04：确定对象使用前已经被初始化

* c++并不会帮助你初始化变量，所以使用前一定要初始化，很多人默认未初始化的变量被定义为0，这是不对的

* 构造函数最好使用成员初始化列表，而不是在构造函数本体内使用赋值。初值列列出的成员变量，排列次序应该和定义他们的次序是一样的


