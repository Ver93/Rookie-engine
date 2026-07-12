@echo off
setlocal enabledelayedexpansion

echo ===============================
echo   Building Chess Engine...
echo ===============================

REM --- Directories ---
set SRC_DIR=src
set INCLUDE_DIR=src\include
set BIN_DIR=bin
set OBJ_DIR=obj
set TEST_DIR=tests
set OBJ_TEST_DIR=obj_tests

REM --- Create folders if missing ---
if not exist %BIN_DIR% mkdir %BIN_DIR%
if not exist %OBJ_DIR% mkdir %OBJ_DIR%
if not exist %OBJ_TEST_DIR% mkdir %OBJ_TEST_DIR%

echo Compiling engine source files...

for /r %SRC_DIR% %%f in (*.cpp) do (
    set FILE=%%f
    set OBJ=%OBJ_DIR%\%%~nf.o

    echo [ENGINE BUILD] %%~nxf
    g++ -std=c++23 -O0 -g -Wall -Wextra -I %INCLUDE_DIR% -c !FILE! -o !OBJ!
)

echo Linking engine.exe...

g++ %OBJ_DIR%\*.o -o %BIN_DIR%\engine.exe

if %ERRORLEVEL% NEQ 0 (
    echo Engine build failed!
    pause
    exit /b 1
)

echo Engine build successful!
echo Output: %BIN_DIR%\engine.exe