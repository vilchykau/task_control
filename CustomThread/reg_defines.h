#pragma once

//Total number of general-purpose registers
#define GEN_REGS_COUNT 8

//Indicators of the general-purpose. Ids are used in the arrays.
#define EAX_ID 0
#define EBX_ID 1
#define EDX_ID 2
#define ECX_ID 3
#define ESP_ID 4
#define EBP_ID 5
#define ESI_ID 6
#define EDI_ID 7
//#define EFL_ID 8

#define __EAX(ARR) ARR
#define __EBX(ARR) ARR+REG_SIZE*EBX_ID
#define __EDX(ARR) ARR+REG_SIZE*EDX_ID
#define __ECX(ARR) ARR+REG_SIZE*ECX_ID
#define __ESP(ARR) ARR+REG_SIZE*ESP_ID
#define __EBP(ARR) ARR+REG_SIZE*EBP_ID
#define __ESI(ARR) ARR+REG_SIZE*ESI_ID
#define __EDI(ARR) ARR+REG_SIZE*EDI_ID
//#define __EFL(ARR) ARR+REG_SIZE*EFL_ID

//define type for register
using reg_t = unsigned int;

//adefine register size
#define REG_SIZE 4

//4*8
#define GEN_REGS_MEMORY_SIZE 32