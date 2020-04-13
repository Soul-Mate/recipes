#include "event2/event.h"
#include <iostream>

int main()
{
    struct event_base *base = event_base_new();
    std::cout << "hello libevent" << std::endl;
    event_base_free(base);
}