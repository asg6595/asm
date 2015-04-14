					.386
					locals

CodeSegment 		segment use16
					assume cs:CodeSegment, ss:StackSegment

include HexToStr.inc
include Pow.inc
include HexToChr.inc

Main 				proc

					mov eax, 10101010h
					mov ecx, 15
					call TestHexToStr
					
					mov eax, 12345678h
					mov ecx, 15
					call TestHexToStr

					mov eax, 0A1B2C3D4h
					mov ecx, 15
					call TestHexToStr

					mov eax, 1029DDDDh
					mov ecx, 15
					call TestHexToStr					

					mov eax, 89ABCDEFh
					mov ecx, 14
					call TestHexToStr

					mov eax, 0
					mov ecx, 7
					call TestHexToStr

					mov ax, 4c00h
					int 21h ; Выход из программы
							; AH = 4Ch
							; AL - код возврата
Main 				endp

TestHexToStr 		proc
					
					push eax
					push ecx
					push edx
					push edi
					push ds
					push es
					push eax            		
					push ecx

					mov ax, DataSegment 	; Настраиваем используемый сегмент данных
					mov ds, ax 
					mov es, ax  
					assume ds:DataSegment, es:DataSegment

					lea edi,Buffer
					cld
					mov al,'x'
					mov ecx, 15
					REP stosb 					; Инициализируем буффер символами ‘x’

					pop ecx
					pop eax
					
					lea edi,Buffer
					call HexToStr 			; Вызываем тестируемую процедуру
					
					cmp eax,0 				; Нет ошибки
					je @@NoError

					cmp eax,1 				; Буфер слишком мал
					je @@BufferTooSmall

					lea dx,UnknownErrorMsg 	; Неизвестная ошибка
					jmp @@ShowMessage

@@BufferTooSmall:
					lea dx,BufferTooSmallMsg
					jmp @@ShowMessage

@@NoError: 									;вывод что нет ошибки
					mov byte ptr [edi],'^'	;помещаем ^ в конец строки
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
					pop eax
					
					ret

TestHexToStr 		endp

CodeSegment 		ends

DataSegment 		segment use16

HexMessage 			label byte
					db 'Hex: '

Buffer 				db '###############*'
					db 0Dh , 0Ah
					db '$'

BufferTooSmallMsg 	db 'Buffer too small'
					db 0Dh , 0Ah, '$'

UnknownErrorMsg 	db 'Unknown error'
					db 0Dh , 0Ah, '$'

DataSegment 		ends

StackSegment 		segment use16 stack 'stack'
					db 1024 dup (?)

StackSegment 		ends

					end Main