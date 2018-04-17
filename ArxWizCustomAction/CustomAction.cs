using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using Microsoft.Deployment.WindowsInstaller;
using System.Text.RegularExpressions;
using System.IO;
using System.Diagnostics;

//Written by Madhukar Moogala ADN

namespace ArxWizCustomAction
{
    public class CustomActions
    {

        /// <summary>
        /// The Objective of this custom action is, we will replace [TARGETDIRECTORY] which is retrieved at time of Installation session in to
        /// several *.vsz file.
        /// We will not replace Wizversion, as every year MSVS comes with some new directory change, fix the [WIZVERSION] on several *.vsz files is becoming complex.
        /// We will change the WIZVERSION to hardcode value start copying.
        /// </summary>
        /// <param name="session"></param>
        /// <returns></returns>
        [CustomAction]
        public static ActionResult PatchVSFiles(Session session)
        {
            session.Log("Begin PatchVSFiles");
            string TARGETDIR = session["TARGETDIR"];
            //This gives us the right folder where the wizard files are sitting.
            string vcFolder = session["D_VS2017VCFOLDER"];
            //This is very ugly trick to find out values while installation is executing.
            session["WIX_CA_LOGGING"] = vcFolder;

            char[] delimiterChars = { ' ', ',', ';', ':', '\t' };

            //ArxAppWiz;ArxAppWiz18_2;ArxAtlWizComWrapper;ArxAtlWizDynProp;ArxWizCustomObject;ArxWizJig;ArxWizMFCSupport;ArxWizNETWrapper;ArxWizReactors
            string pArxWizList = session["ArxWizList"];
            session.Log(" >> PatchVSFiles: ArxWizList = " + pArxWizList);

            string[] ArxWizList = pArxWizList.Split(delimiterChars);
            List<string> lArxWizList = ArxWizList.ToList();

            session.Log(" >> PatchVSFiles:   Processing = " + vcFolder);
            DirectoryInfo di = new DirectoryInfo(vcFolder);
            FileInfo[] files = di.GetFiles("*.vsz", SearchOption.AllDirectories)
                                 .Where(p => lArxWizList.Contains(Path.GetFileNameWithoutExtension(p.Name))).ToArray();
            session.Log(" >> PatchVSFiles:   DirectoryInfo = " + files.Length.ToString());
            foreach (FileInfo file in files)
            {
                try
                {
                    session.Log(" >> PatchVSFiles:   ArxWizList =>> " + file.FullName);
                    string szData = System.IO.File.ReadAllText(file.FullName);
                    szData = szData.Replace("[TARGETDIR]", TARGETDIR);
                    System.IO.File.WriteAllText(file.FullName, szData);
                }
                catch
                {
                }
            }
            session.Log("Ending PatchVSFiles");
            return (ActionResult.Success);
        }
        
        /// <summary>
        /// This custom action updates the default.htm with user given registered developer symbol [RDS]
        /// </summary>
        /// <param name="session"></param>
        /// <returns>ActionResult</returns>
        [CustomAction]
        public static ActionResult PatchHTMLWizFiles(Session session)
        {
            session.Log("Begin PatchHTMLWizFiles");
            //Debugger.Break () ;

            string TARGETDIR = session["TARGETDIR"];
            string RDS = session["RDS"];
            session.Log(" >> PatchHTMLWizFiles: RDS = " + RDS + " / TARGETDIR = " + TARGETDIR);
            //C:\Program Files (x86)\Autodesk\ObjectARX 2019 Wizards\

            DirectoryInfo di = new DirectoryInfo(TARGETDIR);
            FileInfo[] files = di.GetFiles("default.htm", SearchOption.AllDirectories)
                             .Where(p => p.DirectoryName.Contains("AppWiz")).ToArray();
            session.Log(" >> PatchHTMLWizFiles:   DirectoryInfo = " + files.Length.ToString());
            foreach (FileInfo file in files)
            {
                try
                {
                    session.Log(" >> PatchHTMLWizFiles:   =>> " + file.FullName);
                    string szData = System.IO.File.ReadAllText(file.FullName);
                    szData = szData.Replace("<SYMBOL NAME='RDS_SYMB' TYPE='text' VALUE='asdk'></SYMBOL>", "<SYMBOL NAME='RDS_SYMB' TYPE='text' VALUE='" + RDS + "'></SYMBOL>");
                    System.IO.File.WriteAllText(file.FullName, szData);
                }
                catch
                {
                }
            }

            session.Log("Ending PatchHTMLWizFiles");
            return (ActionResult.Success);
        }
        /// <summary>
        /// This custom action will update ArxSdkDir and ACAD Elements in Autodesk.arx-2019.props file post installation 
        /// </summary>
        /// <param name="session"></param>
        /// <returns>ActionResult</returns>

        [CustomAction]
        public static ActionResult PatchPropsWizFiles(Session session)
        {
            session.Log("Begin PatchPropsWizFiles");
            //Debugger.Break () ;

            string TARGETDIR = session["TARGETDIR"];
            string ARXPATH = session["ARXPATH"];
            session.Log(" >> PatchPropsWizFiles: ARXPATH = " + ARXPATH + " / TARGETDIR = " + TARGETDIR);
            //C:\Program Files (x86)\Autodesk\ObjectARX 2019 Wizards\
            string ACAD = session["ACAD"];
            session.Log(" >> PatchPropsWizFiles: ACAD = " + ACAD);

            DirectoryInfo di = new DirectoryInfo(TARGETDIR);
            FileInfo[] files = di.GetFiles("*2019*.props", SearchOption.AllDirectories).ToArray();
            session.Log(" >> PatchPropsWizFiles:   DirectoryInfo = " + files.Length.ToString());
            foreach (FileInfo file in files)
            {
                try
                {
                    session.Log(" >> PatchPropsWizFiles:   =>> " + file.FullName);
                    string szData = System.IO.File.ReadAllText(file.FullName);
                    szData = szData.Replace(@"<ArxSdkDir>C:\ObjectARX\</ArxSdkDir>", @"<ArxSdkDir>" + ARXPATH + "</ArxSdkDir>");
                    szData = szData.Replace("<AcadDir Condition=\"'$(Platform)'=='x64'\">C:\\Program Files\\Autodesk\\AutoCAD 2019\\</AcadDir>", "<AcadDir Condition=\"'$(Platform)'=='x64'\">" + ACAD + "</AcadDir>");
                    szData = szData.Replace("<AcadDir Condition=\"'$(Platform)'=='Win32'\">C:\\Program Files (x86)\\Autodesk\\AutoCAD 2019\\</AcadDir>", "<AcadDir Condition=\"'$(Platform)'=='Win32'\">" + ACAD + "</AcadDir>");
                    System.IO.File.WriteAllText(file.FullName, szData);
                }
                catch
                {
                }

            }
            session.Log("Ending PatchPropsWizFiles");
            return (ActionResult.Success);
        }

    }
}
