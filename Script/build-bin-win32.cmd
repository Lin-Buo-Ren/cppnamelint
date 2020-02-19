@ECHO OFF

python --version        > NUL
IF "9009"=="%ERRORLEVEL%"   (GOTO :ERROR)

git --version           > NUL
IF "9009"=="%ERRORLEVEL%"   (GOTO :ERROR)

cmake --version         > NUL
IF "9009"=="%ERRORLEVEL%"   (GOTO :ERROR)

clang-format --version  > NUL
IF "9009"=="%ERRORLEVEL%"   (GOTO :ERROR)


ECHO ==============================================================
ECHO Git submodule
ECHO ==============================================================
PUSHD ..
git submodule init
git submodule update
POPD

ECHO.
ECHO.
ECHO ==============================================================
ECHO Reformat source files
ECHO ==============================================================
python BuildFlow.py lint-format ..\Source

ECHO.
ECHO.
ECHO ==============================================================
ECHO Static source files analyzation
ECHO ==============================================================
::python build-flow.py lint analyze ..\Source
ECHO Skipped

ECHO.
ECHO.
ECHO ==============================================================
ECHO Generate makefile via CMake
ECHO ==============================================================
SET BUILD_TYPE=
IF /I "Release"=="%1"        (SET BUILD_TYPE="Release")
IF /I "RelWithDebInfo"=="%1" (SET BUILD_TYPE="RelWithDebInfo")
IF /I "Debug"=="%1"          (SET BUILD_TYPE="Debug")
python BuildFlow.py proj-create .. ..\Build %BUILD_TYPE%

ECHO.
ECHO.
ECHO ==============================================================
ECHO Build project
ECHO ==============================================================
::msbuild build-win32\namelint.sln /t:build /p:Configuration=Debug /p:Platform="Win32"

GOTO :EXIT

:ERROR

:EXIT
PAUSE

@ECHO ON
