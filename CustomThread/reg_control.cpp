#include "reg_control.h"

#define reg_fun __declspec(naked) __stdcall

void __declspec(naked) __fastcall load_gen_regs(reg_t* eip, reg_t* gen_regs)
{
	__asm {
		mov ebp, [__EBP(edx)]
		mov esp, [__ESP(edx)]

		push[ecx]

		mov eax, [__EAX(edx)]
		mov ebx, [__EBX(edx)]
		mov ecx, [__ECX(edx)]
		mov esi, [__ESI(edx)]
		mov edi, [__EDI(edx)]

		mov edx, [__EDX(edx)]

		ret
	}
}

void reg_fun gen_regs_to_stack()
{
	__asm {
		sub esp, GEN_REGS_MEMORY_SIZE;
		push eax
			mov eax, [esp + GEN_REGS_MEMORY_SIZE + REG_SIZE]
			mov[esp + REG_SIZE], eax
			pop eax

			;//сохраняем значения всех регистров, кроме esp
		mov[__EAX(esp + REG_SIZE)], eax
			mov[__EBX(esp + REG_SIZE)], ebx
			mov[__ECX(esp + REG_SIZE)], ecx
			mov[__EDX(esp + REG_SIZE)], edx
			mov[__ESI(esp + REG_SIZE)], esi
			mov[__EDI(esp + REG_SIZE)], edi
			mov[__EBP(esp + REG_SIZE)], ebp


			;//esp мы ьудем считать без учёта выделенной памяти для регистров общего назначения
		;//и адреса возврата
		mov eax, esp
			add eax, GEN_REGS_MEMORY_SIZE
			add eax, REG_SIZE
			add eax, REG_SIZE;//


		mov[__ESP(esp + 4)], eax
			mov eax, [__EAX(esp + 4)]

			ret
	}
}

void __declspec(naked) __fastcall save_stack_regs(reg_t* regs)
{
	__asm {
		mov ebx, [__EAX(esp + 4)]
		mov[__EAX(ecx)], ebx

		mov ebx, [__EBX(esp + 4)]
		mov[__EBX(ecx)], ebx

		mov ebx, [__ECX(esp + 4)]
		mov[__ECX(ecx)], ebx

		mov ebx, [__EDX(esp + 4)]
		mov[__EDX(ecx)], ebx

		mov ebx, [__ESI(esp + 4)]
		mov[__ESI(ecx)], ebx

		mov ebx, [__EDI(esp + 4)]
		mov[__EDI(ecx)], ebx

		mov ebx, [__EBP(esp + 4)]
		mov[__EBP(ecx)], ebx

		mov ebx, [__ESP(esp + 4)]
		mov[__ESP(ecx)], ebx

		pop eax
		add esp, GEN_REGS_MEMORY_SIZE
		push eax

		ret
	};
}

void __declspec(naked) __fastcall save_eip(reg_t*) {
	__asm {
		pop ebx
		pop eax
		mov[ecx], eax
		push ebx

		ret
	};
}

