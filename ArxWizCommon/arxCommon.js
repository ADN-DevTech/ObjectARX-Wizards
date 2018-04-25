//- Copyright (c) Autodesk, Inc. All rights reserved.
//- by Cyrille Fauvel - Autodesk Developer Technical Services
//- Madhukar Moogala - Autodesk Developer Technical Services
var szWizardsVersion ="23, 0, 1, 0 - April 24 th, 2018" ;

var szArzWizApplicationTitle ="ObjectARX/DBX Application Wizard for AutoCAD 2019" ;
var szArxWizCOMWrapperTitle ="AutoCAD COM Wrapper Object" ;
var szArxWizDynPropTitle ="AutoCAD Object Dynamic Property" ;
var szArxWizObjectTitle ="ObjectDBX Custom Object Class Wizard" ;
var szArxWizJIGTitle ="ObjectARX Jig Class Wizard" ;
var szArxWizMFCTitle ="ObjectARX MFC Class Wizard" ;
var szArxWizDotNETWrapperTitle ="ObjectARX .NET Custom Object Wrapper Class Wizard" ;
var szArxWizReactorsTitle ="ObjectARX/DBX Transient Reactors Class Wizard" ;
var szArxMemVariableWizTitle ="Add Member Variable Wizard" ;

//wizard.OkCancelAlert ("msg");

//- Get an AutoCAD release
function FindAutoCAD() {
    var szPath = FindAutoCADUsingWMI("C:\\Program Files\\Autodesk\\AutoCAD 2019\\");
    return (szPath);
}

//- Get the RDS value
function GetRDSValue () {		
	var macros =window.external.ProjectObject.CodeModel.Macros ;
	//- It is defined as szRDS
	for ( var i =1 ; i <= macros.Count ; i++ ) {
		if ( macros.Item (i).name == "szRDS" ) {
			var szVal =macros.Item (i).value ;
			return (szVal.slice (szVal.indexOf ("\"") + 1, szVal.lastIndexOf ("\""))) ;
		}
	}
	return ("") ;
}

//- Check whether it is ARX / DBX applications
//- * a DBX project has either an acrxEntryPoint function or an AcRxDbxApp class
//-   it does not link to any AutoCAD libs
//-   it has the .dbx extension
//- * an ARX project is a DBX project, plus it links to AutoCAD libs
//-   it has the .arx extension
//- * a ObjectDBX host application can either be a .dll/.exe
//-   it links to rcexeobj.obj
function IsDbxProject (prj) {
	//- Verify it is a C++ project
	if ( prj.Kind != '{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}' )
		return (false) ;
	//- Verify project type (Static lib)
	var configType =prj.Object.Configurations (1).ConfigurationType
	if ( configType == 4 ) //- ConfigurationTypes.typeStaticLibrary
		return (true) ;
	//- Verify extension
	var outputName =prj.Object.Configurations (1).PrimaryOutput ;
	if (   outputName.substr (outputName.lastIndexOf ('.')).toLowerCase () != '.dbx'
		&& outputName.substr (outputName.lastIndexOf ('.')).toLowerCase () != '.dll'
	)
		return (false) ;
	//- Verify it has an acrxEntryPoint function or an AcRxDbxApp class
	var codeModel =prj.CodeModel ;
	for ( var i =1 ; i <= codeModel.Functions.Count ; i++ ) {
		var fct =codeModel.Functions.Item (i) ;
		if ( fct.Name == 'acrxEntryPoint' )
			break ;
	}
	for ( var j =1 ; j <= codeModel.Classes.Count ; j++ ) {
		var cls =codeModel.Classes.Item (j) ;
		if ( cls.IsDerivedFrom ('AcRxArxApp') )
			return (false) ;
		if ( cls.IsDerivedFrom ('AcRxDbxApp') )
			break ;
	}
	if ( i > codeModel.Functions.Count && j > codeModel.Classes.Count )
		return (false) ;
	//- Verify libs
	var linkTool =prj.Object.Configurations (1).Tools ('VCLinkerTool') ;
	var libs =linkTool.AdditionalDependancies ;
	if ( libs != null ) {
		libs =libs.toLowerCase () ;
		if ( libs.indexOf ('acad.lib') != -1 ) return (false) ;
		if ( libs.indexOf ('acbblclkeditpe.lib') != -1 ) return (false) ;
		if ( libs.indexOf ('acdbmpolygon') != -1 ) return (false) ;
		if ( libs.indexOf ('acedapi.lib') != -1 ) return (false) ;
		if ( libs.indexOf ('acui') != -1 ) return (false) ;
		if ( libs.indexOf ('adui') != -1 ) return (false) ;
		if ( libs.indexOf ('anav.lib') != -1 ) return (false) ;
		if ( libs.indexOf ('oleaprot.lib') != -1 ) return (false) ;
		if ( libs.indexOf ('actc.lib') != -1 ) return (false) ;
		if ( libs.indexOf ('actcui.lib') != -1 ) return (false) ;
		if ( libs.indexOf ('aseapi') != -1 ) return (false) ;
		if ( libs.indexOf ('asiapi') != -1 ) return (false) ;
	}
	//- Verify libs in #pragmas
	// .NET does not provide a way to do this, so we ignore this for now!
	
	return (true) ;
}

