简单C++标准模板库（Standard Template Library）的实现
==========================
[STL 技术实现简要分析](http://blog.csdn.net/chengonghao/article/category/6216131 "CSDN")

[关于作者](profile.md)

#项目简介
        出于学习 C++ 标准库的目的而造的轮子。
        
        实现了基本的空间配置器、迭代器、容器、算法、仿函数、配接器。
        
        空间配置器的实现 allocator 文件夹
        
        迭代器的实现位于 iterator 文件夹
        
        序列式容器的实现位于 sequence containers 文件夹
        
        关联式容器的实现位于 associative containers 文件夹
        
        算法的实现位于 algorithms 文件夹
        
        仿函数的实现位于 function objects 文件夹
        
        配接器的实现位于 adapters 文件夹
        
        所有的测试文件都放在 test 文件夹
        
        version 文件夹存放着各个时期的版本


#使用方法
    1、在 version 目录下下载最新版的源码
    
    2、根据功能，引入需要的头文件（#include）


