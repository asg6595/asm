; 		Процедура перевода числа в строку
; 	Вход:
; 	EAX - шестнадцатиричное число
;	ES:EDI - адрес буфера
;	ECX - размер буфера
; 	Выход:
; 	EAX - код возврата(0 - все хорошо/1 - буфер слишком мал)
;	ES:EDI - адрес буфера

HexToStr			proc

					PUSH EBX
					PUSH ECX
					PUSH EDX
		
					CMP ECX, 15					; Если размер буфера < 15
					JB @@BufferTooSmall			; то выходим с ошибкой (код 1)
					
					MOV ECX, 7					; Начинам обработку с 7 разряда
		
@@DigitLoop:
					MOV EBX, 16	
					CALL Pow					; Возводим 16 в степень разряда
					MOV EDX, 0					; Разряд = число / (16 ^ номер разряда)
					DIV EBX						; Число = чило % (16 ^ номер разряда)
					
					CALL HexToChar				; Преобразуем разряд в соответствующий ему символ
					
					MOV ES:[EDI], AL			; Записываем его в буфер
					INC EDI					; Переходим к следующему символу в буфере
					
					cmp ecx, 0
					je @@label1
					mov byte ptr es:[edi], '_'
					inc edi
@@label1:
					
					MOV EAX, EDX
					
					SUB ECX, 1					; Уменьшаем номер разряда
					JGE @@DigitLoop				; Если он > 0, продолжаем обрабатывать разрядs
					
					MOV EAX, 0					; Выход без ошибки
					JMP @@EndProc				
		
@@BufferTooSmall:								; Выход с ошибкой "Буфер слишком мал"
					MOV EAX, 1
		
@@EndProc:
					POP EDX
					POP ECX
					POP EBX
					
					RET
					
HexToStr			endp