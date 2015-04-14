@ECHO OFF

IF '%1'=='' (ECHO File name not set & EXIT /B)

SET fileName=%1
IF /I '%fileName:~-4%'=='.asm' SET fileName=%fileName:~0,-4%

IF EXIST %fileName%.OBJ DEL %fileName%.OBJ
IF EXIST %fileName%.MAP DEL %fileName%.MAP
IF EXIST %fileName%.EXE DEL %fileName%.EXE
IF EXIST %fileName%.COM DEL %fileName%.COM

..\TASM\TASM /m5 /ml /zi %fileName%
IF ERRORLEVEL 1 goto exit

..\TASM\TLINK /v %fileName%
IF ERRORLEVEL 1 goto exit

%fileName%
IF '%2'=='1' ..\TASM\TD %fileName%.exe


:exit
echo.
pause
exit /b