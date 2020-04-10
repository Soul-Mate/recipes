#include <iostream>
#include <thread>
#include <unistd.h>

class background
{
public:
    background(int& i) :i_(i) {};
    void operator()() const {
        for (int i = 0; i < 100000;i ++) {
            std::cout << i_ << std::endl; // 潜在的访问隐患：存在悬空引用
        }
    };

private:
    int& i_;
};

void func()
{
    int local_state = 100; // 局部变量
    background f(local_state); // 传递的是局部变量，local_state离开func时就被销毁了
    // 创建并分离了线程
    std::thread t(f);
    t.detach(); 

    // 改成 t.join() 可消除隐患
}

int main()
{
    func();
    sleep(1);
}