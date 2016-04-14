Copyright (c) Autodesk, Inc. All rights reserved

AutoCAD/ObjectARX Wizards for Visual Studio by Cyrille Fauvel - Autodesk Developer Network (ADN)
Added Support for Visual Studio 2015 by Madhukar Moogala - Autodesk Developer Network (ADN)
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

ObjectARX-Wizards
AutoCAD ObjectARX Wizards for Visual Studio 2015

This wizard is compiled with WixToolset 3.8 and WinRAR.

It is supposed to install WixToolset into folder "C:\Program Files (x86)\WiX Toolset v3.8".
It is supposed to install WinRAR into folder "C:\Program Files\WinRAR"
If this is not the case for you, please go to ObjectARXWizardsInstaller\make.bat to correct the path.

Build Process

Build ArxWizPatchFilesCA\ArxWizPatchFiles.sln
Run ObjectARXWizardsInstaller\make.bat
If unsuccesful running wizard 
Follow :
•	Check  if all ascii files that cloned to local directory are of  windows complaint.
•	Check can be done in Notepad++ where in the right bottom corner you ‘ll get to know about EOL.
•	Execute following command to convert all files in directory [find . -type f -print0 | xargs -0 -n 1 -P 4 unix2dos]

