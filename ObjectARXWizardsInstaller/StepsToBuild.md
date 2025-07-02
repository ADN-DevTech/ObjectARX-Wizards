# 🔨 Steps To Build ObjectARX Wizards Installer

This guide will walk you through building the MSI installer for the ObjectARX Wizards.

---

## 📋 Prerequisites

Before you begin, ensure you have the following installed:

1. **Visual Studio 2019 or 2022** with C++ development tools
2. **WiX Toolset v3.14.0** - [Download Here](https://wixtoolset.org/releases/v3-14-0-712/)
3. **WiX Toolset Visual Studio Extension** - [Get from Marketplace](https://marketplace.visualstudio.com/items?itemName=WixToolset.WixToolsetVisualStudio2019Extension)

> ⚠️ **Important**: Make sure to install WiX v3.14.0 specifically, as newer versions may have compatibility issues.

---

## 🏗️ Build Process

### Step 1: Setup Environment

1. **Install WiX Toolset**
   - Download and install [WiX Toolset v3.14.0](https://wixtoolset.org/releases/v3-14-0-712/)
   - Restart your computer after installation

2. **Install Visual Studio Extension**
   - Install the [WiX Toolset Visual Studio Extension](https://marketplace.visualstudio.com/items?itemName=WixToolset.WixToolsetVisualStudio2019Extension)
   - Restart Visual Studio

### Step 2: Open the Solution

1. Navigate to the `ObjectARXWizardsInstaller` folder
2. Open `ObjectARXWizard.sln` in Visual Studio

### Step 3: Configure Projects

The solution contains two important projects:

#### 1. **ArxWizCustomAction** 
- Custom action project for post-installation file manipulation
- **Configuration**: Set to **x86** (32-bit)

#### 2. **ObjectARXWizard** 
- Main WiX installer project
- **Configuration**: Set to **x86** (32-bit)

> ⚠️ **Critical**: Both projects MUST be set to **x86** architecture. The MSI engine uses a 32-bit custom action server, and using x64 will cause `BadImageFormatException` errors.

### Step 4: Build the Solution

1. **Set Configuration**:
   - Configuration: `Release` (or `Debug` for debugging)
   - Platform: `x86`

2. **Build**:
   - Right-click the solution → **Build Solution**
   - Or use `Ctrl+Shift+B`

3. **Output**:
   - The MSI installer will be generated in the `bin` folder
   - Look for `ObjectARXWizards.msi`

---

## 🐛 Debugging Custom Actions

Need to debug the installation process? Follow these steps:

### Setup Debug Environment

1. **Open ArxWizCustomAction Project**
2. **Change Configuration to Debug**
3. **Notice the Debug Code**:
   ```csharp
   #if DEBUG 
   System.Diagnostics.Debugger.Launch(); 
   #endif
   ```

### Debug Process

1. **Build with Debug Configuration**
2. **Run the MSI Installer**
3. **Debugger Launch**:
   - MSI will break at the custom action
   - Visual Studio "Just-In-Time" debugger will launch
   - Attach to the process and debug normally

4. **Source Code Access**:
   - The debugger will automatically find your custom action source code
   - Set breakpoints and step through the code as needed

---

## 📁 Project Structure

```
ObjectARXWizardsInstaller/
├── ObjectARXWizard.sln          # Main solution file
├── ObjectARXWizard.wixproj       # WiX installer project
├── ArxWizCustomAction.csproj     # Custom action C# project
├── ObjectARXWizards.wxs          # WiX source file (main)
├── directory.wxi                 # Directory structure definitions
├── feature.wxi                   # Feature definitions
├── property.wxi                  # Property definitions
├── UI.wxi                        # User interface definitions
├── Binary/                       # Custom action binaries
└── temp/                         # Temporary build files
```

---

## ⚠️ Common Issues & Solutions

### Build Errors

| Issue | Solution |
|-------|----------|
| `BadImageFormatException` | Ensure both projects are set to **x86** platform |
| WiX not found | Install WiX Toolset v3.14.0 and restart VS |
| Custom action fails | Check that custom action DLL is properly referenced |
| Missing dependencies | Verify all ObjectARX wizard files are present |

### Installation Issues

- **Run as Administrator**: Always install the MSI with administrator privileges
- **Visual Studio Restart**: Restart Visual Studio after installation
- **Clear Cache**: If wizards don't appear, see the [Troubleshooting Guide](../ObjectARX%20Wizard%20Troubleshooting%20Guide.md)

---

## 🎯 Next Steps

After successfully building:

1. **Test the MSI**: Install on a clean machine to verify functionality
2. **Deploy**: Distribute the MSI to users
3. **Documentation**: Refer users to the main [README.md](../README.md) for usage instructions

---

**Need help?** Check the [Troubleshooting Guide](../ObjectARX%20Wizard%20Troubleshooting%20Guide.md) for common installation issues!
