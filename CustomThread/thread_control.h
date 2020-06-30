#include "thread_info.h"

void thread_init();
thread_id_t thread_create(void(*fun), size_t stack_size_dw);
void thread_kill(thread_id_t target);
void thread_join();
void thread_sleep(int ms);
void thread_async_sleep(int ms);
size_t thread_stack_size();
size_t thread_free_stack_size();
void thread_reloc_stack(size_t new_stack);
thread_id_t thread_id();