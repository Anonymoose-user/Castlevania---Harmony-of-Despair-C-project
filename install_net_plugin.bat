@echo off
rem install_net_plugin.bat - install a network plugin for online play and use it.
rem   install_net_plugin.bat path\to\plugin.dll     (or drag the .dll onto this file)
rem   install_net_plugin.bat gns                    (use an installed one: net\gns.dll)
rem   install_net_plugin.bat none                   (online play off)
setlocal
cd /d "%~dp0"
if "%~1"=="" (
  echo Installed plugins:
  dir /b net\*.dll 2^>nul
  echo.
  echo Usage: install_net_plugin.bat plugin.dll ^| name ^| none
  pause
  exit /b 1
)
set NAME=%~n1
if /i "%~x1"==".dll" (
  if not exist net mkdir net
  copy /y "%~1" net\ >nul || (echo Could not copy %~1 & pause & exit /b 1)
)
if /i not "%NAME%"=="none" if not exist "net\%NAME%.dll" (echo net\%NAME%.dll is not installed & pause & exit /b 1)
if not exist save mkdir save
if exist save\config.txt (findstr /v /b /c:"netPlugin " save\config.txt > save\config.tmp) else (type nul > save\config.tmp)
echo netPlugin %NAME%>> save\config.tmp
move /y save\config.tmp save\config.txt >nul
echo Online play now uses: %NAME%  (from the next start of the game)
pause
