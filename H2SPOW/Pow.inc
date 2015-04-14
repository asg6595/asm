; Процедура возведения в степень
; Вход:
; 	EBX - число
; 	ECX - степень
; Выход:
; 	EBX - число в степени
Pow					proc

					PUSH EAX
					PUSH ECX
					PUSH EDX
					
					MOV EAX, 1				; Результат = 1
	
@@PowLoop:									; Цикл возведения чиста в степень
					CMP ECX, 0				; Если степень = 0
					JE @@EndPowLoop			; выходим
					
					MUL EBX					; Умножаем промежуточный результат на число
											; EAX - первый множитель (результат), EBX - второй множитель (число) 
					DEC ECX					; Уменьшаем степень на 1
					JMP @@PowLoop
		
	@@EndPowLoop:							; Перед выходом помещаем результут возведения в степень в EBX
					MOV EBX, EAX
					
					POP EDX
					POP ECX
					POP EAX
					
					RET
					
Pow					endp
