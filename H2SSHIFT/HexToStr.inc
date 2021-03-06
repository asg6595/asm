; 		��������� �������� ����� � ������
; 	����:
; 	EAX - ����������������� �����
;	ES:EDI - ����� ������
;	ECX - ������ ������
; 	�����:
; 	EAX - ��� ��������(0 - ��� ������/1 - ����� ������� ���)
;	ES:EDI - ����� ������

HexToStr			proc

					PUSH EBX
					PUSH ECX
					PUSH EDX
		
					CMP ECX, 8					; ���� ������ ������ < 8
					JB @@BufferTooSmall			; �� ������� � ������� (��� 1)
					
					MOV ECX, 7					; ������� ��������� � 7 �������
				
@@DigitLoop:
					ROL EAX, 4					; �������� ���������� ����� �� 1 ������
					MOV EDX, EAX				; ��������� �����
					AND EAX, 0Fh				; �������� � EAX "�������" ������
					
					CALL HexToChar				; ����������� ������ � ��������������� ��� ������
					
					MOV ES:[EDI], AL			; ���������� ��� � �����
					INC EDI						; ��������� � ���������� ������� � ������
					
					ROL EDX, 8
					MOV EAX, EDX				; �������� ����� �������
					
					SUB ECX, 1					; ��������� ����� �������
					JGE @@DigitLoop				; ���� �� > 0, ���������� ������������ ������s
					
					MOV EAX, 0					; ����� ��� ������
					JMP @@EndProc				
		
@@BufferTooSmall:								; ����� � ������� "����� ������� ���"
					MOV EAX, 1
		
@@EndProc:
					POP EDX
					POP ECX
					POP EBX
					
					RET
					
HexToStr			endp