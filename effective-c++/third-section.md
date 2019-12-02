# 资源管理

## 条款13：以对象管理资源

RAII，用类来管理资源，将得到的资源放入类中，调用析构函数的时候销毁数据，避免了手动释放

c++中常被使用的RAII class是share_ptr和auto_ptr，也就是智能指针

## 条款14：在资源管理类中小心copy行为

复制RAII对象一定要一并复制它所管理的资源，所以资源的行为决定RAII对象的copy行为。

RAII class 的copy行为有很多种：

* 抑制copying，不允许复制
* 施行引用计数法，类似的有share_ptr
* 直接转移资源，类似auto_ptr
* 自己定义其他的也行，但是一定要保证不能二次释放资源

## 条款15：在资源管理类中提供对原始资源的访问

APIs往往要求访问原始资源(raw resources)，所以每一个RAII class应该提供一个获得其原始资源的方法。获得方法有显式转换也有隐式转换

* 显示转换比较安全，调用get办法得到原始资源
* 隐式转换容易出错，但是对客户比较方便。

```c++
class Font{
public:
    ...
    FontHandle get() const {return f;} //显式转换
    operator FontHandle() const{    //隐式转换
        return f;
    }
    ...
};
```

## 条款16：成对使用new和delete时要采取相同的形式

这个条款意思就是 new和delete匹配 new []要和delete []匹配

## 条款17：以独立语句将newed对象置入智能指针

这个条款在于防止new的指针没有放入智能指针块中被管理