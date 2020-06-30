#pragma once

#include <cstdint>

using reg_t = unsigned int;
#define REG_SIZE 4

using thread_id_t = uint32_t;

#define GEN_REGS_COUNT 8

#define EAX_ID 0
#define EBX_ID 1
#define EDX_ID 2
#define ECX_ID 3
#define ESP_ID 4
#define EBP_ID 5
#define ESI_ID 6
#define EDI_ID 7
#define EFL_ID 8

#define __EAX(ARR) ARR
#define __EBX(ARR) ARR+REG_SIZE*EBX_ID
#define __EDX(ARR) ARR+REG_SIZE*EDX_ID
#define __ECX(ARR) ARR+REG_SIZE*ECX_ID
#define __ESP(ARR) ARR+REG_SIZE*ESP_ID
#define __EBP(ARR) ARR+REG_SIZE*EBP_ID
#define __ESI(ARR) ARR+REG_SIZE*ESI_ID
#define __EDI(ARR) ARR+REG_SIZE*EDI_ID
#define __EFL(ARR) ARR+REG_SIZE*EFL_ID


//4*8
#define GEN_REGS_MEMORY_SIZE 36


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
