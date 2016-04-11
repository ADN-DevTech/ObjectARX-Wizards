1. VS 2015 has become more strict wrt to warnings.
C4838 :conversion from 'int' to 'UINT' requires a narrowing conversion, this is new warning introduced in VS2015, to understand this error, write following console sample in VS2015
int main()
{
	unsigned int i = { -1 };
	printf("%d", i);
	return 0;
}





Or To overcome error, wizard is using warning version flag /Wv:xx[.yy[.zzzzz], currently there is seems to be a bug adding flag interactively, hence I enforced with wizard in .vcxproj file.

You can remove flag from VS editor, goto C\C++->CommandLine->/Wv:17.00.61030, if remove flag:

Following function inside acrxentrypoint file would result in warning.
Troubleshooting “C4838 :conversion from 'int' to 'UINT' requires a narrowing conversion”.


This problem will arise if creating project with wizard and lisp function such as is used
static int ads_MyLispFunction () {
		//struct resbuf *args =acedGetArgs () ;
		
		// Put your command code here

		//acutRelRb (args) ;
		
		// Return a value to the AutoCAD Lisp Interpreter
		// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal

		return (RTNORM) ;
	}
ACED_ADSSYMBOL_ENTRY_AUTO(CSampleWithWizardApp, MyLispFunction, false)
To overcome error, open “arxEntryPoint.h” at line 74
struct _ADSSYMBOL_ENTRY {
    const ACHAR *pszName ;
    int (*fptr) () ;
    bool bRegFunc ;
    UINT nameID ;
} ;


2. Use of ATL from "Project Defaults" might have deprecated in VS2015, hence I suppressed in the Wizard too.

3. Small fix to MixedManaged code to support  Metaobjectprovider like acdbObjectId in .NET system.core assembly is required.
	#define GETOBJECTID(id)     (*reinterpret_cast<AcDbObjectId*>(&(id))), so I added System.Core to assembly reference.