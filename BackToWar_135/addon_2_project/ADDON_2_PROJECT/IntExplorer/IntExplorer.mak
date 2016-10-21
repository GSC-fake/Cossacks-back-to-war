# Microsoft Developer Studio Generated NMAKE File, Based on IntExplorer.dsp
!IF "$(CFG)" == ""
CFG=IntExplorer - Win32 Debug
!MESSAGE No configuration specified. Defaulting to IntExplorer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "IntExplorer - Win32 Release" && "$(CFG)" != "IntExplorer - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IntExplorer.mak" CFG="IntExplorer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IntExplorer - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "IntExplorer - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "IntExplorer - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\IntExplorer.dll" "$(OUTDIR)\IntExplorer.pch"


CLEAN :
	-@erase "$(INTDIR)\DataXchange.obj"
	-@erase "$(INTDIR)\DString.obj"
	-@erase "$(INTDIR)\Explore.obj"
	-@erase "$(INTDIR)\FnDefine.obj"
	-@erase "$(INTDIR)\IntExplorer.obj"
	-@erase "$(INTDIR)\IntExplorer.pch"
	-@erase "$(INTDIR)\ParseRQ.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\IntExplorer.dll"
	-@erase "$(OUTDIR)\IntExplorer.exp"
	-@erase "$(OUTDIR)\IntExplorer.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "INTEXPLORER_EXPORTS" /Fp"$(INTDIR)\IntExplorer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IntExplorer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\IntExplorer.pdb" /machine:I386 /out:"$(OUTDIR)\IntExplorer.dll" /implib:"$(OUTDIR)\IntExplorer.lib" 
LINK32_OBJS= \
	"$(INTDIR)\DataXchange.obj" \
	"$(INTDIR)\DString.obj" \
	"$(INTDIR)\Explore.obj" \
	"$(INTDIR)\FnDefine.obj" \
	"$(INTDIR)\IntExplorer.obj" \
	"$(INTDIR)\ParseRQ.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"..\Exe\dmcr.lib"

"$(OUTDIR)\IntExplorer.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "IntExplorer - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "..\..\acr\IntExplorer.dll" "$(OUTDIR)\IntExplorer.pch"


CLEAN :
	-@erase "$(INTDIR)\DataXchange.obj"
	-@erase "$(INTDIR)\DString.obj"
	-@erase "$(INTDIR)\Explore.obj"
	-@erase "$(INTDIR)\FnDefine.obj"
	-@erase "$(INTDIR)\IntExplorer.obj"
	-@erase "$(INTDIR)\IntExplorer.pch"
	-@erase "$(INTDIR)\ParseRQ.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\IntExplorer.exp"
	-@erase "$(OUTDIR)\IntExplorer.lib"
	-@erase "$(OUTDIR)\IntExplorer.pdb"
	-@erase "..\..\acr\IntExplorer.dll"
	-@erase "..\..\acr\IntExplorer.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "INTEXPLORER_EXPORTS" /Fp"$(INTDIR)\IntExplorer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IntExplorer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\IntExplorer.pdb" /debug /machine:I386 /out:"d:\acr\IntExplorer.dll" /implib:"$(OUTDIR)\IntExplorer.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\DataXchange.obj" \
	"$(INTDIR)\DString.obj" \
	"$(INTDIR)\Explore.obj" \
	"$(INTDIR)\FnDefine.obj" \
	"$(INTDIR)\IntExplorer.obj" \
	"$(INTDIR)\ParseRQ.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"..\Exe\dmcr.lib"

"..\..\acr\IntExplorer.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("IntExplorer.dep")
!INCLUDE "IntExplorer.dep"
!ELSE 
!MESSAGE Warning: cannot find "IntExplorer.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "IntExplorer - Win32 Release" || "$(CFG)" == "IntExplorer - Win32 Debug"
SOURCE=.\DataXchange.cpp

"$(INTDIR)\DataXchange.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DString.cpp

"$(INTDIR)\DString.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Explore.cpp

"$(INTDIR)\Explore.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\FnDefine.cpp

"$(INTDIR)\FnDefine.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\IntExplorer.cpp

"$(INTDIR)\IntExplorer.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ParseRQ.cpp

"$(INTDIR)\ParseRQ.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "IntExplorer - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "INTEXPLORER_EXPORTS" /Fp"$(INTDIR)\IntExplorer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\IntExplorer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "IntExplorer - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "INTEXPLORER_EXPORTS" /Fp"$(INTDIR)\IntExplorer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\IntExplorer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

