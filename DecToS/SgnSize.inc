; Процедура определения размера знакового числа
; Вход:
;		eax - число
; Выход:
;		edx - размер числа


SignedNumberSize		proc
				push eax
				
				cmp eax, 0
				jl @@NumberIsNegative
				
				call UnsignedNumberSize
				
				jmp @@EndProc
				
@@NumberIsNegative:
		
				neg eax
				call UnsignedNumberSize
				inc edx
@@EndProc:				
				pop eax
				
				ret
				
SignedNumberSize		endp