@ECHO OFF

IF '%1'=='' (ECHO File name not set & EXIT /B)

SET fileName=%1
IF /I '%fileName:~-4%'=='.asm' SET fileName=%fileName:~0,-4%

subst u: "%cd%\.."
D:\dosbox\DOSBOX.EXE -c "mount c: D:/Asm" -c "c:" -c "cd S2D" -c "tasm_exe %fileName% %2"
subst u: /d