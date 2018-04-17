# Steps To Build

1. Get Wix Toolset v3.11.0 [WixToolSet](http://wixtoolset.org/releases/v3.11.1/stable)
2. Get Wix Toolset for Visual Studio [VisualStudio2017Extension](https://marketplace.visualstudio.com/items?itemName=RobMensching.WixToolsetVisualStudio2017Extension)
3. Launch Visual Studio 2017, open ObjectArxWizardsInstaller\ObjectARXWizard2019.sln
4. You will find two projects
    1. ArxWizCustomAction: This is a custom action project to manipulate several text files post installation.
    2. ObjectARXWizard2019: This is main installer wix project
5. Make sure you always set MachineType to x86 for both the projects. MSI engine instantiates a 32 bit impersonated custom action server, or else you will get BadImageFormatException, and MSI will fail to read CustomAction Tables.
