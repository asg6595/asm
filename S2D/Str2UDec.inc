; Процедура, осуществляющую преобразование содержимого строки, гарантированно содержащей число в десятичное беззнаковое число.
; Вход:
	; DS:ESI –адрес строки, содержащей число
; Выход:
	; EAX –код ошибки
	; 0 –нет ошибки
		; EBX –число
		; DS:ESI –указывает на первый символ после числа
	; 1 –неправильныйсимвол
		; DS:ESI –указывает на него
	; 2 –слишком большое число(не из диапазона 0..2^32-1)
		; DS:ESI –неопределено
StrToUnsignedDec	proc
					
					mov ebx,0
@@DigitLoop:
					call IsDigit
					cmp eax, -1
					je @@NotDigit				; Некоррректный символ
					imul ebx, 10 
					jc @@IncorrectNumber					; При переполнении ошибка
					add ebx, eax
					jc @@IncorrectNumber					; При переполнении ошибка
					inc esi
					call IsSeparator			; Проверка на разделитель
					cmp eax, 0 					; Пока не разделитель берем следующее число
					je @@DigitLoop
					
					mov eax, 0					; Успешное завершение
					jmp @@EndOfProc
@@NotDigit:
					mov eax, 1
					jmp @@EndOfProc
@@IncorrectNumber:
					mov eax, 2
					jmp @@EndOfProc
@@EndOfProc:
					ret

StrToUnsignedDec	endp