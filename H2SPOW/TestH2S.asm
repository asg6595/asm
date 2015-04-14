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
					int 21h ; ����� �� ���������
							; AH = 4Ch
							; AL - ��� ��������
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

					mov ax, DataSegment 	; ����������� ������������ ������� ������
					mov ds, ax 
					mov es, ax  
					assume ds:DataSegment, es:DataSegment

					lea edi,Buffer
					cld
					mov al,'x'
					mov ecx, 15
					REP stosb 					; �������������� ������ ��������� �x�

					pop ecx
					pop eax
					
					lea edi,Buffer
					call HexToStr 			; �������� ����������� ���������
					
					cmp eax,0 				; ��� ������
					je @@NoError

					cmp eax,1 				; ����� ������� ���
					je @@BufferTooSmall

					lea dx,UnknownErrorMsg 	; ����������� ������
					jmp @@ShowMessage

@@BufferTooSmall:
					lea dx,BufferTooSmallMsg
					jmp @@ShowMessage

@@NoError: 									;����� ��� ��� ������
					mov byte ptr [edi],'^'	;�������� ^ � ����� ������
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