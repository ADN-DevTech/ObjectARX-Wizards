using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Deployment.WindowsInstaller;
using System.IO;
using System.Xml;
using System.Text.RegularExpressions;
using System.Xml.Linq;
using System.Diagnostics;
using System.Windows.Forms;

//Written by Madhukar Moogala ADN

namespace ArxWizCustomAction
{
    public static class CustomActions
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
            string vcFolder = session["D_VS2022VCFOLDER"];

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
                    string szData = File.ReadAllText(file.FullName);
                    szData = szData.Replace("[TARGETDIR]", TARGETDIR);
                    File.WriteAllText(file.FullName, szData);
                    session.Log("\n" + szData);
                }
                catch (Exception ex)
                {
                    session.Log(ex.Message);
                    return ActionResult.Failure;
                }
            }
            session.Log("Ending PatchVSFiles");
            return (ActionResult.Success);
        }

       
        [CustomAction]
        public static ActionResult PatchHTMLWizFiles(Session session)
        {

            session.Log("Begin PatchHTMLWizFiles");
            string TARGETDIR = session["TARGETDIR"];
            string RDS = String.IsNullOrEmpty(session["RDS"]) ? "ADSK" : session["RDS"];
            session.Log(" >> PatchHTMLWizFiles: RDS = " + RDS + " / TARGETDIR = " + TARGETDIR);
            //C:\Program Files (x86)\Autodesk\ObjectARX 2025 Wizards\

            DirectoryInfo di = new DirectoryInfo(TARGETDIR);
            FileInfo[] files = di.GetFiles("default.htm", SearchOption.AllDirectories)
                             .Where(p => p.DirectoryName.Contains("AppWiz")).ToArray();
            session.Log(" >> PatchHTMLWizFiles:   DirectoryInfo = " + files.Length.ToString());
            foreach (FileInfo file in files)
            {
                try
                {
                    session.Log(" >> PatchHTMLWizFiles:   =>> " + file.FullName);
                    string szData = File.ReadAllText(file.FullName);
                    szData = szData.Replace("ADSK", RDS);
                    File.WriteAllText(file.FullName, szData);
                }
                catch (Exception ex)
                {
                    session.Log(ex.Message);
                    return ActionResult.Failure;
                }
            }

            session.Log("Ending PatchHTMLWizFiles");
            return (ActionResult.Success);
        }
        /// <summary>
        /// This custom action will update ArxSdkDir and ACAD Elements in Autodesk.arx-2020.props file post installation 
        /// </summary>
        /// <param name="session"></param>
        /// <returns>ActionResult</returns>

        [CustomAction]
        public static ActionResult PatchPropsWizFiles(Session session)
        {
#if DEBUG
            int processId = Process.GetCurrentProcess().Id;
            string message = string.Format("Please attach the debugger to process [{0}].", processId);
            MessageBox.Show(message, "Debug");
#endif    
            session.Log("Begin PatchPropsWizFiles");
            //Debugger.Break () ;

            string TARGETDIR = session["TARGETDIR"];
            string ARXPATH = session["ARXPATH"];
            session.Log(" >> PatchPropsWizFiles: ARXPATH = " + ARXPATH + " / TARGETDIR = " + TARGETDIR);
            //C:\Program Files (x86)\Autodesk\ObjectARX 2025 Wizards\
            string ACAD = session["ACAD"];
            session.Log(" >> PatchPropsWizFiles: ACAD = " + ACAD);

            DirectoryInfo di = new DirectoryInfo(TARGETDIR);
            FileInfo[] files = di.GetFiles("*2025.props", SearchOption.AllDirectories).ToArray();
            session.Log(" >> PatchPropsWizFiles:   DirectoryInfo = " + files.Length.ToString());
            var _arxpath = ARXPATH;
            var _acad = ACAD;
            foreach (FileInfo file in files)
            {
                try
                {
                    session.Log(" >> PatchPropsWizFiles:   =>> " + file.FullName);
                    string content = File.ReadAllText(file.FullName);
                    content = content.Replace(@"C:\ObjectARX\", _arxpath);
                    var from = @"C:\Program Files\Autodesk\AutoCAD 2025\"; 
                    var to = _acad;
                    session.Log($" >> PatchPropsWizFiles:   =>> replacing {from} with {to}");
                    content = content.Replace(from, to);
                    File.WriteAllText(file.FullName, content);
                    session.Log(" >> PatchPropsWizFiles:   =>> saving"); 

                }
                catch (Exception ex)
                {
                    session.Log(ex.Message);
                    return ActionResult.Failure;
                }

            }
            session.Log("Ending PatchPropsWizFiles");
            return (ActionResult.Success);
        }

    }
}
