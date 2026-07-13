@echo off
setlocal enabledelayedexpansion

REM ============================================
REM   Chess Engine Build System (Debug/Release)
REM ============================================

REM --- Directories ---
set SRC_DIR=src
set INCLUDE_DIR=src\include
set BIN_DIR=bin
set OBJ_DEBUG=obj_debug
set OBJ_RELEASE=obj_release

REM --- Create folders if missing ---
for %%d in (%BIN_DIR% %OBJ_DEBUG% %OBJ_RELEASE%) do (
    if not exist %%d mkdir %%d
)

REM --- Choose build type ---
if "%1"=="" (
    echo Usage: build [debug|release]
    exit /b 1
)

if /I "%1"=="debug" (
    set MODE=debug
    set CFLAGS=-std=c++23 -O0 -g -Wall -Wextra -I %INCLUDE_DIR%
    set OBJ_DIR=%OBJ_DEBUG%
    set OUT_FILE=%BIN_DIR%\engine_debug.exe
)

if /I "%1"=="release" (
    set MODE=release
    set CFLAGS=-std=c++23 -O3 -march=native -flto -DNDEBUG -Wall -Wextra -I %INCLUDE_DIR%
    set OBJ_DIR=%OBJ_RELEASE%
    set OUT_FILE=%BIN_DIR%\engine.exe
)

echo ============================================
echo   Building Chess Engine (%MODE%)
echo ============================================

REM --- Compile all .cpp files ---
for /r %SRC_DIR% %%f in (*.cpp) do (
    set FILE=%%f
    set OBJ=%OBJ_DIR%\%%~nf.o

    echo [COMPILING] %%~nxf
    g++ %CFLAGS% -c !FILE! -o !OBJ!

    if !ERRORLEVEL! NEQ 0 (
        echo Compilation failed on %%~nxf
        exit /b 1
    )
)

REM --- Linking ---
echo [LINKING] %OUT_FILE%
g++ %OBJ_DIR%\*.o -o %OUT_FILE% %CFLAGS%

if %ERRORLEVEL% NEQ 0 (
    echo Linking failed!
    exit /b 1
)

echo ============================================
echo   Build successful!
echo   Output: %OUT_FILE%
echo ============================================

REM --- Auto-run (optional) ---
if /I "%2"=="run" (
    echo Running engine...
    %OUT_FILE%
)

endlocal
exit /b 0
