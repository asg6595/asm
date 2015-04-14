; Процедура, осуществляющую проверку символа из буфера в число, либо выдающая ошибку о невозможности преобразования.
; Вход:
	; byte ptr ds:[esi] –адрес символа
; Выход:
	; EAX – число от 0 до 9
	; -1  - если символ не является цифрой
IsDigit		proc
			mov eax, 0
			mov al, byte ptr ds:[esi]	; Помещаем код символа в буфер
			
			cmp al, '0'
			jb @@Error
			
			cmp al, '9'
			ja @@Error
			
			sub eax, '0'				; Вычисляем цифру по коду
			jmp @@EndOfProc
@@Error:			
			mov eax, -1
			jmp @@EndOfProc
								
@@EndOfProc:
					ret

IsDigit	endp