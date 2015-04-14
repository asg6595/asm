;
; Процедура для определения размера знакового числа
;
; Вход:
; 		EAX - знаковое число
; Выход:
; 		EСX = размер числа
;
NumSize			proc

				push eax
						
				cmp eax, 0					; Определяем знак числа
				jge @@PositiveNumber
				
				neg eax						; Делаем из числа положительное
				
				call UnsignedNumSize
				
				inc ecx						; Учитываем минус
				
				jmp @@EndProc
						
@@PositiveNumber:
						
				call UnsignedNumSize		
						
@@EndProc:
						
				pop eax
				
				ret
						
NumSize			endp
