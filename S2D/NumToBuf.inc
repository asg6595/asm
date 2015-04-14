;
; Процедура для записи знакового числа в буфер
;
; Вход:
; 		EAX - знаковое число
;		ES:EDI - адрес буфера, куда будет помещено число
;

NumToBuffer				proc

						push eax
						
						cmp eax, 0					; Определяем знак числа
						jge @@PositiveNumber
						
						neg eax						; Делаем из числа положительное
						
						call UnsignedNumSize
						
						mov byte ptr es:[edi], '-'
						inc edi
@@PositiveNumber:
			
						call UnsignedNumToBuffer		
						
						pop eax
						
						ret
						
NumToBuffer				endp
