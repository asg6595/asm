; ��������� ������ ��������� ����� � �����
; ����:
;		eax - �����
;		es:edi - ����� �������
; �����:
;		 es:edi- ��������� �� ��������� ������ ����� ����� � �������

SignedNumberToBuffer		proc

				push eax

				cmp eax, 0
				jge @@NumberIsUnsigned
				
				mov byte ptr [edi], '-'			; ���������� ��� � �����
				inc edi						; ��������� � ���������� ������� � ������
				
				neg eax
				
@@NumberIsUnsigned:
				call UnsignedNumberToBuffer
				
				pop eax
				
				ret
				
SignedNumberToBuffer		endp
