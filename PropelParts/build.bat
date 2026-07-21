@echo OFF
ninja.exe
if %errorlevel%==0 echo d | xcopy /y "./bin" "%DOLPHIN_USER_DIR%\Load\Riivolution\PropelParts-KP\Code"
