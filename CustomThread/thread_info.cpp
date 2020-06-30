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

//We don't init stack only if its main thread(have a look at thread_info(thread_id_t)).
bool thread_info::is_main() const
{
	return stack_size == 0;
}
