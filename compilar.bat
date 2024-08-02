@echo off
setlocal enabledelayedexpansion
set FILES=

FOR /R %%i IN (*.cpp) DO (
    set FILES=!FILES! "%%i"
)

g++ -Wall -g %FILES% -o app.out
