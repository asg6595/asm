				.386								;разрешение использовать регистры и команды процессора i386
				locals								;разрешение использовать локальные идентификаторы

CodeSegment		segment use16
				assume cs:CodeSegment, ss:StackSegment

include DecToS.inc								;подключение файлов
include SgnSize.inc
include UsgnSize.inc
include SNmToBuf.inc
include UNmToBuf.inc
include Pow.inc

Main			proc	

				mov eax, 1234					;тесты
				mov ecx, 8
				mov bl, 1
				call TestDecToStr
				
				mov eax, -12345
				mov ecx, 8
				mov bl, 0
				call TestDecToStr

				mov eax, -1124125346
				mov ecx, 15
				mov bl, 5
				call TestDecToStr	

				mov eax, 1345363
				mov ecx, 2
				mov bl, 1
				call TestDecToStr	

				mov eax, 12345678
				mov ecx, 8
				mov bl, 0
				call TestDecToStr	

				mov eax, 1
				mov ecx, 2
				mov bl, 1
				call TestDecToStr					
				
				mov ax, 4c00h						
				int 21h

Main			endp

;Процедура тестирования перевода шестандцатеричного числа в строку
;Вход:
;		eax - число
;		ecx - размер буффера
;		ebx - выравнивание 
;Выход:
;		-

TestDecToStr	proc
				
				push eax							;помещение содержимого изменяемых регистров в стек
				push ecx
				push edx
				push edi
				push ds
				push es
				
				push eax
				push ecx
				
				mov ax, DataSegment
				mov ds, ax
				mov es, ax
				assume ds:DataSegment, es:DataSegment

				lea edi, Buffer
				cld									;установка флага направления df в 0 
				mov al, 'x'							;заполнение регистра al 9 символами х
				mov ecx, 12
				rep stosb
				
				pop ecx
				pop eax 
				
				lea edi, Buffer
				call DecToString
				
				cmp eax, 0
				je @@NoError
				
				cmp eax, 1
				je @@ErrorBufferTooSmall
				
				lea dx, UnknownErrorMsg
				jmp @@ShowMessage
				
@@ErrorBufferTooSmall:
				lea dx, BufferTooSmall
				jmp @@ShowMessage
@@NoError:
				mov byte ptr [edi], '^'				;помещаем знак ^ в конец строки
				inc edi
				mov byte ptr [edi], 13
				inc edi
				mov byte ptr [edi], 10
				inc edi
				mov byte ptr [edi], '$'
				lea dx, DecMessage

@@ShowMessage:
				mov ah, 9							;номер вызываемой функции
				int 21h
@@EndProc:
				pop es
				pop ds
				pop edi
				pop edx
				pop ecx
				pop eax
				ret

TestDecToStr 	endp

CodeSegment 	ends

DataSegment		segment use16
	DecMessage	label byte
				db	'Dec:	'
	Buffer		db '###########*', 13, 10, '$'
	BufferTooSmall  db 'Buffer Too Small', 13, 10, '$'
	UnknownErrorMsg db 'Unknown Error', 13, 10, '$'


DataSegment		ends

StackSegment	segment use16 stack 'stack'
				db 1024 dup (?)
StackSegment	ends

				end Main

