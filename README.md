# ObjectARX Wizards for Visual Studio

**AutoCAD/ObjectARX Wizards for Visual Studio 2022**  
*by Cyrille Fauvel, Madhukar Moogala - Autodesk Developer Network (ADN)*

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

---

## 📋 Overview

This repository contains Visual Studio project wizards for **ObjectARX** development, making it easier to create AutoCAD plugins and applications. The wizards provide templates and boilerplate code for various ObjectARX development scenarios.

### Available Wizards

- **ArxAppWiz** - Main ObjectARX application wizard
- **ArxWizCustomObject** - Custom AutoCAD entity creation
- **ArxWizReactors** - Event-driven reactor implementations  
- **ArxWizJig** - Interactive drawing jigs
- **ArxWizMFCSupport** - MFC-based UI components
- **ArxWizNETWrapper** - .NET wrapper classes
- **ArxAtlWizComWrapper** - COM component wrappers
- **ArxAtlWizDynProp** - Dynamic property implementations

---

## 🚀 Getting Started

### Prerequisites

- **Visual Studio 2019 or 2022**
- **ObjectARX SDK** (corresponding to your AutoCAD version)
- **WiX Toolset v3.14.0** (for building the installer)
- **AutoCAD** (for testing your ObjectARX applications)

### 📥 Clone the Repository

```bash
git clone https://github.com/ADN-DevTech/ObjectARX-Wizards.git
cd ObjectARX-Wizards
```

### 🔨 Build Instructions

For detailed build instructions, see **[StepsToBuild.md](ObjectARXWizardsInstaller/StepsToBuild.md)**

**Quick Build Steps:**

1. Install [WiX Toolset v3.14.0](https://wixtoolset.org/releases/v3-14-0-712/)
2. Install [WiX Toolset Visual Studio Extension](https://marketplace.visualstudio.com/items?itemName=WixToolset.WixToolsetVisualStudio2019Extension)
3. Open `ObjectARXWizardsInstaller/ObjectARXWizard.sln` in Visual Studio
4. Set configuration to **x86** for both projects
5. Build the solution to generate the installer

### 💾 Installation

1. Build the installer MSI using the steps above
2. Run the generated MSI file as **Administrator**
3. Restart Visual Studio
4. The wizards will appear in **File → New → Project** under Visual C++

---

## 🔧 Troubleshooting

**Wizards not appearing in Visual Studio?** 

See our comprehensive **[Troubleshooting Guide](ObjectARX%20Wizard%20Troubleshooting%20Guide.md)** for solutions to common issues including:

- MEF cache clearing
- Visual Studio configuration reset
- Permission and compatibility issues

---

## 📁 Project Structure

```
ObjectARX-Wizards/
├── ArxAppWiz/              # Main application wizard
├── ArxWizCustomObject/     # Custom object wizard  
├── ArxWizReactors/         # Reactor wizard templates
├── ArxWizJig/              # Jig wizard templates
├── ArxWizMFCSupport/       # MFC support templates
├── ArxWizNETWrapper/       # .NET wrapper templates
├── ArxAtlWizComWrapper/    # COM wrapper templates
├── ArxAtlWizDynProp/       # Dynamic property templates
├── ObjectARXWizardsInstaller/ # MSI installer project
└── _Installs/              # Installation files and props
```

---

## 🤝 Contributing

Contributions are welcome! Please feel free to submit issues and pull requests.

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Submit a pull request

---

## 📄 License

Copyright (c) Autodesk, Inc. All rights reserved 

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## 🔗 Resources

- [ObjectARX Documentation](https://help.autodesk.com/view/OARX/2024/ENU/)
- [AutoCAD Developer Center](https://www.autodesk.com/developer-network/platform-technologies/autocad)
- [Autodesk Developer Network](https://www.autodesk.com/developer-network)

---

**Happy ObjectARX Development! 🎯**
