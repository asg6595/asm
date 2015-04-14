					.386
					locals	
					
CodeSegment 		segment use16
					assume cs:CodeSegment, ss:StackSegment
					
					
					


Main 				proc
					mov ax, DataSegment 	; Настраиваем используемый сегмент данных
					mov ds, ax 
					mov es, ax  
					assume es:DataSegment
					
					mov eax, 12345678h
					bsr	eax, eax

					mov ax, 4c00h
					int 21h ; Выход из программы
							; AH = 4Ch
							; AL - код возврата
Main 				endp

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