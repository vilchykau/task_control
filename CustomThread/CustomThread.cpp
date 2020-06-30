#include <iostream>

#include "thread_control.h"

#define STACK_SIZE 2000

void fun1() {
    while (true) {
        std::cout << "Fun1 " << std::endl;
        thread_async_sleep(1000);
    }
}

void  fun2() {
    int i = 0;
    while (true) {
        std::cout << "Fun2" << std::endl;
        thread_async_sleep(2000);
        if (i > 2) {
            std::cout << "Fun 2 is going to suicide" << std::endl;
            thread_kill(thread_id());
        }
        ++i;
    }
}

void fun3() {
    std::cout << "Fun3" << std::endl;
}

int main()
{
    thread_init();

    thread_create(&fun2, STACK_SIZE);
    thread_create(&fun1, STACK_SIZE);
    thread_create(&fun3, STACK_SIZE);

    while (true) {
        std::cout << "Main" << std::endl;
        thread_async_sleep(3000);
    }

    return 0;
}