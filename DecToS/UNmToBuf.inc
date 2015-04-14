; Процедура вывода беззнакового числа в буфер
; Вход:
;		eax - число
;		es:edi - адрес буффера
; Выход:
;		es:edi - указатель на следующий символ после числа в буффере

UnsignedNumberToBuffer		proc
				
				push eax
				push ebx
				push ecx
				push edx
				
				call UnsignedNumberSize

				dec edx
				
@@DigitLoop:
				mov ebx, 10	
				mov ecx, edx
				
				call Pow					; Возводим 10 в степень разряда
				
				push edx
				
				mov edx, 0					; Разряд = число / (10 ^ номер разряда)
				div ebx						; Число = чиcло % (10 ^ номер разряда)
				
				add al, '0'					; Преобразуем разряд в соответствующий ему символ
					
				mov es:[edi], al			; Записываем его в буфер
				inc edi						; Переходим к следующему символу в буфере
				
				mov eax, edx
				
				pop edx
					
				sub edx, 1					; Уменьшаем номер разряда
				jge @@DigitLoop				; Если он > 0, продолжаем обрабатывать разрядs
					
				mov eax, 0					; Выход без ошибки
				jmp @@EndProc	
				
@@EndProc:
				pop edx
				pop ecx
				pop ebx
				pop eax
				
				ret
				
UnsignedNumberToBuffer		endp
