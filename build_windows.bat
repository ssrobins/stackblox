@echo off
setlocal

set build_dir=build_windows

cd /d %~dp0
if not exist %build_dir% mkdir %build_dir%
cd %build_dir%

conan remote add bintray-stever https://api.bintray.com/conan/stever/conan --insert --force || goto :error

conan install --update .. -s arch=x86 -s compiler.version=16 -s compiler.runtime=MT || goto :error

cmake -G "Visual Studio 16 2019" -A Win32 .. || goto :error

set config=Release

cmake --build . --config %config% -- /m || goto :error

ctest -C %config% --output-on-failure || goto :error

cpack -C %config% || goto :error

:error
exit /b %errorlevel%
