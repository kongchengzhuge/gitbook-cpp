# lambda表达式

lambda表达式没有带来新的特性，任何能用lambda表达式实现的东西，都可以手动实现。但是，它确实给我们带来了方便。

## 条款31：避免默认捕获模式

lambda表达式的默认捕获方式有两种，一种是使用=执行按值捕获，一种是使用&执行按引用捕获。

这两种各有各的用处，各有各的好处。使用的时候应该仔细区分，不能直接使用默认情况。

* 按引用的默认捕获会导致空悬指针问题，这是因为捕获了局部变量，但是将闭包在超过局部作用域使用
* 按值的默认捕获极易受空悬指针的影响，并且会误导人们，lambda表达式是自洽的，也就是随处可以使用的。

***

## 条款32：使用初始化捕获将对象移入闭包

在c++14中，给lambda表达式加入了初始化捕获。初始化捕获有两个好处，一个是可以对捕获的变量命名，二是可以使用移动捕获了。

下面是代码示例

```c++
auto pw = std::make_unique<Widget>();
...
auto func = [pw=std::move(pw)](){
    return pw->isValidated()&&pw->isArchived();
};
```

对于c++11，没有这么好的支持，但是可以用std::bind实现类型效果

```c++
std::vector<double> data;

auto func=std::bind([](const std::vector<double>&data))
    {},std::move(data));
```

***

## 条款33：对auto&&型别的形参使用decltype，以std::forward之

前面条款也提到了，auto&&也是一个万能引用。c++14中lambda表达式也支持了auto&&型别。所以如果想到实现一个闭包，目的是转发参数，可以接受左右值，那么就要使用std::forward。

在之前使用std::forward的时候，它的模板都是T，但是这里我们使用auto接受参数。就需要使用decltype()得到参数类型了，代码如下

```c++
auto f = [](auto &&param)
{
    return func(normalize(std::forward<decltype(param)>(param)));
};
```

***

## 条款34：优先选用lambda式，而非std::bind

我对std::bind也不是太熟悉，大概就是知道能生成一个函数对象，可以绑定函数和参数。

下面把要点列一下

* lambda式比起使用std::bind而言，可读性更好，表达力更强，可能运行的效率也更高
* 仅在c++11中，std::bind实现移动捕获，或是绑定到具备模板化的函数调用运算符的对象的场合中，可能尚有余热可以发挥。
