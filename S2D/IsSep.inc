; Процедура, осуществляющую проверку символа из буфера на то, является ли он разделителем .
; Вход:
; 	ds:esi –адрес символа
; Выход:
; 	EAX – 1 -является/ 0 - не является
;Разделителями считаются следующие символы: пробел, запятая и символы с кодами: 0, 10, 13.
IsSeparator		proc
				
				cmp byte ptr ds:[esi], ' '
				je @@Separator
				
				cmp byte ptr ds:[esi], ','
				je @@Separator
				
				cmp byte ptr ds:[esi], 0
				je @@Separator
				
				cmp byte ptr ds:[esi], 10
				je @@Separator
				
				cmp byte ptr ds:[esi], 13
				je @@Separator
				
				mov eax, 0
				jmp @@EndOfProc
					
@@Separator:		
				mov eax, 1
			
@@EndOfProc:
				ret

IsSeparator		endp