function IsDbxHostproject (prj) {
	//- Verify it is a C++ project
	if ( prj.Kind != '{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}' )
		return (false) ;
	//- Verify project type (static lib)
	var configType =prj.Object.Configurations (1).ConfigurationType 
	if ( configType == 4 ) //- ConfigurationTypes.typeStaticLibrary
		return (true) ;
	//- Verify extension
	var outputName =prj.Object.Configurations (1).PrimaryOutput ;
	if (   outputName.substr (outputName.lastIndexOf ('.')).toLowerCase () != '.exe'
		&& outputName.substr (outputName.lastIndexOf ('.')).toLowerCase () != '.dll'
	)
		return (false) ;
	//- Verify it has an acrxEntryPoint function or an AcRxDbxApp class
	var codeModel =prj.CodeModel ;
	for ( var i =1 ; i <= codeModel.Functions.Count ; i++ ) {
		var fct =codeModel.Functions.Item (i) ;
		if ( fct.Name == 'acrxEntryPoint' )
			break ;
	}
	for ( var j =1 ; j <= codeModel.Classes.Count ; j++ ) {
		var cls =codeModel.Classes.Item (j) ;
		if ( cls.IsDerivedFrom ('AcRxArxApp') )
			return (false) ;
		if ( cls.IsDerivedFrom ('AcRxDbxApp') )
			break ;
	}
	if ( i > codeModel.Functions.Count && j > codeModel.Classes.Count )
		return (false) ;
	//- Verify libs
	var linkTool =prj.Object.Configurations (1).Tools ('VCLinkerTool') ;
	var libs =linkTool.AdditionalDependancies ;
	if ( libs == null )
		return (false) ;
	libs =libs.toLowerCase () ;
	if ( libs.indexOf ('acad.lib') != -1 ) return (false) ;
	if ( libs.indexOf ('acbblclkeditpe.lib') != -1 ) return (false) ;
	if ( libs.indexOf ('acdbmpolygon') != -1 ) return (false) ;
	if ( libs.indexOf ('acedapi.lib') != -1 ) return (false) ;
	if ( libs.indexOf ('acui') != -1 ) return (false) ;
	if ( libs.indexOf ('adui') != -1 ) return (false) ;
	if ( libs.indexOf ('anav.lib') != -1 ) return (false) ;
	if ( libs.indexOf ('oleaprot.lib') != -1 ) return (false) ;
	if ( libs.indexOf ('actc.lib') != -1 ) return (false) ;
	if ( libs.indexOf ('actcui.lib') != -1 ) return (false) ;
	if ( libs.indexOf ('aseapi') != -1 ) return (false) ;
	if ( libs.indexOf ('asiapi') != -1 ) return (false) ;
	//- For this one, it must be there
	if ( libs.indexOf ('rcexelib.obj') == -1 ) return (false) ;
	//- Verify libs in #pragmas
	// .NET does not provide a way to do this, so we ignore this for now!
	
	return (true) ;
}

