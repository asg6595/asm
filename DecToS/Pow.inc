;	Процедура возведения числа в степень
;	Вход:
;			ebx - число
;			ecx - степень
;	Выход:
;			ebx - число, возведенное в степень

Pow			proc
		
			push eax			;помещаем значения изменяемых регистров в стек
			push ecx
			push edx

			mov eax, 1			;результат = 1
@@PowLoop:
			cmp ecx, 0			;степень > 0?
			je @@EndPowLoop

			mul ebx				;результат = результат * число
			dec ecx				;степень--
			jmp @@PowLoop
@@EndPowLoop:
			mov ebx, eax		

			pop edx
			pop ecx
			pop eax

			ret

Pow			endp