#pragma once

#include "reg_defines.h"

void __fastcall load_gen_regs(reg_t* eip, reg_t* gen_regs);
void __stdcall gen_regs_to_stack();
void __fastcall save_stack_regs(reg_t* regs);
void __fastcall save_eip(reg_t*);
