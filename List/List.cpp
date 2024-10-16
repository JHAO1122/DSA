#include "List.h"
#include <iostream>

int main()
{
    List<int> list = {1,2,3,4,5};//测试初始化链表
    list.clear();//clear清空数据测试

    List<int> lst;
    std::cout << lst.empty() <<std::endl;//判断链表是否为空
    for (int i = 0; i < 10; ++i)
    {
        lst.push_back(i);
    }
    lst.push_front(100);
    for (auto &x : lst)
    {
        std::cout << x << "\t" ;
    }
    std::cout << std::endl;//push_back左值&push_front右值功能测试，同时测试insert
    
    lst.pop_front();
    lst.pop_back();
    for (auto &x : lst)
    {
        std::cout << x << "\t" ;
    }
    std::cout << std::endl;//pop_front&pop_back功能测试同时测试erase
    
    const int& test = lst.back();
    std::cout << test << std::endl;//back返回最后一个数据测试(只读，可修改同理)
    
    lst.front() = 100;
    for (auto &x : lst)
    {
        std::cout << x << "\t" ;
    }
    std::cout << std::endl;//front返回第一个数据且可修改测试
    
    std::cout << lst.size() <<std::endl;//size返回List数据总数测试
    
    List<int> lst2 = std::move(lst);
    for (auto &x : lst2)
    {
        std::cout << x << "\t" ;
    }
    std::cout << std::endl;//移动构造函数测试

    List<int> lst3 = {1,2,3,4,5};
    List<int> lst4 = lst3;
    for (auto &y : lst4)
    {
        std::cout << y << "\t" ;
    }
    std::cout << std::endl;
    lst4.pop_back();
    for (auto &y : lst3)
    {
        std::cout << y << "\t" ;
    }
    std::cout << std::endl;//拷贝构造函数测试,测试深拷贝

    for(List<int>::const_iterator p = lst3.begin(); p !=lst3.end(); ++p)
    {
        std::cout<< *p << "\t";
    }
    std::cout<<std::endl;//测试前置自增运算符(自减同理)

    for(List<int>::const_iterator p = lst4.begin(); p !=lst4.end();)
    {
        std::cout<< *p << "\t";
        p++;
    }
    std::cout<<std::endl;//测试后置自增运算符(自减同理)
    return 0;
}
 
