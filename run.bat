@echo off
setlocal enabledelayedexpansion

set FILES=main.cpp Model/ProcessList.cpp 

:: Adicionar Process.cpp
set FILES=!FILES! Model/Process/Process.cpp

:: Incluir todos os arquivos de implementação das subclasses (confirme os caminhos)
set FILES=!FILES! Model/Process/ReadingProcess.cpp
set FILES=!FILES! Model/Process/WritingProcess.cpp
set FILES=!FILES! Model/Process/ComputingProcess.cpp
set FILES=!FILES! Model/Process/PrintingProcess.cpp

g++ %FILES% -I. -o main.exe 
if %errorlevel% neq 0 (
    echo Compilation failed.
    exit /b %errorlevel%
)
main.exe