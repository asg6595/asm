; ���������, �������������� �������� ������� �� ������ � �����, ���� �������� ������ � ������������� ��������������.
; ����:
	; byte ptr ds:[esi] ������ �������
; �����:
	; EAX � ����� �� 0 �� 9
	; -1  - ���� ������ �� �������� ������
IsDigit		proc
			mov eax, 0
			mov al, byte ptr ds:[esi]	; �������� ��� ������� � �����
			
			cmp al, '0'
			jb @@Error
			
			cmp al, '9'
			ja @@Error
			
			sub eax, '0'				; ��������� ����� �� ����
			jmp @@EndOfProc
@@Error:			
			mov eax, -1
			jmp @@EndOfProc
								
@@EndOfProc:
					ret

IsDigit	endp