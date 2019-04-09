using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Deployment.WindowsInstaller;
using System.IO;
using System.Diagnostics;
using System.Text.RegularExpressions;
using System.Windows.Forms;

//Custom Action changed by Madhukar Moogala ADN Devtech

namespace ArxWizPatchFiles {

    public class CustomActions {

        /// <summary>
        /// The Objective of this custom action is, we will replace [TARGETDIRECTORY] which is retrieved at time of Installation session in to
        /// several *.vsz file.
        /// We will not replace Wizversion, as every year MSVS comes with some new directory change, fix the [WIZVERSION] on several *.vsz files is becoming complex.
        /// We will change the WIZVERSION to hardcode value start copying.
        /// </summary>
        /// <param name="session"></param>
        /// <returns></returns>
        [CustomAction]
        public static ActionResult PatchVSFiles(Session session) {
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




        #region ForLegacy
        /*
        //Debugger.Break () ;
    //#if DEBUG
    //            int processId = Process.GetCurrentProcess().Id;
    //            string message = string.Format("Please attach the debugger (elevated on Vista or Win 7) to process [{0}].", processId);
    //            MessageBox.Show(message, "Debug");
    //#endif
        string TARGETDIR = session["TARGETDIR"];
        session["WIX_CA_LOGGING"] = TARGETDIR;
        session.Log(" >> PatchVSFiles: TARGETDIR = " + TARGETDIR);
        //C:\Program Files (x86)\Autodesk\ObjectARX 2018 Wizards\

        string pVSList = session["VSList"];
        char[] delimiterChars = { ' ', ',', ';', ':', '\t' };
        string[] VSList = pVSList.Split(delimiterChars);

        string pArxWizList = session["ArxWizList"];
        //session.Log(" >> PatchVSFiles: ArxWizList = " + pArxWizList);
        //ArxAppWiz;ArxAppWiz18_2;ArxAtlWizComWrapper;ArxAtlWizDynProp;ArxWizCustomObject;ArxWizJig;ArxWizMFCSupport;ArxWizNETWrapper;ArxWizReactors
        string[] ArxWizList = pArxWizList.Split(delimiterChars);
        List<string> lArxWizList = ArxWizList.ToList();

        //C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\
        for (int i = 0; i < VSList.Length; i++)
        {
            string vcFolder = session[VSList[i]];
            session["WIX_CA_LOGGING"] = i.ToString();
            session["WIX_CA_LOGGING"] = vcFolder;

            if ( VSList[i].Contains("EXPRESS") )
                vcFolder +=@"Express\";
            session.Log(" >> PatchVSFiles:   VSList = " + VSList[i] + " - " + vcFolder);
            if (vcFolder.Length == 0 || vcFolder.Contains(TARGETDIR) || !Directory.Exists(vcFolder))
                continue;

            Regex regex = new Regex(@"Microsoft Visual .* (\d+\.\d+)+");
            Match m = regex.Match(vcFolder);
            if (!m.Success)
                continue;
            string WIZVERSION = m.Groups[1].Value;
            session.Log(" >> PatchVSFiles:   WIZVERSION = " + WIZVERSION);


            session.Log(" >> PatchVSFiles:   Processing = " + vcFolder);
            DirectoryInfo di = new DirectoryInfo(vcFolder);
            FileInfo[] files = di.GetFiles("*.vsz", SearchOption.AllDirectories)
                                     //.Where(p => Path.GetFileNameWithoutExtension(p.Name) == ".msi").ToArray();
                                     .Where(p => lArxWizList.Contains(Path.GetFileNameWithoutExtension(p.Name))).ToArray();
            session.Log(" >> PatchVSFiles:   DirectoryInfo = " + files.Length.ToString ());
            foreach (FileInfo file in files)
            {
                try
                {
                    session.Log(" >> PatchVSFiles:   ArxWizList =>> " + file.FullName);
                    string szData = System.IO.File.ReadAllText(file.FullName);
                    szData = szData.Replace("[WIZVERSION]", WIZVERSION);
                    szData = szData.Replace("[TARGETDIR]", TARGETDIR);
                    System.IO.File.WriteAllText(file.FullName, szData);
                }
                catch
                {
                }
            }
        }

        session.Log("Ending PatchVSFiles");
        return (ActionResult.Success) ;*/

#endregion

        [CustomAction]
		public static ActionResult PatchHTMLWizFiles(Session session) {
			session.Log("Begin PatchHTMLWizFiles");
			//Debugger.Break () ;

			string TARGETDIR = session["TARGETDIR"];
			string RDS = session["RDS"];
			session.Log(" >> PatchHTMLWizFiles: RDS = " + RDS +" / TARGETDIR = " + TARGETDIR);
			//C:\Program Files (x86)\Autodesk\ObjectARX 2018 Wizards\

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

/*
' Autodesk.arx-2013.props
Call PatchSymbolInFile (Session.Property ("TARGETDIR") + "Autodesk.arx-2013.props", "ARXPATH")
Call PatchSymbolInFile (Session.Property ("TARGETDIR") + "Autodesk.arx-2013.props", "ACAD19_0")
Call PatchSymbolInFile (Session.Property ("TARGETDIR") + "Autodesk.arx-2013.props", "ACAD19_0")
Call PatchSymbolInFile (Session.Property ("TARGETDIR") + "ArxAppWiz\Templates\1033\Autodesk.arx-2013.props", "ARXPATH")
Call PatchSymbolInFile (Session.Property ("TARGETDIR") + "ArxAppWiz\Templates\1033\Autodesk.arx-2013.props", "ACAD19_0")
Call PatchSymbolInFile (Session.Property ("TARGETDIR") + "ArxAppWiz\Templates\1033\Autodesk.arx-2013.props", "ACAD19_0")
 *
 * */

/*
DirectoryInfo di = new DirectoryInfo(@"C:\");
FileInfo[] files = di.GetFiles("*.msi")
                     .Where(p => p.Extension == ".msi").ToArray();
foreach (FileInfo file in files)
    try
    {
        file.Attributes = FileAttributes.Normal;
        File.Delete(file.FullName);
    }
    catch { }
*/
