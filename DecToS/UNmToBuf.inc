; ��������� ������ ������������ ����� � �����
; ����:
;		eax - �����
;		es:edi - ����� �������
; �����:
;		es:edi - ��������� �� ��������� ������ ����� ����� � �������

UnsignedNumberToBuffer		proc
				
				push eax
				push ebx
				push ecx
				push edx
				
				call UnsignedNumberSize

				dec edx
				
@@DigitLoop:
				mov ebx, 10	
				mov ecx, edx
				
				call Pow					; �������� 10 � ������� �������
				
				push edx
				
				mov edx, 0					; ������ = ����� / (10 ^ ����� �������)
				div ebx						; ����� = ��c�� % (10 ^ ����� �������)
				
				add al, '0'					; ����������� ������ � ��������������� ��� ������
					
				mov es:[edi], al			; ���������� ��� � �����
				inc edi						; ��������� � ���������� ������� � ������
				
				mov eax, edx
				
				pop edx
					
				sub edx, 1					; ��������� ����� �������
				jge @@DigitLoop				; ���� �� > 0, ���������� ������������ ������s
					
				mov eax, 0					; ����� ��� ������
				jmp @@EndProc	
				
@@EndProc:
				pop edx
				pop ecx
				pop ebx
				pop eax
				
				ret
				
UnsignedNumberToBuffer		endp
