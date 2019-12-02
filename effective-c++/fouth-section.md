# 设计与声明

## 条款18：让接口容易被正确使用，不易被误用

这个条款说的主要是要将接口设计好，设计合理

***

## 条款19：设计class犹如type

设计一个类就要要设计一个新type，要考虑很多问题

* 如何创建和销毁
* 初始化和赋值有什么区别
* 等等

***

## 条款20：宁以pass-by-reference-to-const替换pass-by-value

这个条款无需多解释，在传递参数的时候防止拷贝构造函数即可

***

## 条款21：必须返回对象的时候，别妄想返回其reference

返回引用效率很高，但是不要所有地方都返回一个引用。最严重的就是返回的引用指向一个local stack对象。在函数结束的时候，对象会被销毁

***

## 条款22：将成员变量声明为private

## 条款23：宁以non-member、non-friend替换member函数

上面两个条款其实都是对于面向对象语言编程需要遵循的条款。成员使用private使得类更具有封装性。

在一些情况下，使用menber func是更好的。但是如果一个函数不是这个类的特性，就不要将其实现为menberfunc

***

## 条款24：若所有参数均需要类型转换，请为此采用non-member函数

在定义构造函数的时候，允许隐式转换，当一个对象呗认定为参数的时候。编译器会自动转换这个对象。但是如果是member func，调用方必须是一个member。可以看下面的例子

```c++
class Rational{
public:
    Rational(int numberator=0,
        int denominator=1);//允许int to Rational的隐式转换
    int numberator() const;
    int denominator() const;
private:
    ...
}

const Rational Rational::operator*(const Rational& rhs) const; //定义一

const Rational operator*(const Rational&lhs,const Rational&rhs);    //定义二

```

对于定义一，这种形式是不允许的 res=2\*tmp,但是对于定义二是允许的。定义二甚至可以 Rational res=2*2;

***

## 条款25：考虑写出一个不抛出异常的swap函数

* 当std::swap效率不高的时候，考虑自己实现一个menber swap，并确定这个函数不抛出异常
  * std::swap函数只会简单的调用拷贝构造，如果有效率更好的swap，可以尝试写
* 如果提供一个member swap，也应该提供一个non-member swap来调用前者

