# 定制new和delete

## 条款49：了解new-handle的行为

new-handle和single-handle很像。new-handle是一个函数，当operator new无法满足某一份内存分配需求的时候。他会抛出异常。在抛出异常之前，它会先调用new-handle来处理异常。

通过set-new-handle来设置new-handle。这个返回值是原来的new-handle，如果要得到当前的new-handle，可以这么写函数

```c++
typedef void (*new_handle)();
new_handle set_new_handle(new_handle p) throw();

new_handle current_handle=set_new_handle(0);//得到当前的
set_new_handle(p);  //将之前的处理函数设置回去
```

当operator new无法满足内存申请的时候，会调用new-handle函数，直到找到足够的内存，一个好的new-handle函数必须做如下事情：

* 让更多的内存被使用
* 安装另一个new-handle，如果存在的问题，另一个new-handle能处理，便调用并且安装另一个new-handle。于是在下一次循环的时候，能够重新handle
* 卸除new-handle：在处理不了问题的时候，卸除new-handle。最后new会抛出一个异常
* 抛出bad_alloc
* 不返回

***

## 条款50：了解new和delete的合理替换时机

一般用来替换编译器提供的new和delete有三个最常见的理由

* 用来检测运用上的错误：比如在分配的内存前后加上校验位，缺点在于对于体系结构的齐位没有把握好
* 为了强化效能：特定情况下，自己定制的new和delete效率更高
* 为了收集统计数据：查看你的软件如何使用其动态内存

***

## 条款51：编写new和delete时需固守常规

首先需要知道，new在传入0的时候，也能正常工作，这时候new将0变为1，最后返回分配的一个字节的地址

而delete在收到null指针的时候，应该不干任何事

还需要加入new_handle，加入while循环一直处理

这里尤其需要注意的就是，对于class版本的new和delete。在分配和删除之前都需要检查size是否对的上现在的对象，因为drived class也会继承。对于drived class，不能调用原来的new和delete

***

## 条款52：编写了placement new也要编写placement delete

我之前只知道，placement new是加入一个参数，参数代表对象被new的位置。这次读完之后我才知道自己片面了。

只要加入了参数，就算placement new。只是上面说的那个被用的最多，被加入到了c++标准库。

这个条款的重点是，如果你调用了placement new，但是用普通的delete将空间释放，这是不对的。并且，如果new成功，但是在构造一个对象的时候失败，编译器会自动帮你调用相应的delete函数。也即是placement delete。如果没有定义也是不行的。

缺省情况下，编译器会为在global作用域提供如下形式的operator new

```c++
void* operator new(std::size_t) throw(std::bad_alloc) //normal new
void* operator new(std::size_t,void*) throw(); //placement new
void* operator new(std::size_t,const std::nothrow_t&) throw (); //nothrow new
```

但是之前的条款也提到了，如果再类里重载了函数，会在大的定义域遮掩他们。要避免这种的简单做法就是，建立一个base class，里面有所有的正常形式的new和delete，用户可以用继承加using声明式取得标准

```c++
class StandardNewDeleteForms{
public:
    //normal new/delete
    static void* operator new(std::size_t size) throw(std::bad_alloc){
        return ::operator new(size);
    }
    static void operator delete(void* pMemory) throw(){
        ::operator delete(pMemory);
    }

    //placement new/delete
    static void* operator new(std::size_t size,void* ptr) throw(){
        return ::operator(size,ptr);
    }
    static void operator delete(void* pMemory,void* ptr) throw(0){
        ::operator delete(pMemory,ptr);
    }

    //nothrow new/delete
    static void* operator new(std::size_t size,const std::nothrow_t&nt) throw(){
        return ::operator(size,nt);
    }
    static void operator delete(void* pMemory) throw(0){
        ::operator delete(pMemory);
    }
}
```
