;
; �������� ���������, �������������� ������ ����������� ��������� ����� � ������ � �������������.
;
; ����:
; 		EAX - �����
; 		BL - ������������
; 			* 0 - �� ������ ����
; 			* �������� �� 0 - �� ������� ����, �� 11 �������. ��� ���� ������� ����� ������ ����������� ���������
; 		ES:EDI - ����� ������, ���� ����� �������� �����
; 		ECX - ������ ������
;
; �����:
; 		EAX = 0, ���� �������
; 			ES:EDI - ��������� �� ��������� ������ � ������ ����� �����
; 		EAX = 1, ���� ����� ������� ���
; ����������: ��� ������������ �� ������ ���� � ������ ����������� �������� ������ ������� ����������� ��� ������ �����.
;

DecToStr				proc
						
						push ebx
						push ecx
						push edx
						
						cmp bl, 0
						jne @@RightAlign
						
						mov edx, ecx
						
						call NumSize
						
						cmp ecx, edx
						jg @@BufferTooSmall
						jmp @@WriteNumToBuffer
@@RightAlign:
						cmp ecx, 11
						jl @@BufferTooSmall
						
						call NumSize
						
						mov edx, 11
						sub edx, ecx
						
						call SpacesToBuffer
@@WriteNumToBuffer:
						call NumToBuffer
						mov eax, 0
						jmp @@EndProc

@@BufferTooSmall:								; ��������� ������ ���������� ������
						mov eax, 1
@@EndProc:

						pop edx
						pop ecx
						pop ebx
						
						ret
						
DecToStr				endp