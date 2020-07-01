#include "thread_info.h"

#include <memory>

thread_info::thread_info(thread_id_t new_id, size_t stack_size)
	: stack_size(stack_size), id(new_id), eip(0)
{
	memset(gen_regs, NULL, GEN_REGS_MEMORY_SIZE);
	//Alloc memory for stack used in thread
	stack = new reg_t[stack_size];
	//Set esp, ebp to the end of the stack
	gen_regs[ESP_ID] =
		gen_regs[EBP_ID] =
		reinterpret_cast<reg_t>(stack + stack_size - 1);
}

//Constructor for the main thread. We don't init stack.
thread_info::thread_info(thread_id_t new_id) :
	thread_info(new_id, 0)
{
}

//Constructor for a child thread. In this constructor, we set an address of a call-back
//function(this function will free memory and delete thread_info form a list of threads) 
//at the beginning of the stack and set eip to the beginning of the thread. 
thread_info::thread_info(thread_id_t new_id, size_t stack_size, 
	reg_t eip, reg_t ret) :
	thread_info(new_id, stack_size)
{
	stack[stack_size - 1] = ret;
	this->eip = eip;
}

thread_info::~thread_info()
{
	delete[] stack;
}

thread_info* thread_info::clone(thread_id_t new_id, size_t new_stack_size)
{
	auto new_info = new thread_info(new_id, new_stack_size, eip, stack[stack_size - 1]);
	copy_stack(new_info);
	copy_gen_regs(new_info);
	copy_eip(new_info);
	return new_info;
}

//We don't init stack only if its main thread(have a look at thread_info(thread_id_t)).
bool thread_info::is_main() const
{
	return stack_size == 0;
}

void thread_info::copy_stack(thread_info* dist)
{
	size_t min_size = dist->stack_size > this->stack_size ? this->stack_size : dist->stack_size;
	for (size_t i = 0; i < min_size; ++i) {
		dist->stack[dist->stack_size - i - 1] =
			this->stack[this->stack_size - i - 1];
	}
}

void thread_info::copy_gen_regs(thread_info* dist)
{
	memcpy(dist->gen_regs, this->gen_regs, GEN_REGS_MEMORY_SIZE);

	size_t delta_esp =
		this->stack + this->stack_size - reinterpret_cast<reg_t*>(this->gen_regs[ESP_ID]);
	size_t delta_ebp =
		this->stack + this->stack_size - reinterpret_cast<reg_t*>(this->gen_regs[EBP_ID]);

	dist->gen_regs[ESP_ID] =
		reinterpret_cast<reg_t>(dist->stack + dist->stack_size - delta_esp);
	dist->gen_regs[EBP_ID] =
		reinterpret_cast<reg_t>(dist->stack + dist->stack_size - delta_ebp);
}

void thread_info::copy_eip(thread_info* dist) 
{
	dist->eip = this->eip;
}
