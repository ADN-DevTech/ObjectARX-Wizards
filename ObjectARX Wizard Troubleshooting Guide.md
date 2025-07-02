# 🔧 ObjectARX Wizard Troubleshooting Guide

*Having trouble seeing your ObjectARX wizards in Visual Studio? Don't worry - this guide will help you get them working!*

> 📖 **Also See**: [README.md](README.md) for installation instructions and [StepsToBuild.md](ObjectARXWizardsInstaller/StepsToBuild.md) for building the installer.

---

## 🚨 Common Issues

When ObjectARX wizards or Visual Studio extensions don't appear as expected, it's usually due to one of these common issues:

- **Visual Studio's internal cache corruption** 
- **Incorrect installation permissions**
- **Visual Studio version mismatch**
- **Corrupted wizard files or registry entries**

---

## 🧹 **Solution 1: Clear the MEF Cache** ⭐ *Most Effective*

The **Managed Extensibility Framework (MEF)** cache can become corrupted, especially after installing or updating extensions. This prevents wizards from loading properly.

### Steps:

1. **Close Visual Studio completely**
   - Make sure all Visual Studio processes are terminated
   - Check Task Manager if necessary

2. **Delete the MEF cache folders:**
   - Navigate to: `%LocalAppData%\Microsoft\VisualStudio\17.0_xxxxx\ComponentModelCache`
   - **For Visual Studio 2019**: `%LocalAppData%\Microsoft\VisualStudio\16.0_xxxxx\ComponentModelCache`
   - **For Visual Studio 2022**: `%LocalAppData%\Microsoft\VisualStudio\17.0_xxxxx\ComponentModelCache`
   - Delete **all files and folders** inside this directory
   
3. **Restart Visual Studio**

Visual Studio will automatically rebuild the cache with fresh data, which often resolves wizard visibility issues.

> 💡 **Tip**: You can also delete the entire `17.0_xxxxx` folder if you want a complete reset, but this will reset all your Visual Studio settings.

---

## ⚙️ **Solution 2: Reset Visual Studio Configuration**

If clearing the MEF cache doesn't resolve the issue, try resetting Visual Studio's internal configuration using command-line switches.

### Available Commands:

Run these from the **Developer Command Prompt for Visual Studio** (Run as Administrator):

- **Reset skipped packages:**
  ```cmd
  devenv.exe /ResetSkipPkgs
  ```

- **Force configuration update:**
  ```cmd
  devenv.exe /UpdateConfiguration
  ```

- **Reset all settings (nuclear option):**
  ```cmd
  devenv.exe /ResetSettings
  ```

- **Clear template cache:**
  ```cmd
  devenv.exe /InstallVSTemplates
  ```

---

## 🔍 **Solution 3: Verify Installation**

### Check Installation Paths

Ensure the wizard files are installed in the correct locations:

**For Visual Studio 2022:**
- `%USERPROFILE%\Documents\Visual Studio 2022\Templates\ProjectTemplates\Visual C++\`
- `%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Community\Common7\IDE\VC\vcprojects\`




---

## 🔨 **Solution 4: Reinstall the Wizards**

If other solutions don't work, try a clean reinstallation:

1. **Uninstall** the current ObjectARX Wizards (if installed via MSI)
2. **Clear cache** using Solution 1 above
3. **Rebuild the installer** following the [StepsToBuild.md](ObjectARXWizardsInstaller/StepsToBuild.md) guide
4. **Install as Administrator**
5. **Restart Visual Studio**

---

## 🔒 **Solution 5: Permission Issues**

### Run as Administrator
- Always install the MSI package with **Administrator privileges**
- Run Visual Studio as Administrator during the first launch after installation

### Folder Permissions
Check that you have write permissions to:
- Visual Studio installation directories
- User template folders
- Windows registry (for wizard registration)

---

## 🎯 **Solution 6: Version Compatibility**

### Check Compatibility Matrix

| Visual Studio Version | ObjectARX Version | AutoCAD Version | Status |
|----------------------|------------------|-----------------|---------|
| VS 2022 | ObjectARX 2025 | AutoCAD 2025 | ✅ Supported |
| VS 2022 | ObjectARX 2024 | AutoCAD 2024 | ✅ Supported |
| VS 2019 | ObjectARX 2023 | AutoCAD 2023 | ✅ Supported |
| VS 2019 | ObjectARX 2022 | AutoCAD 2022 | ✅ Supported |

### Update Paths
Ensure you're using the correct wizard version for your:
- Visual Studio version
- ObjectARX SDK version  
- Target AutoCAD version

---

## 🔧 **Advanced Troubleshooting**

### Enable Visual Studio Logging

1. **Create a registry key**:
   - Path: `HKEY_CURRENT_USER\Software\Microsoft\VisualStudio\<version>\General`
   - Name: `EnableLogging`
   - Type: `DWORD`
   - Value: `1`

2. **Check logs** in: `%APPDATA%\Microsoft\VisualStudio\<version>\ActivityLog.xml`

### Wizard File Verification

Verify these files exist and are not corrupted:
- `*.vsz` files (wizard definition)
- `*.vsdir` files (directory entries)
- Template files in the Templates folder
- Associated resource files (icons, etc.)

---

## 📞 **Still Having Issues?**

If these solutions don't resolve your problem, the issue might be:

### Build-Related Issues
- **Incorrect build configuration** - See [StepsToBuild.md](ObjectARXWizardsInstaller/StepsToBuild.md)
- **Missing dependencies** - Check WiX Toolset installation
- **Custom action failures** - Debug using the guide in StepsToBuild.md

### Environment Issues
- **Corrupted Visual Studio installation** - Consider repairing/reinstalling VS
- **Windows permission restrictions** - Check group policies
- **Antivirus interference** - Temporarily disable during installation

### Installation Issues  
- **MSI installation errors** - Check Windows Event Logs
- **Silent installation failures** - Try interactive installation
- **Previous version conflicts** - Completely uninstall old versions

---

## 📋 **Troubleshooting Checklist**

Before reporting issues, please verify:

- [ ] Visual Studio is completely closed before troubleshooting
- [ ] You have Administrator privileges
- [ ] ObjectARX SDK is properly installed
- [ ] Correct Visual Studio version compatibility
- [ ] MEF cache has been cleared
- [ ] Visual Studio configuration has been reset
- [ ] Wizards are installed in the correct directories
- [ ] No antivirus software is blocking the installation
- [ ] Windows is up to date
- [ ] You've restarted your computer after installation

---

## 🆘 **Getting Help**

If you're still experiencing issues:

1. **Check the logs** (ActivityLog.xml, Windows Event Logs)
2. **Document your environment** (VS version, Windows version, ObjectARX version)
3. **Create a GitHub issue** with detailed information
4. **Include error messages** and log files

---

**Remember**: Most wizard visibility issues are resolved by clearing the MEF cache and restarting Visual Studio! 🎯
