; Процедура вывода знакового числа в буфер
; Вход:
;		eax - число
;		es:edi - адрес буффера
; Выход:
;		 es:edi- указатель на следующий символ после числа в буффере

SignedNumberToBuffer		proc

				push eax

				cmp eax, 0
				jge @@NumberIsUnsigned
				
				mov byte ptr [edi], '-'			; Записываем его в буфер
				inc edi						; Переходим к следующему символу в буфере
				
				neg eax
				
@@NumberIsUnsigned:
				call UnsignedNumberToBuffer
				
				pop eax
				
				ret
				
SignedNumberToBuffer		endp