function IsCrxProject (prj) {
	//- Verify it is a C++ project
	if ( prj.Kind != '{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}' )
		return (false) ;
	//- Verify project type (static lib)
	var configType =prj.Object.Configurations (1).ConfigurationType 
	if ( configType == 4 ) //- ConfigurationTypes.typeStaticLibrary
		return (true) ;
	//- Verify extension
	var outputName =prj.Object.Configurations (1).PrimaryOutput ;
	if (   outputName.substr (outputName.lastIndexOf ('.')).toLowerCase () != '.crx'
		&& outputName.substr (outputName.lastIndexOf ('.')).toLowerCase () != '.dll'
	)
		return (false) ;
	//- Verify it has an acrxEntryPoint function or an AcRxDbxApp class
	var codeModel =prj.CodeModel ;
	for ( var i =1 ; i <= codeModel.Functions.Count ; i++ ) {
		var fct =codeModel.Functions.Item (i) ;
		if ( fct.Name == 'acrxEntryPoint' )
			break ;
	}
	for ( var j =1 ; j <= codeModel.Classes.Count ; j++ ) {
		var cls =codeModel.Classes.Item (j) ;
		if ( cls.IsDerivedFrom ('AcRxArxApp') )
			break ;
	}
	if ( i > codeModel.Functions.Count && j > codeModel.Classes.Count )
		return (false) ;
	//- Verify libs
	var linkTool =prj.Object.Configurations (1).Tools ('VCLinkerTool') ;
	var libs =linkTool.AdditionalDependancies ;
	if ( libs != null ) {
		libs =libs.toLowerCase () ;
		if ( libs.indexOf ('acad.lib') != -1 ) return (false) ;
		if ( libs.indexOf ('acbblclkeditpe.lib') != -1 ) return (false) ;
		if ( libs.indexOf ('acedapi.lib') != -1 ) return (false) ;
		if ( libs.indexOf ('adui') != -1 ) return (false) ;
		if ( libs.indexOf ('anav.lib') != -1 ) return (false) ;
		if ( libs.indexOf ('oleaprot.lib') != -1 ) return (false) ;
		if ( libs.indexOf ('aseapi') != -1 ) return (false) ;
		if ( libs.indexOf ('asiapi') != -1 ) return (false) ;
		//- Verify libs in #pragmas
		// .NET does not provide a way to do this, so we ignore this for now!
	}
	return (true) ;
}

function IsArxProject (prj) {
	//- Verify it is a C++ project
	if ( prj.Kind != '{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}' )
		return (false) ;
	//- Verify project type (static lib)
	var configType =prj.Object.Configurations (1).ConfigurationType 
	if ( configType == 4 ) //- ConfigurationTypes.typeStaticLibrary
		return (true) ;
	//- Verify extension
	var outputName =prj.Object.Configurations (1).PrimaryOutput ;
	if (   outputName.substr (outputName.lastIndexOf ('.')).toLowerCase () != '.arx'
		&& outputName.substr (outputName.lastIndexOf ('.')).toLowerCase () != '.dll'
	)
		return (false) ;
	//- Verify it has an acrxEntryPoint function or an AcRxDbxApp class
	var codeModel =prj.CodeModel ;
	for ( var i =1 ; i <= codeModel.Functions.Count ; i++ ) {
		var fct =codeModel.Functions.Item (i) ;
		if ( fct.Name == 'acrxEntryPoint' )
			break ;
	}
	for ( var j =1 ; j <= codeModel.Classes.Count ; j++ ) {
		var cls =codeModel.Classes.Item (j) ;
		if ( cls.IsDerivedFrom ('AcRxArxApp') )
			break ;
	}
	if ( i > codeModel.Functions.Count && j > codeModel.Classes.Count )
		return (false) ;

	return (true) ;
}

function IsValidAdeskProject (prj, level) {
	//- Levels: (bitwise)
	//-   1- .dbx Object Enabler
	//-   2- .arx AutoCAD Application
	//-   4- .exe/.dll ObjectDBX Host Application
	//-   8- .crx AutoCAD Console Application
	var dbx =IsDbxProject (prj) ;
	var crx =IsCrxProject (prj) ;
	var arx =IsArxProject (prj) ;
	var host =IsDbxHostproject (prj) ;

	switch ( level ) {
		case 1: return (dbx) ;
		case 2: return (arx) ;
		case 3: return (dbx | arx) ;
		case 4: return (host) ;
		case 5: return (dbx | host) ;
		case 6: return (arx | host) ;
		case 7: return (dbx | arx | host) ;
		case 8: return (crx) ;
		case 9: return (dbx | crx) ;
		case 10: return (arx | crx) ;
		case 11: return (dbx | arx | crx) ;
		case 12: return (host | crx) ;
		case 13: return (dbx | host | crx) ;
		case 14: return (arx | host | crx) ;
		case 15: return (dbx | arx | host | crx) ;
		default: break ;
	}
	return (false) ;
}

//- Is that class derived at least from AcDbObject
function IsDbxObject(cls) {
    return (cls.IsDerivedFrom('AcDbObject'));
}

//- Calling ARX Wizard's help
function InvokeArxWizardHelp () {
	var myUrl =window.external.FindSymbol("ABSOLUTE_PATH") ;
	var myName =window.external.FindSymbol("WIZARD_NAME") ;
	myUrl =myUrl.substring (0, myUrl.lastIndexOf ("\\") + 1) ;
	open ("ms-its:" + myUrl + "ArxWizardHelp.chm::HTML/" + myName + ".htm") ;
}
