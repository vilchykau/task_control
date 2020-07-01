#include "thread_control.h"

#include "reg_control.h"
#include "circle_list.h"
#include "thread_info.h"
#include "delta_time.h"
#include "platform.h"

circle_list<thread_info*> __thread_info_list;
thread_info* __selected_info = nullptr;
thread_id_t __id_counter = 0;

void __thread_rotate();
void __thread_finish();
void __thread_erase_prev();
void __thread_clone();

void thread_init()
{
	__thread_info_list.insert(new thread_info{ __id_counter++ });
	__selected_info = __thread_info_list.get_now();
}

thread_id_t thread_create(void(*fun), size_t stack_size) {
	auto t = __thread_info_list.insert(new thread_info{ __id_counter++, stack_size, 
		reinterpret_cast<reg_t>(fun),
		reinterpret_cast<reg_t>(&__thread_finish)
		});
	return t->id;
}

bool thread_kill(thread_id_t target)
{
	bool deleted = false;
	if (target == thread_id()) {
		__thread_finish();
	}
	else {
		auto now_id = thread_id();

		__thread_info_list.go_next();
		while (__thread_info_list.get_now()->id != now_id) {
			if (!deleted && __thread_info_list.get_now()->id == target) {
				delete __thread_info_list.get_now();
				__thread_info_list.pop_now();
				deleted = true;
			}
			else {
				__thread_info_list.go_next();
			}
		}
	}
	return deleted;
}

void __declspec(naked) thread_join() {
	gen_regs_to_stack();
	save_stack_regs(__selected_info->gen_regs);
	save_eip(&__selected_info->eip);

	__thread_rotate();
}

void __thread_rotate() {
	__thread_info_list.go_next();
	__selected_info = __thread_info_list.get_now();

	load_gen_regs(&__selected_info->eip, __selected_info->gen_regs);
}

void __thread_finish() {
	auto& next = __thread_info_list.next();
	next->gen_regs[ESP_ID] -= REG_SIZE;
	reg_t* r = reinterpret_cast<reg_t*>(next->gen_regs[ESP_ID]);
	*r = next->eip;
	next->eip = reinterpret_cast<reg_t>(&__thread_erase_prev);

	__thread_rotate();
}

void __thread_erase_prev() {
	__thread_info_list.go_prev();
	delete __thread_info_list.get_now();
	__thread_info_list.pop_now();
	__thread_info_list.go_prev();
	
	reg_t* r = reinterpret_cast<reg_t*>(__selected_info->gen_regs[ESP_ID]);
	__selected_info->eip = *r;
	__selected_info->gen_regs[ESP_ID] += REG_SIZE;


	__thread_rotate();
}

void thread_sleep(int ms)
{
	platform_sleep(ms);
}


void thread_async_sleep(int ms)
{
	delta_time* delta = new delta_time(); 
	while (delta->get_delta() < ms) {
		thread_join();
		platform_sleep(1);
	} 
	delete delta;
}

size_t thread_stack_size()
{
	return __selected_info->stack_size;
}

size_t thread_free_stack_size()
{
	return  reinterpret_cast<reg_t*>(__selected_info->gen_regs[ESP_ID]) - 
		__selected_info->stack;
}

int __declspec(naked) __fastcall thread_fork(size_t stack_size_dw){
	gen_regs_to_stack();
	save_stack_regs(__selected_info->gen_regs);
	save_eip(&__selected_info->eip);

	__thread_clone();

	__thread_info_list.go_prev();
	__thread_rotate();
	
	__asm {
		mov eax, 0
		ret
	}
}

void __thread_clone() {
	size_t new_stack_size = __selected_info->gen_regs[ECX_ID];
	if(new_stack_size == 0)
		new_stack_size = __selected_info->stack_size;

	auto cloned = __selected_info->clone(++__id_counter, new_stack_size);
	__thread_info_list.insert(cloned);
	__selected_info->gen_regs[EAX_ID] = 0u;
	__thread_info_list.next()->gen_regs[EAX_ID] = 1u;
}

thread_id_t thread_id()
{
	return __selected_info->id;
}
