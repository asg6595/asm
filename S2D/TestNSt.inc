; Процедура для проверки на корректность начала числа. Отслеживаем нехорошие ситации с 0 и -
; Вход:
; 		DS:ESI –адрес строки (указывает на первый символ числа)
; Выход:
; 		EAX –код ошибки
; 			0 – нет ошибки
; 				DS:ESI – указывает на первый символ числа
; 			1 – неправильный символ
; 				DS:ESI –указывает на него

TestNumStart		proc
					
					push edi
					
					mov edi, esi 
					
					cmp byte ptr ds:[esi], '-'				; Проверяем первый знак числа
					je @@NegativeNum
					
					cmp byte ptr ds:[esi], '0'				; Если не 0, проверка пройдена
					jne @@AllOK
					
					inc esi
					call IsSeparator						; После нуля обязательно должен следовать разделитель
					cmp eax, 1 								; Проверка на разделитель
					je @@AllOK
					jmp @@Error1
					
@@NegativeNum:		
					inc esi
					cmp byte ptr ds:[esi], '0'				; Проверка на -0
					je @@Error1
					
					call IsSeparator						; После "-" не должен следовать разделитель
					cmp eax, 1 								; Проверка на разделитель (если является разделителем - выходим)
					je @@Error1
					jmp @@AllOK
@@Error1:
					mov eax, 1
					jmp @@EndOfProc

@@AllOK:
					mov eax, 0
					mov esi, edi
@@EndOfProc:
					pop edi
					ret
					
TestNumStart		endp