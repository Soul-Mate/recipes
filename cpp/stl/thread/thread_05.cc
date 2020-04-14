#include <iostream>
#include <thread>
#include <cstring>
#include <cassert>
#include <string>
#include <vector>

void f1(char *buf, int n)
{
    for (int i = 0; i < n; i++)
        buf[i] = "FEDCBA9876543210"[i % 16];
}

void oop1()
{
    char buf[16];
    std::memset(buf, '\0', 16);
    for (int i = 0; i < 16; i++)
    {
        buf[i] = "0123456789ABCDEF"[i % 16];
    }
    std::cout << "oop1 thread start before buf = " << buf << std::endl;
    // 传递指针
    std::thread t(f1, buf, 16);
    t.join();
    std::cout << "oop1 thread start after buf = " << buf << std::endl;
}

void f2(std::string &s)
{
    for (int i = 0, j = s.size() - 1, n = s.size(); i < n; i++, j--)
    {
        s[i] = s[j];
    }
}

void oop2()
{
    std::string str("hello world");
    std::cout << "oop2 thread start before str = " << str << std::endl;
    // 传递引用，但需要显示的std::ref声明
    std::thread t(f2, std::ref(str));
    t.join();
    std::cout << "oop2 thread start after str = " << str << std::endl;
}

void f3(std::vector<char> buf)
{
    for (int i = 0; i < buf.size(); i++)
        buf[i] = "FEDCBA9876543210"[i % 16];

    std::cout << "oop3 func, internal f3 thread vertor = " << buf.data() << std::endl;
}

void oop3()
{
    std::vector<char> buf;
    for (int i = 0; i < 16; i++)
    {
        buf.push_back("0123456789ABCDEF"[i % 16]);
    }

    std::cout << "oop3 func, main thread vertor = " << buf.data() << std::endl;

    // 传递拷贝，配合std::move
    std::thread t(f3, std::move(buf));
    t.join();

    // 后续不能在使用buf了，因为内部的data已经move了
}

int main()
{
    oop1();
    oop2();
    oop3();
}