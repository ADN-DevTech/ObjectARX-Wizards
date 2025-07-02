@echo off
setlocal enabledelayedexpansion

:: Set WiX tool paths - adjust if you installed WiX elsewhere
set WIX_BIN="%ProgramFiles(x86)%\WiX Toolset v3.14\bin"
set CANDLE=%WIX_BIN%\candle.exe
set LIGHT=%WIX_BIN%\light.exe
set EXT_PATH=%WIX_BIN%\WixVSExtension.dll

:: Input and output files
set WXS=ObjectARXWizards.wxs
set WIXOBJ=ObjectARXWizards.wixobj
set MSI=ObjectARX2026Wizards.msi

:: Clean old outputs
if exist %WIXOBJ% del /f %WIXOBJ%
if exist %MSI% del /f %MSI%

echo =====================================
echo Building installer for ObjectARX...
echo =====================================

:: Compile .wxs to .wixobj
%CANDLE% -I. -ext WixVSExtension %WXS%
if errorlevel 1 (
    echo candle.exe failed. Check for syntax or missing .wxi includes.
    exit /b 1
)

:: Link .wixobj to .msi
%LIGHT% -ext WixVSExtension -out %MSI% %WIXOBJ%
if errorlevel 1 (
    echo light.exe failed. Check for unresolved symbols or bad paths.
    exit /b 2
)

echo  Build succeeded: %MSI%
exit /b 0
