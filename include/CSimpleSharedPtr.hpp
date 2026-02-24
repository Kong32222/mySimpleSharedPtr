#ifndef _CSIMPLESHAREDPTR_H_
#define _CSIMPLESHAREDPTR_H_

#include <iostream>

template <typename T>
class CSimpleShared_prt
{
public:
    // 防止 写 CSimpleShared_prt<CPrintHello> p_Print2 ; 报错。因为这个时候的成员变量都是未知的

    // 构造：接管一个裸指针
    explicit CSimpleShared_prt(T *p = nullptr)
        : ptr(p)  //, ref_count(new int(1))
    {
        if (ptr)
            ref_count = new int(1);
        else
            ref_count = nullptr;

        std::cout << "构造ctor, count = "
                  << (ref_count ? *ref_count : 0) << std::endl; 
    }

    // 拷贝构造：共享所有权(ref_count 数值是一样的)
    CSimpleShared_prt(const CSimpleShared_prt &other)
        : ptr(other.ptr),
          ref_count(other.ref_count)
    {
        ++(*ref_count);
        std::cout << "copy构造 ctor, count = " << *ref_count << std::endl;
    }

    // 拷贝赋值
    /*注意 因为ref count 是不一定开辟空间的，所以访问要注意*/
    CSimpleShared_prt &operator=(const CSimpleShared_prt &other)
    {
        if (this != &other)
        {
            release();
           
            ptr = other.ptr;
           
            //顺序一定不能乱，一定是外部的指针 赋值给this，this才可以++，或者就是++外部的count
            ref_count = other.ref_count;
             ++(*ref_count); //都++;    
            if(ref_count)
                std::cout << "copy operator= ctor, count = " << *ref_count << std::endl;
        }
        return *this;
    }

    //移动拷贝
    CSimpleShared_prt(CSimpleShared_prt &&other) noexcept
        : ptr(other.ptr), ref_count(other.ref_count)
    {
        other.ptr = nullptr;
        other.ref_count = nullptr;
        // other.ref_count = new int(0);
        std::cout << "move ctor\n";
    }

    // 析构
    ~CSimpleShared_prt()
    {
        release();
    }

    // 像指针一样用
    T *operator->() const { return ptr; }
    T &operator*() const { return *ptr; }

    int use_count() const
    {
        if (ref_count)
            return *ref_count;
        else
            return 0;
    }

private:
    void release()
    {
        if (!ref_count)
        {
            std::cout << " ref_count is null 不是错误\n";
            return;
        }

        
        if (--(*ref_count) == 0)
        {
            std::cout << "delete managed object\n";
            delete ptr;
            delete ref_count;
        }

        ref_count = nullptr;
        ptr = nullptr;
        
    }

private:
    T *ptr;         // 被管理的对象
    int *ref_count; // 引用计数（共享的）
};

#endif
