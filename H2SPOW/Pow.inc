; ��������� ���������� � �������
; ����:
; 	EBX - �����
; 	ECX - �������
; �����:
; 	EBX - ����� � �������
Pow					proc

					PUSH EAX
					PUSH ECX
					PUSH EDX
					
					MOV EAX, 1				; ��������� = 1
	
@@PowLoop:									; ���� ���������� ����� � �������
					CMP ECX, 0				; ���� ������� = 0
					JE @@EndPowLoop			; �������
					
					MUL EBX					; �������� ������������� ��������� �� �����
											; EAX - ������ ��������� (���������), EBX - ������ ��������� (�����) 
					DEC ECX					; ��������� ������� �� 1
					JMP @@PowLoop
		
	@@EndPowLoop:							; ����� ������� �������� ��������� ���������� � ������� � EBX
					MOV EBX, EAX
					
					POP EDX
					POP ECX
					POP EAX
					
					RET
					
Pow					endp
