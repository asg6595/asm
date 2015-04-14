; Процедура, осуществляющую преобразование содержимого строки, гарантированно содержащей число в десятичное знаковое число.
; Вход:
	; DS:ESI –адрес строки, содержащей число
; Выход:
	; EAX –код ошибки
	; 0 –нет ошибки
		; EBX –число
		; DS:ESI –указывает на первый символ после числа
	; 1 –неправильныйсимвол
		; DS:ESI –указывает на него
	; 2 –слишком большое число(не из диапазона -2^31..2^31-1)
		; DS:ESI –неопределено

; Примечание: 
	; Число в буфере записано корректно, в следующих случаях:
		; · Перед числом допускается только любое количество пробелов
		; · Отрицательные числа начинаются с одного символа ‘-‘. Между ним и числом пробелыне допускаются.
		; · Число состоит из цифр ‘0’- ‘9’, при этом цифра ‘0’ может стоять на первом месте только учисла 0. Число ‘-0’считается недопустимым.
		; · Число должно заканчиваться разделителем. Разделителями считаются следующие символы: пробел, запятая и символы с кодами: 0, 10, 13.
		; · Числосодержится в диапазоне -2^31..2^31-1
StrToDec			proc
					push edx
					
					cmp byte ptr ds:[esi], '-'				; Проверяем первый знак числа
					je @@MinusFound
					
					cmp byte ptr ds:[esi], '0'				; Если не 0, проверка пройдена
					jne @@PositiveNum
					
					inc esi
					call IsSeparator						; После нуля обязательно должен следовать разделитель
					cmp eax, 1 								; Проверка на разделитель
					je @@NullFound
					jmp @@IncorrectSymbol
					
@@MinusFound:		
					inc esi
					cmp byte ptr ds:[esi], '0'				; Проверка на -0
					je @@IncorrectSymbol
					
					call IsSeparator						; После "-" не должен следовать разделитель
					cmp eax, 1 								; Проверка на разделитель (если является разделителем - выходим)
					je @@IncorrectSymbol
					dec esi
					
@@NegativeNum:
					mov edx, 1 						; Запоминаем минус
					inc esi
					
@@PositiveNum:
					call StrToUnsignedDec
					cmp eax, 1						; Некорректный символ
					je @@IncorrectSymbol
					cmp eax, 2						; Некорректное число
					je @@IncorrectNumber
					
					cmp edx, 1						; Действуем в зависимости от знака
					jne @@ComparePositiveNimber
					cmp ebx, 2147483648 			; Модуль максимально допустимого значение для отрицательного числа (2^31)		
					ja @@IncorrectNumber
					
					neg ebx							; Переводим число в отрицательное
					mov eax, 0						; Успешное завершение
					jmp @@EndOfProc
					
@@ComparePositiveNimber:
					cmp ebx, 2147483647 			; Максимально допустимое значение для положительного числа (2^31 - 1)
					ja @@IncorrectNumber
					
					mov eax, 0						; Успешное завершение
					jmp @@EndOfProc
@@NullFound:
					mov eax, 0						; Успешное завершение с нулем
					mov ebx, 0
					jmp @@EndOfProc
@@IncorrectSymbol:
					mov eax, 1
					jmp @@EndOfProc
@@IncorrectNumber:
					mov eax, 2

@@EndOfProc:
					pop edx
					ret

StrToDec			endp