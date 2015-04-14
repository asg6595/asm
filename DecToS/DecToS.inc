; Процедура перевода десятичного знакового числа в строку
; Вход:
; 		eax - десятичное знаковое число
;		bl - выравнивание:
;							0 - по левому краю
;							отличное от 0 - по правому, по 11 позиции с пробелами
;		es:edi - адрес буфера
;		ecx - размер буффера
; Выход:
; 		eax=0, если успешно
;				es:edi указывает на следующий символ в буфере после числа
;		eax=1, если буффер слишком мал

DecToString			proc

					push ecx
		
					cmp bl, 0					; Если размер буфера < 8
					jne @@RightAlign			; то выходим с ошибкой (код 1)
					
					call SignedNumberSize
					
					cmp ecx, edx
					jl @@BufferTooSmall
					
					jmp @@WriteNumberToBuffer

@@RightAlign:	
					cmp ecx, 1
					jl @@BufferTooSmall
					
					call SignedNumberSize
					
					cmp ecx, edx
					jl @@BufferTooSmall
					
					push eax
					push ebx
					
					mov ebx, 11
					sub ebx, edx
					
					cld							;установка флага направления df в 0 
					mov al, ' '					;заполнение регистра al 9 символами х
					mov ecx, ebx
					rep stosb
					
					pop ebx
					pop eax
					
					jmp @@WriteNumberToBuffer
		
@@BufferTooSmall:								; Выход с ошибкой "Буфер слишком мал"
					mov eax, 1
					
					jmp @@EndProc
 
@@WriteNumberToBuffer:
					call SignedNumberToBuffer
					
					mov eax, 0
					
@@EndProc:
					pop ecx
					
					ret
					
DecToString			endp