#include "thread_info.h"

#include <memory>

thread_info::thread_info(thread_id_t new_id) :
	thread_info(new_id, 0)
{
}

thread_info::thread_info(thread_id_t new_id, size_t stack_size)
	: stack_size(stack_size), id(new_id)
{
	stack = new reg_t[stack_size];

	gen_regs[ESP_ID] =
		gen_regs[EBP_ID] =
		reinterpret_cast<std::uintptr_t>(stack + stack_size - 1);
}

thread_info::thread_info(thread_id_t new_id, size_t stack_size, 
	std::uintptr_t eip, std::uintptr_t ret) :
	thread_info(new_id, stack_size)
{
	stack[stack_size - 1] = ret;
	this->eip = eip;
}

thread_info::~thread_info()
{
	delete[] stack;
}

bool thread_info::is_main() const
{
	return stack_size == 0;
}
