@echo off

set "file=%~1"

:loop
if not exist "%file%" (
  timeout /t 1 /nobreak > nul
  goto loop
)

exit /b 0
