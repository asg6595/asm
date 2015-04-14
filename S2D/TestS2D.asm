					.386
					locals	
					
CodeSegment 		segment use16
					assume cs:CodeSegment, ss:StackSegment
					
					
					
;Для вывода числа из буфера
include DecToStr.inc
include Pow.inc
include NumSize.inc
include NumToBuf.inc
include UNumSize.inc
include UNumBuf.inc
include SpaceBuf.inc
;Для чтения числа из буфера
include IsDig.inc
include IsSep.inc
include SkipSpas.inc
include Str2Dec.inc
include Str2UDec.inc
include TestNSt.inc
include S2D.inc

Main 				proc
					mov ax, DataSegment 	; Настраиваем используемый сегмент данных
					mov ds, ax 
					mov es, ax  
					assume es:DataSegment
					
					lea esi, Test1
					call TestStrToDec
					
					lea esi, Test2
					call TestStrToDec
					
					lea esi, Test3
					call TestStrToDec
					
					lea esi, Test4
					call TestStrToDec
					
					lea esi, Test5
					call TestStrToDec
					
					lea esi, Test6
					call TestStrToDec
					
					lea esi, Test7
					call TestStrToDec
					
					lea esi, Test8
					call TestStrToDec
					
					lea esi, Test9
					call TestStrToDec
					
					lea esi, Test10
					call TestStrToDec
					
					lea esi, Test11
					call TestStrToDec
					
					lea esi, Test12
					call TestStrToDec
					
					lea esi, Test13
					call TestStrToDec
					
					lea esi, Test14
					call TestStrToDec
					
					lea esi, Test15
					call TestStrToDec
					
					lea esi, Test16
					call TestStrToDec
				

					mov ax, 4c00h
					int 21h ; Выход из программы
							; AH = 4Ch
							; AL - код возврата
Main 				endp

TestStrToDec 		proc
					
					push eax
					push ebx
					push ecx
					push edx
					push edi
					push ds
					push es
					
					
					call StringToDec			; Вызываем тестируемую процедуру
					
					push eax            		

					mov ax, DataSegment 	; Настраиваем используемый сегмент данных
					mov ds, ax 
					mov es, ax  
					assume es:DataSegment

					lea edi, Buffer
					
					pop eax
					
					cmp eax,2 				; Пустая строка
					je @@EmptyString
					
					cmp eax,3 				; Некорректный символ
					je @@IncorrectSymbol					
					
					cmp eax,4				; Некорректное число
					je @@IncorrectNumber
					
					cmp eax,0
					jne @@UnknownError
					
					mov eax, ebx
					mov ecx, 11
					mov ebx, 0
					call DecToStr
					
					cmp eax,0 				; Нет ошибки
					je @@NoError

					cmp eax,1 				; Буфер слишком мал
					je @@BufferTooSmall
@@UnknownError:
					lea dx, UnknownErrorMsg 	; Неизвестная ошибка
					jmp @@ShowMessage

@@EmptyString:
					lea dx,EmptyStringMsg
					jmp @@ShowMessage
@@IncorrectSymbol:
					mov al, ds:[esi]
					mov [IncorrectSymbol], al
					lea dx,IncorrectSymbolMsg
					jmp @@ShowMessage
@@IncorrectNumber:
					lea dx,IncorrectNumberMsg
					jmp @@ShowMessage
@@BufferTooSmall:
					lea dx,BufferTooSmallMsg
					jmp @@ShowMessage

@@NoError: 									;вывод что нет ошибки
					;mov byte ptr [edi],'^'	;помещаем ^ в конец строки
					mov byte ptr [edi], 0Dh
					inc edi
					mov byte ptr [edi], 0Ah
					inc edi
					mov byte ptr [edi], '$' 
					lea dx, HexMessage

@@ShowMessage:
					mov ah, 9
					int 21h

@@EndProc:
					pop es
					pop ds
					pop edi
					pop edx
					pop ecx
					pop ebx
					pop eax
					
					ret

TestStrToDec 		endp

CodeSegment 		ends

DataSegment 		segment use16

HexMessage 			label byte
					db 'Number:'

Buffer 				db '###########*'
					db 0Dh , 0Ah
					db '$'

BufferTooSmallMsg 	db 'Buffer too small'
					db 0Dh , 0Ah, '$'
					
EmptyStringMsg		db 'Empty String'
					db 0Dh , 0Ah, '$'
					
IncorrectSymbolMsg  db 'Incorrect Symbol '
IncorrectSymbol		db '#'
					db 0Dh , 0Ah, '$'
					
IncorrectNumberMsg  db 'Incorrect Number'
					db 0Dh , 0Ah, '$'
					
UnknownErrorMsg 	db 'Unknown error'
					db 0Dh , 0Ah, '$'


Test1 				db ' 100'
					db 0
					
Test2 				db '        -1000'
					db 0
					
Test3 				db ' 1a00'
					db 0
					
Test4 				db ' 00'
					db 0
					
Test5 				db ' -0'
					db 0
					
Test6 				db '       0'
					db 0
					
Test7 				db '   -234235235235235235325325'
					db 0
					
Test8 				db ' -'
					db 0
					
Test9 				db ' 01'
					db 0
					
Test10 				db '  999999999999999999999'
					db 0
					
Test11 				db '  -2147483648'
					db 0
					
Test12 				db '  -2147483649'
					db 0
					
Test13 				db '  2147483647'
					db 0
					
Test14 				db '  2147483648'
					db 0
					
Test15				db '  ,      '
					db 0
					
Test16				db ','
					db 0
					
DataSegment 		ends

StackSegment 		segment use16 stack 'stack'
					db 1024 dup (?)

StackSegment 		ends

					end Main