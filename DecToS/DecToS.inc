; ��������� �������� ����������� ��������� ����� � ������
; ����:
; 		eax - ���������� �������� �����
;		bl - ������������:
;							0 - �� ������ ����
;							�������� �� 0 - �� �������, �� 11 ������� � ���������
;		es:edi - ����� ������
;		ecx - ������ �������
; �����:
; 		eax=0, ���� �������
;				es:edi ��������� �� ��������� ������ � ������ ����� �����
;		eax=1, ���� ������ ������� ���

DecToString			proc

					push ecx
		
					cmp bl, 0					; ���� ������ ������ < 8
					jne @@RightAlign			; �� ������� � ������� (��� 1)
					
					call SignedNumberSize
					
					cmp ecx, edx
					jl @@BufferTooSmall
					
					jmp @@WriteNumberToBuffer

@@RightAlign:	
					cmp ecx, 1
					jl @@BufferTooSmall
					
					call SignedNumberSize
					
					cmp ecx, edx
					jl @@BufferTooSmall
					
					push eax
					push ebx
					
					mov ebx, 11
					sub ebx, edx
					
					cld							;��������� ����� ����������� df � 0 
					mov al, ' '					;���������� �������� al 9 ��������� �
					mov ecx, ebx
					rep stosb
					
					pop ebx
					pop eax
					
					jmp @@WriteNumberToBuffer
		
@@BufferTooSmall:								; ����� � ������� "����� ������� ���"
					mov eax, 1
					
					jmp @@EndProc
 
@@WriteNumberToBuffer:
					call SignedNumberToBuffer
					
					mov eax, 0
					
@@EndProc:
					pop ecx
					
					ret
					
DecToString			endp