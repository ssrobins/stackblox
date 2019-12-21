@echo off
setlocal

set build_dir=build_windows

cd /d %~dp0
if not exist %build_dir% mkdir %build_dir%
cd %build_dir%

cmake -G "Visual Studio 16 2019" -A Win32 .. || goto :error

set config=Release

cmake --build . --config %config% --verbose -- /m || goto :error

ctest -C %config% --output-on-failure || goto :error

cpack -C %config% || goto :error

:error
exit /b %errorlevel%
