;
; Процедура для определения размера беззнакового числа
;
; Вход:
; 		EAX - беззнаковое число
; Выход:
; 		EСX = размер числа
;
UnsignedNumSize			proc
						push eax
						push ebx
						push edx
						
						mov ebx, 10					;т. к. число десятичное
						
						mov ecx, 0
@@NumberLenghtLoop:									
	                    inc ecx
						
						mov edx, 0

						div ebx					
                        cmp eax, 0
						jne @@NumberLenghtLoop 
						
						pop edx
						pop ebx
						pop eax
						
						ret
						
UnsignedNumSize			endp
