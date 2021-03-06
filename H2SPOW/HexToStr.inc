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
		
					CMP ECX, 15					; ���� ������ ������ < 15
					JB @@BufferTooSmall			; �� ������� � ������� (��� 1)
					
					MOV ECX, 7					; ������� ��������� � 7 �������
		
@@DigitLoop:
					MOV EBX, 16	
					CALL Pow					; �������� 16 � ������� �������
					MOV EDX, 0					; ������ = ����� / (16 ^ ����� �������)
					DIV EBX						; ����� = ���� % (16 ^ ����� �������)
					
					CALL HexToChar				; ����������� ������ � ��������������� ��� ������
					
					MOV ES:[EDI], AL			; ���������� ��� � �����
					INC EDI					; ��������� � ���������� ������� � ������
					
					cmp ecx, 0
					je @@label1
					mov byte ptr es:[edi], '_'
					inc edi
@@label1:
					
					MOV EAX, EDX
					
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