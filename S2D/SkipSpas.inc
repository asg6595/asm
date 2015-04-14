 ; Процедура для обработки пробелов перед записью числа в буфере.
; Вход:
	; DS:ESI –адрес строки
; Выход:
	; EAX –код ошибки
	; 0 –нет ошибки
		; DS:ESI –указывает на первый символ числа
	; 1 –пустая строка
		; DS:ESI –указывает на символ конца строки 
SkipSpaces			proc

					mov eax, 0
@@SpaceLoop:					
					cmp byte ptr ds:[esi], ' '
					jne @@TrimedString				; Если следующий символ не пробел, продолжаем
					inc esi
					jmp @@SpaceLoop
					
@@TrimedString:		
					cmp byte ptr ds:[esi], 0
					jne @@EndOfProc					
					
					mov eax, 1						; В случае, когда строка состоит из одних пробелов
@@EndOfProc:

					ret
					
SkipSpaces			endp