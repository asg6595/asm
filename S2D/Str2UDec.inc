; ���������, �������������� �������������� ����������� ������, �������������� ���������� ����� � ���������� ����������� �����.
; ����:
	; DS:ESI ������ ������, ���������� �����
; �����:
	; EAX ���� ������
	; 0 ���� ������
		; EBX ������
		; DS:ESI ���������� �� ������ ������ ����� �����
	; 1 �������������������
		; DS:ESI ���������� �� ����
	; 2 �������� ������� �����(�� �� ��������� 0..2^32-1)
		; DS:ESI �������������
StrToUnsignedDec	proc
					
					mov ebx,0
@@DigitLoop:
					call IsDigit
					cmp eax, -1
					je @@NotDigit				; ������������� ������
					imul ebx, 10 
					jc @@IncorrectNumber					; ��� ������������ ������
					add ebx, eax
					jc @@IncorrectNumber					; ��� ������������ ������
					inc esi
					call IsSeparator			; �������� �� �����������
					cmp eax, 0 					; ���� �� ����������� ����� ��������� �����
					je @@DigitLoop
					
					mov eax, 0					; �������� ����������
					jmp @@EndOfProc
@@NotDigit:
					mov eax, 1
					jmp @@EndOfProc
@@IncorrectNumber:
					mov eax, 2
					jmp @@EndOfProc
@@EndOfProc:
					ret

StrToUnsignedDec	endp