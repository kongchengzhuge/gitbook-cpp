# 继承与面向对象设计

## 条款32：确定你的public继承塑模出is-a关系

“public继承”意味着is-a，适用于base class身上的每件事情一定也适用于drived class身上，因为每一个derived class对象也都是一个base class对象

***

## 条款33：避免遮掩继承来的名称

继承关系中的作用域和函数声明中的作用域其实很像。当前作用域中的会遮掩大作用域中的。

继承的函数也是，类如果重写了base class的函数，base class中被重写的函数将会被遮掩。这不是最恐怖的，因为很多情况下，你本来就想重写这个函数。

但是，如果base class有两个重载函数，就参数不同。drived class改写了其中一个函数，另一个函数也将被遮掩。因为函数名字是一样的。这里可以用using关键字来让父类作用域可见

***

## 条款34：区分接口继承和实现继承

接口继承和实验继承不同。在public继承之下，derived classes总是继承base class的接口

* pure virtual函数只继承具体的接口
* 非纯虚函数具体指定接口继承及缺省实现继承
* non-virtual函数具体指定接口继承以及强制性实现继承

***

## 条款35：考虑virtual函数以外的选择

这里讲的一种设计模式，感觉不是太感兴趣，就没有仔细阅读

***

## 条款36：绝不重新定义继承而来的non-virtual函数

如果是non-virtual函数，那么子类肯定是要保留父类这个性质的。所以不能改写。

***

## 绝不重新定义继承过来的缺省参数值

紧跟上一条款，如果重新定义，说明是virtual函数。virtual函数就代表动态绑定，会根据子类的性质执行相应的函数。但是问题就在于，缺省参数值（也就是默认参数）是静态绑定。如果父类指针指向子类对象，调用函数的时候，参数有默认值，这个默认值是静态的，但是函数确实调用的子类的。这就会存在问题。

不过上面问题仅仅会存在于子类重新定义了父类的缺省参数值。如果没有重新定义，那就不回存在问题。

***

## 条款39：明智而审慎的使用private继承

private继承意味着 is-implemented-in-terms-of（根据莫物实现出）他通常比复合的级别低。但是当drived class要访问base class的protect成员的时候，或者是重新定义继承而来的virtual func的时候，使用private是合理的

***

### 条款40：明智而审慎的使用多重继承

* 多重继承比单一进程复杂。可能会有歧义。必要的时候（比如钻石继承），需要virtual继承。
* 但是和使用virtual函数一样，如果使用virtual，会有额外的开销。会增加大小，速度，初始化复杂度等等成本。如果virtual base class不带有任何数据，将是最具有实用价值的情况


