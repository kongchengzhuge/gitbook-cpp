# 实现

## 条款26：尽可能延后变量出现的时间

可能存在定义好的变量最后没有被用上的情况。所以要尽可能的延后变量定义的时间。

***

## 条款27：尽量少做转型动作

c++相比于c，提供了4个新的转型动作

* const_cast:用来剔除对象的常量性
* dynamic_cast:用来执行父类到子类的转型
* reinterpret_cast:执行低级转型
* static_cast:除了上面的几种特殊转型，一般都是用这个转型

如果需要转型，尽量使用新式转型，而不是旧式转型。新式转型容易被被辨识出来。

如果可以，尽量避免转型，特别是在注重效率的代码中使用dynamic_cast，这是很慢的。

***

## 条款28：避免返回handles指向对象内部成分

这个和避免返回local stack变量的引用是一个道理。对象也容易被销毁，之后产生悬空handle

***

## 条款29：为异常安全而努力是值得的

异常安全函数分为3种：基本型，强烈型，不抛异常型

对于强烈型，要不就是完成调用，要不就返回到开始的状态，这个可以用copy and swap实现

***

## 条款30：了解inlining的里里外外

inline函数效率很高，之前在defing模块也提到了。但是inline只适用于小型函数，对于大型函数而言使用inline是一种灾难。

首先，如果你想得到一个inline函数的函数指针，编译器还是会为这个函数生成一个函数本体。甚至你没有想去得到函数指针，编译器回去得到构造函数和析构函数的函数指针。如果将构造函数和析构函数inline，这是个不好的行为，会有大量的重复代码。

inline函数还不好调试，在调试期只能关闭inline

***

## 条款31：将文件间的编译依赖关系降到最低

这个条款大概就是告诉大家如何放置声明与定义

支持“编译依存性”最小化的一般构想是：相依与声明式，不要相依与定义式。如果只依赖于声明式，在改变结构的时候。重新编译只需要修改定义代码。如果依赖于定义式，还需要修改调用代码

程序头文件应该完全只有声明式