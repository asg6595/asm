;
; ��������� ��� ������ �������� � �����
;
; ����:
; 		EDX - ����� ��������
;		ES:EDI - ����� ������, ���� ����� �������� �������
;
SpacesToBuffer		proc

					push edx
					jmp @@LoopStart
					
@@SpaceLoop:
					mov byte ptr es:[edi], ' '
					inc edi

					dec edx

@@LoopStart:
					cmp edx, 0
					jg @@SpaceLoop
					
					pop edx
					
					ret
					
SpacesToBuffer		endp
