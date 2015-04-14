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
		
					CMP ECX, 8					; Если размер буфера < 8
					JB @@BufferTooSmall			; то выходим с ошибкой (код 1)
					
					MOV ECX, 7					; Начинам обработку с 7 разряда
				
@@DigitLoop:
					ROL EAX, 4					; Сдвигаем циклически влево на 1 разряд
					MOV EDX, EAX				; Дублируем число
					AND EAX, 0Fh				; Получаем в EAX "старший" разряд
					
					CALL HexToChar				; Преобразуем разряд в соответствующий ему символ
					
					MOV ES:[EDI], AL			; Записываем его в буфер
					INC EDI						; Переходим к следующему символу в буфере
					
					ROL EDX, 8
					MOV EAX, EDX				; Помещаем число обратно
					
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