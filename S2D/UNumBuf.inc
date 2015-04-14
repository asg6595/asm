;
; Процедура для записи беззнакового числа в буфер
;
; Вход:
; 		EAX - беззнаковое число
;		ES:EDI - адрес буфера, куда будет помещено число
;
UnsignedNumToBuffer		proc
						push eax
						push ebx
						push ecx
						
						call UnsignedNumSize
						dec ecx						; Чтобы получить старший разряд
@@DigitLoop:
						mov ebx, 10
						call Pow

						mov edx, 0
						div ebx						                        
						
						add al, '0'
						mov es:[edi], al
						inc edi

						mov eax, edx

						dec ecx
												
						cmp ecx, 0
						jge @@DigitLoop
						
						pop ecx
						pop ebx
						pop eax
						
						ret
						
UnsignedNumToBuffer		endp
