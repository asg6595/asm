;
; ��������� ��� ������ ��������� ����� � �����
;
; ����:
; 		EAX - �������� �����
;		ES:EDI - ����� ������, ���� ����� �������� �����
;

NumToBuffer				proc

						push eax
						
						; cmp eax, 0					; ���������� ���� �����
						; jge @@PositiveNumber
						
						; neg eax						; ������ �� ����� �������������
						
						; call UnsignedNumSize
						
						; mov byte ptr es:[edi], '-'
						; inc edi
@@PositiveNumber:
			
						call UnsignedNumToBuffer		
						
						pop eax
						
						ret
						
NumToBuffer				endp
