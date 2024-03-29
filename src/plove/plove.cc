//==========================================================================
//  PLOVE.CC - part of
//
//                     OMNeT++/OMNEST
//            Discrete System Simulation in C++
//
//  contains: startup code
//
//==========================================================================

/*--------------------------------------------------------------*
  Copyright (C) 1992-2005 Andras Varga

  This file is distributed WITHOUT ANY WARRANTY. See the file
  `terms' for details on this and other legal matters.
*--------------------------------------------------------------*/

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <tk.h>

#ifdef HAVE_BLT
#include <blt.h>
// following decl is missing from BLT headers (2.4z)
extern "C" int Blt_Init(Tcl_Interp *interp);
#endif

#ifdef USE_WINMAIN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "tklib.h"
#include "../utils/ver.h"


int loadPlove(Tcl_Interp *interp)
{
    char *plove_dir;

    // path for the Tcl files
#ifdef OMNETPP_PLOVE_DIR
    plove_dir = getenv("OMNETPP_PLOVE_DIR");
    if (!plove_dir)
       plove_dir = OMNETPP_PLOVE_DIR;
#endif

    // add OMNeT++'s commands to Tcl
    createTkCommands( interp, tcl_commands );

    Tcl_SetVar(interp, "OMNETPP_RELEASE", OMNETPP_RELEASE, TCL_GLOBAL_ONLY);
    Tcl_SetVar(interp, "OMNETPP_EDITION", OMNETPP_EDITION, TCL_GLOBAL_ONLY);

    // load sources
#ifdef OMNETPP_PLOVE_DIR
    // Case A: TCL code in separate .tcl files
    //
    Tcl_SetVar(interp, "OMNETPP_PLOVE_DIR",  plove_dir, TCL_GLOBAL_ONLY);

    char fname[256];
    sprintf(fname,"%s/plove.tcl", plove_dir);
    if (Tcl_EvalFile(interp,fname)==TCL_ERROR)
    {
         printTclError(Tcl_GetStringResult(interp));
         fprintf(stderr, "Is OMNETPP_PLOVE_DIR set correctly?"
#ifdef _WIN32
                         " (e.g. C:\\omnetpp\\src\\plove)\n"
#else
                         " (e.g. /home/you/omnetpp/src/plove)\n"
#endif
                );
         return TCL_ERROR;
    }
#else
    // Case B: compiled-in TCL code
    //
    // The tclcode.cc file must be generated from the TCL scripts
    // with the tcl2c program (to be compiled from tcl2c.c).
    //
#include "tclcode.cc"
    if (Tcl_Eval(interp,(char *)tcl_code)==TCL_ERROR)
    {
         printTclError(Tcl_GetStringResult(interp));
         return TCL_ERROR;
    }
#endif

    // evaluate main script and build user interface
    if (Tcl_Eval(interp,"startPlove $argv")==TCL_ERROR)
    {
         printTclError(Tcl_GetStringResult(interp));
         Tcl_Eval(interp,"puts $errorInfo");
         return TCL_ERROR;
    }

    return TCL_OK;
}


int initPlove(Tcl_Interp *interp)
{
    if (Tcl_Init(interp)!=TCL_OK)
         return TCL_ERROR;
    if (Tk_Init(interp)!=TCL_OK)
         return TCL_ERROR;
    Tcl_StaticPackage(interp, "Tk", Tk_Init, Tk_SafeInit);
#ifdef HAVE_BLT
    if (Blt_Init(interp)!=TCL_OK)
         return TCL_ERROR;
    //Tcl_StaticPackage(interp, "Blt", Blt_Init, Blt_SafeInit);
#endif
    if (loadPlove(interp)!=TCL_OK)
        return TCL_ERROR;

    return TCL_OK;
}

#ifdef USE_WINMAIN
int APIENTRY
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    char **argv;
    int argc;
    setargv(&argc, &argv);
    Tk_Main(argc, argv, initPlove);
    return 1;
}
#else
int main(int argc, const char *argv[])
{
    runTkApplication(argc,argv,initPlove);
    return 0;
}
#endif


