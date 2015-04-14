					.386
					locals

CodeSegment 		segment use16
					assume cs:CodeSegment, ss:StackSegment

include DecToStr.inc
include Pow.inc
include NumSize.inc
include NumToBuf.inc
include UNumSize.inc
include UNumBuf.inc
include SpaceBuf.inc


Main 				proc

					; mov eax, 100
					; mov ecx, 5
					; mov bl, 0
					; call TestDecToStr
					
					; mov eax, -100
					; mov ecx, 5
					; mov bl, 0
					; call TestDecToStr
					
					; mov eax, -100
					; mov ecx, 2
					; mov bl, 0
					; call TestDecToStr
								
					; mov eax, -2147483648
					; mov ecx, 11
					; mov bl, 0
					; call TestDecToStr
					
					; mov eax, 2147483647
					; mov ecx, 11
					; mov bl, 0
					; call TestDecToStr
					
					; mov eax, 100
					; mov ecx, 15
					; mov bl, 1
					; call TestDecToStr
					
					; mov eax, -100
					; mov ecx, 15
					; mov bl, 1
					; call TestDecToStr
					
					; mov eax, -100
					; mov ecx, 5
					; mov bl, 1
					; call TestDecToStr
								
					; mov eax, -2147483648
					; mov ecx, 11
					; mov bl, 1
					; call TestDecToStr
					
					; mov eax, 2147483647
					; mov ecx, 11
					; mov bl, 1
					; call TestDecToStr
					
					mov eax, 0FFFFFFFFh
					mov ecx, 10
					mov bl, 1
					call TestDecToStr
					
					mov eax, 256
					mov ecx, 5
					mov bl, 0
					call TestDecToStr
					
					mov eax, 256
					mov ecx, 2
					mov bl, 0
					call TestDecToStr
					
					mov eax, 256
					mov ecx, 15
					mov bl, 1
					call TestDecToStr
					
					mov eax, 256
					mov ecx, 5
					mov bl, 1
					call TestDecToStr

					mov ax, 4c00h
					int 21h ; Выход из программы
							; AH = 4Ch
							; AL - код возврата
Main 				endp

TestDecToStr 		proc
					
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

					lea edi, Buffer
					cld
					mov al,'x'
					mov ecx, 12
					rep stosb 					; Инициализируем буффер символами ‘x’

					pop ecx
					pop eax
					
					lea edi,Buffer
					call DecToStr 			; Вызываем тестируемую процедуру
					
					cmp eax,0 				; Нет ошибки
					je @@NoError

					cmp eax,1 				; Буфер слишком мал
					je @@BufferTooSmall

					lea dx, UnknownErrorMsg 	; Неизвестная ошибка
					jmp @@ShowMessage

@@BufferTooSmall:
					lea dx,BufferTooSmallMsg
					jmp @@ShowMessage

@@NoError: 									;вывод что нет ошибки
					mov byte ptr [edi],'^'	;помещаем ^ в конец строки
					; mov byte ptr [edi], 0Dh
					; inc edi
					; mov byte ptr [edi], 0Ah
					; inc edi
					; mov byte ptr [edi], '$' 
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

TestDecToStr 		endp

CodeSegment 		ends

DataSegment 		segment use16

HexMessage 			label byte
					db 'Number:'

Buffer 				db '###########*'
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