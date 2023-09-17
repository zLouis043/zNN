@echo off

cls

@echo:
@echo [INFO] Run make in bin folder.
cd bin
make
@echo [INFO] Run znn.exe: 
@echo ON
znn.exe --h
@echo: 
@echo off
if errorlevel 1 (
    @echo [ERROR] ********** BUILD FAILURE **********   
    exit /b 1
)
@echo [INFO] Program ended successfully.
