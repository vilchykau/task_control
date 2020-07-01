#pragma once

#include "reg_defines.h"


//define a new type for thread_id, threads will use the id for dealing,
//communication with other threads
using thread_id_t = unsigned int;
#define thread_id_null thread_id_t(0)

//in this structure, we save information about threads:
//general purpose registers, eip, stack.....
struct thread_info
{
	reg_t gen_regs[GEN_REGS_COUNT];
	reg_t eip;
	reg_t* stack;
	size_t stack_size;
	thread_id_t id;

	//Constructor for the main thread.
	thread_info(thread_id_t new_id);

	//Auxiliary Constructor
	thread_info(thread_id_t new_id, size_t stack_size);

	//Constructor for a child thread.
	thread_info(thread_id_t new_id, size_t stack_size, reg_t eip, reg_t ret);

	~thread_info();

	thread_info* clone(thread_id_t new_id, size_t new_stack_size);

	bool is_main() const;

private:
	void copy_stack(thread_info* dist);

	void copy_gen_regs(thread_info* dist);
	
	void copy_eip(thread_info* dist);
};
