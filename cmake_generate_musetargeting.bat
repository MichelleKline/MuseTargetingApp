
@ECHO OFF
SETLOCAL

SET DIR_SRC=.
SET DIR_BUILD=_build_

IF [%DIR_DEV_TOOLS%]==[] CALL :PrintError "Please define the required environment variable DIR_DEV_TOOLS."
SET "CMAKE=%DIR_DEV_TOOLS%\cmake\bin\cmake.exe"

SET TEST_DEPS_BIN=D:\Qt\5.15.1\msvc2019\bin
SET PATH=%TEST_DEPS_BIN%;%Path%

SET SLN_DIR=%DIR_BUILD%\vs2019_x32
REM Use -A Win32 for x32, and -A x64 for x64

%CMAKE% -S "%DIR_SRC%" -B "%DIR_BUILD%\vs2019_x32" -G "Visual Studio 16 2019" -A Win32
REM %CMAKE% -S "%DIR_SRC%" -B "%DIR_BUILD%\vs2019_x64" -G "Visual Studio 16 2019" -A x64

%DIR_DEV_TOOLS%\cmake\bin\cmake.exe --open %SLN_DIR%
REM POPD

ENDLOCAL
PAUSE
GOTO:eof

:PrintError
ECHO Error: %1
PAUSE
EXIT 42
GOTO:eof
..