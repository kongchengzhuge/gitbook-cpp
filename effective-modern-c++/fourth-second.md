# 智能指针

在古老的c++98中，只鞥你指针已经出现，那时候只有一个智能指针叫。auto_ptr，它考虑了指针所有权的问题，为了避免一个资源被析构两次。auto_ptr利用复制操作实现了它的移动操作。但是在c++11中。移动操作被合法话，能够合理的定义移动操作了。所以c++11利用行的unique_ptr替代了原来的auto_ptr。除此之外，c++11还定义了两个新的指针指针，分别是shared_ptr，和weak_ptr。

## 条款18：使用std::unique_ptr管理具备专属所有权的资源。

这个条款需要注意3点：

* std::unique_ptr是小巧的，高速的，具备只移动型的智能指针，对托管语义有专属移动权。
* 默认的，资源析构采用delete运算符来实现，但是支持自定义删除器。有状态的函数器和采用函数指针实现的删除器会增加std::unique_ptr的大小。但是使用函数指针一般会增加一个到两个字节。但是用一个对象，或者有捕获的lambda表达式增加的大小取决于对象的大小。
* 将std::unique_ptr转换为std::shared_ptr是简单的。

***

## 条款19：使用std::shared_ptr管理具备共享所有权的资源

std::shared_ptr的要点如下：

* std::shared_ptr能够再c++中实现类似垃圾回收功能，它是通过引用计数来实现对所有者个数的追踪
* shared_ptr尺寸是裸指针的两倍，它内部包含一个裸指针，还包含一个指向这个资源一用计数的指针
* 引用计数是动态分配，并且如果使用std::make_ptr来生成会节省资源
* 引用计数的递增和递减必须是原子操作

std::shared_ptr的构造函数通常会增加引用计数，但是只是通常。c++11中还有个特殊的移动构造函数，这个构造函数会将原来的指针置空，不会有引用计数的操作，所以会比复制构造函数快。

std::shared_ptr中最重要的一点就是它的控制块。控制块中有引用计数，弱计数和删除器一类的东西。这样以来，自定义的析构器就不会想unique_ptr一样，成为型别。拥有不同析构器的shared_ptr也能用一种vector存储。

控制块这么重要，里面还包含了析构函数，那么一个指针就只能有一个控制块。shared_ptr在这几种情况下会创建控制块。一定不能为一个指针创建多个控制块

* 使用std::make_sharedd 总是创建一个控制块
* 从具备专属所有权的指针（unique或者auto）构造一个std::shared_ptr时，会创建一个控制块
* 当std::shared_ptr的构造函数使用裸指针作为实参来调用时，它会创建一个控制块


***

## 条款20：对于类似std::shared_ptr但有可能空悬的指针使用std::weak_ptr

std::shared_ptr还有个问题，就是如果两个类互相引用。最后程序退出时，类不能被很好的析构。这时候，使用weak_ptr就能很好的避免这个问题。

在控制块中，shared_ptr管理引用计数，weak_ptr并不会好增加或者减少引用计数，只会影响其中的弱引用。weak_ptr也支持空悬。

***

## 条款21：优先选用std::make_unique和std::make_shared而非直接使用new

**理由1：**

```c++
auto upw(std::make_unique<Widget>());
std::unique_ptr<Widget> upw2(new Widget);
```

可以看到，使用make_unique，类名只需要写一次，对于很多类名很长的情况，这能减轻程序员的工作，并且减少出错的机会。

**理由2:**

第二个原因和安全有关。看下面代码

```c++
void processWidget(std::shared_ptr<Widget> spw,int priority);

//使用new调用
processWidget(std::shared_ptr<Widget>(new Widget),computePriority());

//使用make_shared调用
processWidget(std::make_share<Widget>(),computePriority());
```

对于使用new调用函数，这里存在内存泄漏的问题，由于你不知道new，compute函数和share_ptr构造函数的调用顺序。如果先new然后compute函数，在函数中出现了异常。那么new在堆上的空间就会泄漏。

但是使用make_shared不会存在这个问题，make_shared直接一步到位

**理由3：**

第三个原因和性能有关：

可以看理由1中的代码，使用new构建只能指正看似只有一次内存分配，但是shared_ptr还有控制块。所以，还会分配内存块的空间。这里就有两次内存分配。

但是使用make_shared来代替new的话。就只会有一次内存分配。会直接分配一个大块供对象和控制块的使用。这种分配方式还能减小程序的静态尺寸

当然，使用make_shared还是有一些不好的地方。首先，使用make不能自定义析构器。然后就是使用make_shared会直接分配一个大块。大块。但是在控制块中，不止有引用计数，还有weak_ptr的弱引用。引用计数为0的时候，并不会回收控制块。所以，当最后一个shared_ptr析构时，控制块并不能直接回收。需要最后一个weak_ptr析构。


***

## 条款22：使用Pimpl习惯用法时，将特殊成员函数的定义放到实现文件中：

这里说的Pimpl习惯用法大概意思就是定义和实现分离。符合设计模式开闭原则。

这里只把要点列出来：

* Pimpl惯用法通过降低类的客户和类实现者之间的依赖性，减少了构建遍数。
* 对于采用std::unique_ptr来实现pimpl指针，须在类的头文件中声明特种成员函数（如析构函数），但在特种文件中实现他们。即使默认函数实现有着正确的行为，也必须这么做。
* 上述建议不使用与std::shared_ptr


