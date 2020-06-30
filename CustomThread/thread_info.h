#pragma once

#include <cstdint>

#include "reg_defines.h"

using thread_id_t = uint32_t;


struct thread_info
{
	reg_t gen_regs[GEN_REGS_COUNT];
	reg_t eip;
	reg_t* stack;
	size_t stack_size;
	thread_id_t id;

	thread_info(thread_id_t new_id);
	thread_info(thread_id_t new_id, size_t stack_size);
	thread_info(thread_id_t new_id, size_t stack_size, std::uintptr_t eip, std::uintptr_t ret);
	~thread_info();

	bool is_main() const;
};
