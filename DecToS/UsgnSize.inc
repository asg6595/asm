; Процедура определения размера беззнакового числа
; Вход:
;		eax - число
; Выход:
;		edx - размер числа


UnsignedNumberSize		proc
				push eax
				push ebx
				
				mov edx, 1
				
@@DigitLoop:
				push edx
				
				mov edx, 0
				mov ebx, 10
				div ebx
				
				pop edx
				
				cmp eax, 0
				je @@EndDigitLoop
				
				inc edx
				
				jmp @@DigitLoop
				
@@EndDigitLoop:
				pop ebx
				pop eax
				
				ret
				
UnsignedNumberSize		endp