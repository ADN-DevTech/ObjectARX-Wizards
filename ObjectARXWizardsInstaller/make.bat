@echo off
%~d0
cd /d %~dp0

if exist w:\nul subst w: /d
subst w: "C:\Program Files (x86)\WiX Toolset v3.8"

w:\bin\candle.exe ObjectARXWizards.wxs -out temp\ObjectARXWizards.wixobj
w:\bin\light.exe -sw1076 -b .. temp\ObjectARXWizards.wixobj -out ObjectARXWizards.msi 
rem -ext WixUIExtension
if exist ObjectARXWizards-2018.zip del ObjectARXWizards-2018.zip > nul
"C:\Program Files\WinRAR\WinRAR.exe" a ObjectARXWizards-2018.zip ObjectARXWizards.msi > nul

pause