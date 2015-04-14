;
; Написать процедуру, осуществляющую запись десятичного знакового числа в строку с выравниванием.
;
; Вход:
; 		EAX - число
; 		BL - выравнивание
; 			* 0 - по левому краю
; 			* отличное от 0 - по правому краю, по 11 позиции. При этом символы перед числом заполняются пробелами
; 		ES:EDI - адрес буфера, куда будет помещено число
; 		ECX - размер буфера
;
; Выход:
; 		EAX = 0, если успешно
; 			ES:EDI - указывает на следующий символ в буфере после числа
; 		EAX = 1, если буфер слишком мал
; Примечание: при выравнивании по левому краю в буфере разрешается изменять только символы необходимые для записи числа.
;

DecToStr				proc
						
						push ebx
						push ecx
						push edx
						
						cmp bl, 0
						jne @@RightAlign
						
						mov edx, ecx
						
						call NumSize
						
						cmp ecx, edx
						jg @@BufferTooSmall
						jmp @@WriteNumToBuffer
@@RightAlign:
						cmp ecx, 11
						jl @@BufferTooSmall
						
						call NumSize
						
						mov edx, 11
						sub edx, ecx
						
						call SpacesToBuffer
@@WriteNumToBuffer:
						call NumToBuffer
						mov eax, 0
						jmp @@EndProc

@@BufferTooSmall:								; Обработка ошибки маленького буфера
						mov eax, 1
@@EndProc:

						pop edx
						pop ecx
						pop ebx
						
						ret
						
DecToStr				endp