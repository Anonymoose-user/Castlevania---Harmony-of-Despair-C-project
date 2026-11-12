@echo off
rem Build one game module DLL with the CVHD modding kit (cmd.exe):
rem   build_module.bat <player|enemy|shot> <source folder> <dll name> [output folder]
setlocal enabledelayedexpansion
if "%~3"=="" (echo usage: build_module.bat ^<player^|enemy^|shot^> ^<source folder^> ^<dll name^> [output folder] & exit /b 1)
set FAM=%~1
set SRC=%~f2
set NAME=%~3
set OUT=%~f4
if "%~4"=="" set OUT=%CD%
set KIT=%~dp0
if "%KIT:~-1%"=="\" set KIT=%KIT:~0,-1%
if /i not "%FAM%"=="player" if /i not "%FAM%"=="enemy" if /i not "%FAM%"=="shot" (echo family must be player, enemy or shot & exit /b 1)
set LLVM=%LLVM_BIN%
if "%LLVM%"=="" set LLVM=C:\Program Files\LLVM\bin
if not exist "%LLVM%\clang-cl.exe" (
  for %%X in (clang-cl.exe) do set LLVM=%%~dp$PATH:X
  if "!LLVM!"=="" (echo ERROR: LLVM not found. Install LLVM ^(clang-cl, lld-link^) to C:\Program Files\LLVM or put its bin folder on PATH. & exit /b 1)
  if "!LLVM:~-1!"=="\" set LLVM=!LLVM:~0,-1!
)
if not exist "%OUT%" mkdir "%OUT%"
set OBJ=%OUT%\obj_%NAME%
if not exist "%OBJ%" mkdir "%OBJ%"
set CF=-nologo -c -Z7 -O1 -std:c++17 -EHsc -Wno-everything -DCVHD_NATIVE=1 -DCVHD_MODULE=1 -MTd -D_DEBUG "-I%KIT%\include" "-I%SRC%"
set OBJS=
set EXPORTS=-export:cvhdModuleInit
set FILES=
for /r "%SRC%" %%F in (*.cpp) do set FILES=!FILES! "%%F"
if /i "%FAM%"=="player" set FILES=!FILES! "%KIT%\src\PlayerTuning.cpp"
for %%F in (!FILES!) do (
  echo compile %%~nxF
  "%LLVM%\clang-cl.exe" %CF% "%%~F" "-Fo%OBJ%\%%~nxF.obj" || exit /b 1
  "%LLVM%\llvm-nm.exe" --defined-only "%OBJ%\%%~nxF.obj" | findstr /c:" T cvhdModuleShutdown" >nul && set EXPORTS=!EXPORTS! -export:cvhdModuleShutdown
  set OBJS=!OBJS! "%OBJ%\%%~nxF.obj"
)
rem image base: relocatable, above 4 GB, a 2 MB slot from the name's CRC32
for /f %%B in ('powershell -NoProfile -Command "$c=[uint32]4294967295;foreach($b in [Text.Encoding]::ASCII.GetBytes('%NAME%')){$c=$c -bxor $b;for($i=0;$i -lt 8;$i++){if($c -band 1){$c=($c -shr 1) -bxor 3988292384}else{$c=$c -shr 1}}};$c=$c -bxor 4294967295;'0x{0:X}' -f (0x500000000+($c %% 120)*0x200000)"') do set BASE=%%B
if "%BASE%"=="" set BASE=0x500000000
echo link %NAME%.dll (base %BASE%)
"%LLVM%\lld-link.exe" -nologo -dll -debug "-out:%OUT%\%NAME%.dll" %EXPORTS% -base:%BASE% -dynamicbase -highentropyva:no -largeaddressaware %OBJS% "%KIT%\lib\cvhd_%FAM%.lib" libcmtd.lib libcpmtd.lib kernel32.lib || exit /b 1
del /q "%OUT%\%NAME%.lib" "%OUT%\%NAME%.exp" 2>nul
echo built %OUT%\%NAME%.dll
