# Microsoft Developer Studio Project File - Name="ddexam" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ddexam - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DmCraft.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DmCraft.mak" CFG="ddexam - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ddexam - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_WINDOWS" /YX /FD /c
# SUBTRACT CPP /WX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib libc.lib oldnames.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib /out:"D:\Exchange\OLIMP\dmcr.exe" /FIXED:NO /MAPINFO:LINES /MAPINFO:EXPORTS
# SUBTRACT LINK32 /pdb:none
# Begin Target

# Name "ddexam - Win32 Release"
# Begin Group "Dump"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Ddini.h
# End Source File
# Begin Source File

SOURCE=.\Dplay.h
# End Source File
# Begin Source File

SOURCE=.\event.h
# End Source File
# Begin Source File

SOURCE=.\Lines.cpp
# End Source File
# Begin Source File

SOURCE=.\Lines.h
# End Source File
# Begin Source File

SOURCE=.\menu.cpp
# End Source File
# Begin Source File

SOURCE=.\menu.h
# End Source File
# Begin Source File

SOURCE=.\mgraph.h
# End Source File
# Begin Source File

SOURCE=.\mode.h
# End Source File
# Begin Source File

SOURCE=.\MoveToXY.cpp
# End Source File
# Begin Source File

SOURCE=.\Resfile.cpp
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# End Group
# Begin Group "Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Dpchat.h
# End Source File
# Begin Source File

SOURCE=.\Dplobby.h
# End Source File
# Begin Source File

SOURCE=.\fog.h
# End Source File
# Begin Source File

SOURCE=.\Multipl.h
# End Source File
# Begin Source File

SOURCE=.\Nucl.h
# End Source File
# Begin Source File

SOURCE=.\Resfile.h
# End Source File
# End Group
# Begin Group "datas"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Austria.nds
# End Source File
# Begin Source File

SOURCE=.\complex.lst
# End Source File
# Begin Source File

SOURCE=.\complex.rsr
# End Source File
# Begin Source File

SOURCE=.\england.nds
# End Source File
# Begin Source File

SOURCE=.\holelist.LST
# End Source File
# Begin Source File

SOURCE=.\holelist.rsr
# End Source File
# Begin Source File

SOURCE=.\Nres.dat
# End Source File
# Begin Source File

SOURCE=.\Orcs.nds
# End Source File
# Begin Source File

SOURCE=.\Orcs.scr
# End Source File
# Begin Source File

SOURCE=.\Peoples.nds
# End Source File
# Begin Source File

SOURCE=.\SoundList.txt
# End Source File
# Begin Source File

SOURCE=.\stonlist.LST
# End Source File
# Begin Source File

SOURCE=.\stonlist.rsr
# End Source File
# Begin Source File

SOURCE=.\textures.lst
# End Source File
# Begin Source File

SOURCE=.\Treelist.lst
# End Source File
# Begin Source File

SOURCE=.\treelist.rsr
# End Source File
# Begin Source File

SOURCE=.\Walls.lst
# End Source File
# Begin Source File

SOURCE=.\Weapon.ads
# End Source File
# Begin Source File

SOURCE=.\Weapon.nds
# End Source File
# End Group
# Begin Group "New Monsters Discription"

# PROP Default_Filter "md"
# Begin Source File

SOURCE=.\Adet.md
# End Source File
# Begin Source File

SOURCE=.\aka.md
# End Source File
# Begin Source File

SOURCE=.\arc.md
# End Source File
# Begin Source File

SOURCE=.\Ardt.md
# End Source File
# Begin Source File

SOURCE=.\art.md
# End Source File
# Begin Source File

SOURCE=.\Artt.md
# End Source File
# Begin Source File

SOURCE=.\ba1.md
# End Source File
# Begin Source File

SOURCE=.\bae.md
# End Source File
# Begin Source File

SOURCE=.\bar.md
# End Source File
# Begin Source File

SOURCE=.\bas.md
# End Source File
# Begin Source File

SOURCE=.\Bat.md
# End Source File
# Begin Source File

SOURCE=.\bfg.md
# End Source File
# Begin Source File

SOURCE=.\Brt.md
# End Source File
# Begin Source File

SOURCE=.\Cal.md
# End Source File
# Begin Source File

SOURCE=.\Cau.md
# End Source File
# Begin Source File

SOURCE=.\Ceb.md
# End Source File
# Begin Source File

SOURCE=.\Cef.md
# End Source File
# Begin Source File

SOURCE=.\Ceh.md
# End Source File
# Begin Source File

SOURCE=.\Cei.md
# End Source File
# Begin Source File

SOURCE=.\Center_UR.md
# End Source File
# Begin Source File

SOURCE=.\Cep.md
# End Source File
# Begin Source File

SOURCE=.\cer.md
# End Source File
# Begin Source File

SOURCE=.\Ces.md
# End Source File
# Begin Source File

SOURCE=.\Cet.md
# End Source File
# Begin Source File

SOURCE=.\Ceu.md
# End Source File
# Begin Source File

SOURCE=.\Che.md
# End Source File
# Begin Source File

SOURCE=.\Cpl.md
# End Source File
# Begin Source File

SOURCE=.\Crp.md
# End Source File
# Begin Source File

SOURCE=.\Csw.md
# End Source File
# Begin Source File

SOURCE=.\cur.md
# End Source File
# Begin Source File

SOURCE=.\cyb.md
# End Source File
# Begin Source File

SOURCE=.\Dal.md
# End Source File
# Begin Source File

SOURCE=.\Dau.md
# End Source File
# Begin Source File

SOURCE=.\dip.md
# End Source File
# Begin Source File

SOURCE=.\Dipt.md
# End Source File
# Begin Source File

SOURCE=.\dkaz.md
# End Source File
# Begin Source File

SOURCE=.\dob.md
# End Source File
# Begin Source File

SOURCE=.\Dof.md
# End Source File
# Begin Source File

SOURCE=.\Dog.md
# End Source File
# Begin Source File

SOURCE=.\Doi.md
# End Source File
# Begin Source File

SOURCE=.\Dop.md
# End Source File
# Begin Source File

SOURCE=.\Dos.md
# End Source File
# Begin Source File

SOURCE=.\Dot.md
# End Source File
# Begin Source File

SOURCE=.\Dpl.md
# End Source File
# Begin Source File

SOURCE=.\Dpr.md
# End Source File
# Begin Source File

SOURCE=.\Dr2.md
# End Source File
# Begin Source File

SOURCE=.\dra.md
# End Source File
# Begin Source File

SOURCE=.\Drf.md
# End Source File
# Begin Source File

SOURCE=.\Dsw.md
# End Source File
# Begin Source File

SOURCE=.\Ens.md
# End Source File
# Begin Source File

SOURCE=.\Env.md
# End Source File
# Begin Source File

SOURCE=.\eud.md
# End Source File
# Begin Source File

SOURCE=.\evr.md
# End Source File
# Begin Source File

SOURCE=.\evro.md
# End Source File
# Begin Source File

SOURCE=.\Field1.md
# End Source File
# Begin Source File

SOURCE=.\fir.md
# End Source File
# Begin Source File

SOURCE=.\Freg.md
# End Source File
# Begin Source File

SOURCE=.\Gal.md
# End Source File
# Begin Source File

SOURCE=.\get.md
# End Source File
# Begin Source File

SOURCE=.\Gnf.md
# End Source File
# Begin Source File

SOURCE=.\grass1.md
# End Source File
# Begin Source File

SOURCE=.\Gre.md
# End Source File
# Begin Source File

SOURCE=.\grr1.md
# End Source File
# Begin Source File

SOURCE=.\gu2.md
# End Source File
# Begin Source File

SOURCE=.\gul.md
# End Source File
# Begin Source File

SOURCE=.\gun.md
# End Source File
# Begin Source File

SOURCE=.\Gus.md
# End Source File
# Begin Source File

SOURCE=.\Iconlist.txt
# End Source File
# Begin Source File

SOURCE=.\imp.md
# End Source File
# Begin Source File

SOURCE=.\Jia.md
# End Source File
# Begin Source File

SOURCE=.\k2z.md
# End Source File
# Begin Source File

SOURCE=.\Kaa.md
# End Source File
# Begin Source File

SOURCE=.\kaz.md
# End Source File
# Begin Source File

SOURCE=.\kaz1.md
# End Source File
# Begin Source File

SOURCE=.\kni.md
# End Source File
# Begin Source File

SOURCE=.\Kof.md
# End Source File
# Begin Source File

SOURCE=.\kom.md
# End Source File
# Begin Source File

SOURCE=.\kon.md
# End Source File
# Begin Source File

SOURCE=.\konush.md
# End Source File
# Begin Source File

SOURCE=.\kor.md
# End Source File
# Begin Source File

SOURCE=.\kos.md
# End Source File
# Begin Source File

SOURCE=.\Kot.md
# End Source File
# Begin Source File

SOURCE=.\Kpo.md
# End Source File
# Begin Source File

SOURCE=.\kr3.md
# End Source File
# Begin Source File

SOURCE=.\kre.md
# End Source File
# Begin Source File

SOURCE=.\Krp.md
# End Source File
# Begin Source File

SOURCE=.\Krs.md
# End Source File
# Begin Source File

SOURCE=.\Krt.md
# End Source File
# Begin Source File

SOURCE=.\kru.md
# End Source File
# Begin Source File

SOURCE=.\kst.md
# End Source File
# Begin Source File

SOURCE=.\Ksw.md
# End Source File
# Begin Source File

SOURCE=.\Kut.md
# End Source File
# Begin Source File

SOURCE=.\kuz.md
# End Source File
# Begin Source File

SOURCE=.\Kvt.md
# End Source File
# Begin Source File

SOURCE=.\kzk.md
# End Source File
# Begin Source File

SOURCE=.\L2t.md
# End Source File
# Begin Source File

SOURCE=.\Link.md
# End Source File
# Begin Source File

SOURCE=.\lo2.md
# End Source File
# Begin Source File

SOURCE=.\lo3.md
# End Source File
# Begin Source File

SOURCE=.\Lo4.md
# End Source File
# Begin Source File

SOURCE=.\Lod.md
# End Source File
# Begin Source File

SOURCE=.\lok.md
# End Source File
# Begin Source File

SOURCE=.\los.md
# End Source File
# Begin Source File

SOURCE=.\Lpf.md
# End Source File
# Begin Source File

SOURCE=.\Lpt.md
# End Source File
# Begin Source File

SOURCE=.\Lre.md
# End Source File
# Begin Source File

SOURCE=.\mac.md
# End Source File
# Begin Source File

SOURCE=.\Mam.md
# End Source File
# Begin Source File

SOURCE=.\man.md
# End Source File
# Begin Source File

SOURCE=.\MDHelp.txt
# End Source File
# Begin Source File

SOURCE=.\Mel.md
# End Source File
# Begin Source File

SOURCE=.\meln.md
# End Source File
# Begin Source File

SOURCE=.\meln2.md
# End Source File
# Begin Source File

SOURCE=.\Met.md
# End Source File
# Begin Source File

SOURCE=.\Mit.md
# End Source File
# Begin Source File

SOURCE=.\mor.md
# End Source File
# Begin Source File

SOURCE=.\Mua.md
# End Source File
# Begin Source File

SOURCE=.\mue.md
# End Source File
# Begin Source File

SOURCE=.\Mun.md
# End Source File
# Begin Source File

SOURCE=.\Mup.md
# End Source File
# Begin Source File

SOURCE=.\mus.md
# End Source File
# Begin Source File

SOURCE=.\Mut.md
# End Source File
# Begin Source File

SOURCE=.\nmlist.txt
# End Source File
# Begin Source File

SOURCE=.\Of2.md
# End Source File
# Begin Source File

SOURCE=.\ofi.md
# End Source File
# Begin Source File

SOURCE=.\Oft.md
# End Source File
# Begin Source File

SOURCE=.\Paa.md
# End Source File
# Begin Source File

SOURCE=.\pe2.md
# End Source File
# Begin Source File

SOURCE=.\pie.md
# End Source File
# Begin Source File

SOURCE=.\Pik.md
# End Source File
# Begin Source File

SOURCE=.\Pip.md
# End Source File
# Begin Source File

SOURCE=.\pir.md
# End Source File
# Begin Source File

SOURCE=.\pis.md
# End Source File
# Begin Source File

SOURCE=.\pla.md
# End Source File
# Begin Source File

SOURCE=.\Prs.md
# End Source File
# Begin Source File

SOURCE=.\Psm.md
# End Source File
# Begin Source File

SOURCE=.\pul.md
# End Source File
# Begin Source File

SOURCE=.\pus.md
# End Source File
# Begin Source File

SOURCE=.\ric.md
# End Source File
# Begin Source File

SOURCE=.\rin.md
# End Source File
# Begin Source File

SOURCE=.\Rit.md
# End Source File
# Begin Source File

SOURCE=.\roc.md
# End Source File
# Begin Source File

SOURCE=.\rst.md
# End Source File
# Begin Source File

SOURCE=.\Rua.md
# End Source File
# Begin Source File

SOURCE=.\rud.md
# End Source File
# Begin Source File

SOURCE=.\rus.md
# End Source File
# Begin Source File

SOURCE=.\Sag.md
# End Source File
# Begin Source File

SOURCE=.\Sak.md
# End Source File
# Begin Source File

SOURCE=.\Sam.md
# End Source File
# Begin Source File

SOURCE=.\sar.md
# End Source File
# Begin Source File

SOURCE=.\sce.md
# End Source File
# Begin Source File

SOURCE=.\sh2.md
# End Source File
# Begin Source File

SOURCE=.\sha.md
# End Source File
# Begin Source File

SOURCE=.\She.md
# End Source File
# Begin Source File

SOURCE=.\Skl1.md
# End Source File
# Begin Source File

SOURCE=.\Skl2.md
# End Source File
# Begin Source File

SOURCE=.\Skl3.md
# End Source File
# Begin Source File

SOURCE=.\Skl4.md
# End Source File
# Begin Source File

SOURCE=.\sp2.md
# End Source File
# Begin Source File

SOURCE=.\spi.md
# End Source File
# Begin Source File

SOURCE=.\Sti.md
# End Source File
# Begin Source File

SOURCE=.\str.md
# End Source File
# Begin Source File

SOURCE=.\strel1.md
# End Source File
# Begin Source File

SOURCE=.\strelec.md
# End Source File
# Begin Source File

SOURCE=.\Sv2.md
# End Source File
# Begin Source File

SOURCE=.\Sve.md
# End Source File
# Begin Source File

SOURCE=.\Svu.md
# End Source File
# Begin Source File

SOURCE=.\Swp.md
# End Source File
# Begin Source File

SOURCE=.\Swr.md
# End Source File
# Begin Source File

SOURCE=.\ta2.md
# End Source File
# Begin Source File

SOURCE=.\tag.md
# End Source File
# Begin Source File

SOURCE=.\Tak.md
# End Source File
# Begin Source File

SOURCE=.\tar.md
# End Source File
# Begin Source File

SOURCE=.\Tat.md
# End Source File
# Begin Source File

SOURCE=.\Tkp.md
# End Source File
# Begin Source File

SOURCE=.\to2.md
# End Source File
# Begin Source File

SOURCE=.\tow.md
# End Source File
# Begin Source File

SOURCE=.\tra.md
# End Source File
# Begin Source File

SOURCE=.\ukd.md
# End Source File
# Begin Source File

SOURCE=.\uks.md
# End Source File
# Begin Source File

SOURCE=.\Vga.md
# End Source File
# Begin Source File

SOURCE=.\Vga2.md
# End Source File
# Begin Source File

SOURCE=.\wakk_kr.md
# End Source File
# Begin Source File

SOURCE=.\wall_ev.md
# End Source File
# Begin Source File

SOURCE=.\wall_kr.md
# End Source File
# Begin Source File

SOURCE=.\wall_ukr.md
# End Source File
# Begin Source File

SOURCE=.\Yah.md
# End Source File
# Begin Source File

SOURCE=.\zom.md
# End Source File
# End Group
# Begin Group "Arc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\gFile.h
# End Source File
# Begin Source File

SOURCE=.\Arc\GSCarch.cpp
# End Source File
# Begin Source File

SOURCE=.\Arc\GSCarch.h
# End Source File
# Begin Source File

SOURCE=.\Arc\GSCset.cpp
# End Source File
# Begin Source File

SOURCE=.\Arc\GSCset.h
# End Source File
# Begin Source File

SOURCE=.\Arc\GSCtypes.h
# End Source File
# Begin Source File

SOURCE=.\GSINC.h
# End Source File
# Begin Source File

SOURCE=.\gText.cpp
# End Source File
# Begin Source File

SOURCE=.\Arc\isiMasks.cpp
# End Source File
# Begin Source File

SOURCE=.\Arc\isiMasks.h
# End Source File
# End Group
# Begin Group "GameSpy"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Chat\chat.h
# End Source File
# Begin Source File

SOURCE=.\CommCore.h
# End Source File
# Begin Source File

SOURCE=.\CEngine\goaceng.h
# End Source File
# Begin Source File

SOURCE=.\MPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\peer.h
# End Source File
# Begin Source File

SOURCE=.\PeerClass.cpp
# End Source File
# Begin Source File

SOURCE=.\PeerClass.h
# End Source File
# Begin Source File

SOURCE=.\Pinger.h
# End Source File
# Begin Source File

SOURCE=.\Peer.lib
# End Source File
# End Group
# Begin Group "AI"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Brigade.cpp
# End Source File
# Begin Source File

SOURCE=.\EinfoClass.cpp
# End Source File
# Begin Source File

SOURCE=.\EinfoClass.h
# End Source File
# Begin Source File

SOURCE=.\Megapolis.cpp
# End Source File
# Begin Source File

SOURCE=.\Megapolis.h
# End Source File
# Begin Source File

SOURCE=.\NewAI.cpp
# End Source File
# Begin Source File

SOURCE=.\NewAI.h
# End Source File
# Begin Source File

SOURCE=.\SafeNet.cpp
# End Source File
# Begin Source File

SOURCE=.\Safety.h
# End Source File
# Begin Source File

SOURCE=.\StrategyResearch.cpp
# ADD CPP /O2
# End Source File
# Begin Source File

SOURCE=.\StrategyResearch.h
# End Source File
# Begin Source File

SOURCE=.\Towers.h
# End Source File
# End Group
# Begin Group "3D Engine"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3DBars.cpp
# End Source File
# Begin Source File

SOURCE=.\3DBars.h
# End Source File
# Begin Source File

SOURCE=.\3DGraph.cpp
# End Source File
# Begin Source File

SOURCE=.\3DGraph.h
# End Source File
# Begin Source File

SOURCE=.\3DMapEd.cpp
# End Source File
# Begin Source File

SOURCE=.\3DMapEd.h
# End Source File
# Begin Source File

SOURCE=.\3DRandMap.cpp
# ADD CPP /O2
# End Source File
# Begin Source File

SOURCE=.\3DRandMap.h
# End Source File
# Begin Source File

SOURCE=.\3DSurf.cpp
# End Source File
# Begin Source File

SOURCE=.\3DSurf.h
# End Source File
# Begin Source File

SOURCE=.\Masks.h
# End Source File
# End Group
# Begin Group "Graphics&DirectX"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ArchTool.cpp
# End Source File
# Begin Source File

SOURCE=.\ArchTool.h
# End Source File
# Begin Source File

SOURCE=.\bmptool.cpp
# End Source File
# Begin Source File

SOURCE=.\bmptool.h
# End Source File
# Begin Source File

SOURCE=.\Curve.h
# End Source File
# Begin Source File

SOURCE=.\Ddini.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialogs.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialogs.h
# End Source File
# Begin Source File

SOURCE=.\DrawForm.h
# End Source File
# Begin Source File

SOURCE=.\DrawForms.cpp
# End Source File
# Begin Source File

SOURCE=.\Fastdraw.cpp
# End Source File
# Begin Source File

SOURCE=.\Fastdraw.h
# End Source File
# Begin Source File

SOURCE=.\fog.cpp
# End Source File
# Begin Source File

SOURCE=.\Fonts.h
# End Source File
# Begin Source File

SOURCE=.\GP_Draw.cpp
# End Source File
# Begin Source File

SOURCE=.\GP_Draw.h
# End Source File
# Begin Source File

SOURCE=.\Graphs.cpp
# End Source File
# Begin Source File

SOURCE=.\Graphs.h
# End Source File
# Begin Source File

SOURCE=.\GVClass.cpp
# End Source File
# Begin Source File

SOURCE=.\Hint.cpp
# End Source File
# Begin Source File

SOURCE=.\Icons.h
# End Source File
# Begin Source File

SOURCE=.\IconTool.cpp
# End Source File
# Begin Source File

SOURCE=.\IconTool.h
# End Source File
# Begin Source File

SOURCE=.\Interface.cpp
# End Source File
# Begin Source File

SOURCE=.\Masks.cpp
# End Source File
# Begin Source File

SOURCE=.\mode.dat
# End Source File
# Begin Source File

SOURCE=.\mouse.h
# End Source File
# Begin Source File

SOURCE=.\Mouse_X.cpp
# End Source File
# Begin Source File

SOURCE=.\MousZone.cpp
# End Source File
# Begin Source File

SOURCE=.\Video.cpp
# End Source File
# Begin Source File

SOURCE=.\Video.h
# End Source File
# Begin Source File

SOURCE=.\VirtScr.cpp
# ADD CPP /O2
# End Source File
# Begin Source File

SOURCE=.\VirtScreen.h
# End Source File
# Begin Source File

SOURCE=.\ZBuffer.cpp
# ADD CPP /O2
# End Source File
# Begin Source File

SOURCE=.\ZBuffer.h
# End Source File
# End Group
# Begin Group "Engine"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Build.cpp
# End Source File
# Begin Source File

SOURCE=.\Ddex1.cpp
# End Source File
# Begin Source File

SOURCE=.\Economy.cpp
# End Source File
# Begin Source File

SOURCE=.\Fractal.cpp
# End Source File
# Begin Source File

SOURCE=.\Groups.cpp
# End Source File
# Begin Source File

SOURCE=.\LoadSave.cpp
# End Source File
# Begin Source File

SOURCE=.\LoadSave.h
# End Source File
# Begin Source File

SOURCE=.\mapa.cpp
# End Source File
# Begin Source File

SOURCE=.\MapDiscr.h
# End Source File
# Begin Source File

SOURCE=.\MapSprites.cpp
# ADD CPP /O2
# End Source File
# Begin Source File

SOURCE=.\MapSprites.h
# End Source File
# Begin Source File

SOURCE=.\Motion.cpp
# End Source File
# Begin Source File

SOURCE=.\MPlayer.h
# End Source File
# Begin Source File

SOURCE=.\Multi.cpp
# End Source File
# Begin Source File

SOURCE=.\Nation.cpp
# End Source File
# Begin Source File

SOURCE=.\Nations.lst
# End Source File
# Begin Source File

SOURCE=.\Nature.cpp
# End Source File
# Begin Source File

SOURCE=.\Nature.h
# End Source File
# Begin Source File

SOURCE=.\NewMon.cpp
# ADD CPP /Zi /O2
# End Source File
# Begin Source File

SOURCE=.\NewMon.h
# End Source File
# Begin Source File

SOURCE=.\NewUpgrade.cpp
# End Source File
# Begin Source File

SOURCE=.\NewUpgrade.h
# End Source File
# Begin Source File

SOURCE=.\OnWater.cpp
# End Source File
# Begin Source File

SOURCE=.\path.cpp
# ADD CPP /O2
# End Source File
# Begin Source File

SOURCE=.\Path.h
# End Source File
# Begin Source File

SOURCE=.\Process.h
# End Source File
# Begin Source File

SOURCE=.\RealWater.cpp
# End Source File
# Begin Source File

SOURCE=.\RealWater.h
# End Source File
# Begin Source File

SOURCE=.\Recorder.cpp
# End Source File
# Begin Source File

SOURCE=.\Recorder.h
# End Source File
# Begin Source File

SOURCE=.\River.cpp
# End Source File
# Begin Source File

SOURCE=.\SaveNewMap.cpp
# End Source File
# Begin Source File

SOURCE=.\Timing.cpp
# End Source File
# Begin Source File

SOURCE=.\TopoGraf.cpp
# ADD CPP /O2
# End Source File
# Begin Source File

SOURCE=.\TopoGraf.h
# End Source File
# Begin Source File

SOURCE=.\Transport.cpp
# End Source File
# Begin Source File

SOURCE=.\Transport.h
# End Source File
# Begin Source File

SOURCE=.\Upgrade.cpp
# End Source File
# Begin Source File

SOURCE=.\Upgrade.h
# End Source File
# Begin Source File

SOURCE=.\walls.cpp
# End Source File
# Begin Source File

SOURCE=.\walls.h
# End Source File
# Begin Source File

SOURCE=.\Weapon.cpp
# ADD CPP /O2
# End Source File
# Begin Source File

SOURCE=.\WeaponID.h
# End Source File
# End Group
# Begin Group "Scenario"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ActiveScenary.cpp
# End Source File
# Begin Source File

SOURCE=.\ActiveScenary.h
# End Source File
# Begin Source File

SOURCE=.\ActiveZone.cpp
# End Source File
# Begin Source File

SOURCE=.\ActiveZone.h
# End Source File
# Begin Source File

SOURCE=.\InteractiveScenario.cpp
# End Source File
# End Group
# Begin Group "Debug"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AntiBug.cpp
# End Source File
# Begin Source File

SOURCE=.\AntiBug.h
# End Source File
# Begin Source File

SOURCE=.\Report.cpp
# End Source File
# Begin Source File

SOURCE=.\UnRar.cpp
# End Source File
# Begin Source File

SOURCE=.\Unrar.h
# End Source File
# Begin Source File

SOURCE=.\UnSyncro.cpp
# End Source File
# Begin Source File

SOURCE=.\UnSyncro.h
# End Source File
# End Group
# Begin Group "Device"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Cdirsnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Cdirsnd.h
# End Source File
# Begin Source File

SOURCE=.\Cwave.cpp
# End Source File
# Begin Source File

SOURCE=.\Cwave.h
# End Source File
# Begin Source File

SOURCE=.\DeviceCD.cpp
# End Source File
# Begin Source File

SOURCE=.\DeviceCD.h
# End Source File
# Begin Source File

SOURCE=.\GameSound.cpp
# End Source File
# Begin Source File

SOURCE=.\GSound.h
# End Source File
# Begin Source File

SOURCE=.\TMixer.cpp
# End Source File
# Begin Source File

SOURCE=.\TMixer.h
# End Source File
# End Group
# Begin Group "LIB"

# PROP Default_Filter "*.lib"
# Begin Source File

SOURCE=.\tntFileIO.lib
# End Source File
# Begin Source File

SOURCE=.\ProTest.lib
# End Source File
# Begin Source File

SOURCE=.\Winmm.lib
# End Source File
# Begin Source File

SOURCE=.\Ddraw.lib
# End Source File
# Begin Source File

SOURCE=.\dsound.lib
# End Source File
# Begin Source File

SOURCE=.\dplayx.lib
# End Source File
# Begin Source File

SOURCE=.\Pinger.lib
# End Source File
# Begin Source File

SOURCE=..\IChat\Debug\ichat.lib
# End Source File
# Begin Source File

SOURCE=..\CommCore.lib
# End Source File
# End Group
# Begin Group "OLD FILES"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Navorots.cpp
# End Source File
# Begin Source File

SOURCE=.\Nuclear.cpp
# End Source File
# Begin Source File

SOURCE=.\protest.h
# End Source File
# Begin Source File

SOURCE=.\Script1.rc
# End Source File
# Begin Source File

SOURCE=.\ScriptHelp.txt
# End Source File
# End Group
# Begin Group "Internet Rating&Profiles"

# PROP Default_Filter ""
# Begin Group "Stats"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\InetRaiting\darray.c
# End Source File
# Begin Source File

SOURCE=.\InetRaiting\darray.h
# End Source File
# Begin Source File

SOURCE=.\InetRaiting\stats\gbucket.c
# End Source File
# Begin Source File

SOURCE=.\InetRaiting\stats\gbucket.h
# End Source File
# Begin Source File

SOURCE=.\InetRaiting\stats\gpersist.h
# End Source File
# Begin Source File

SOURCE=.\InetRaiting\stats\gstats.c
# End Source File
# Begin Source File

SOURCE=.\InetRaiting\stats\gstats.h
# End Source File
# Begin Source File

SOURCE=.\InetRaiting\hashtable.c
# End Source File
# Begin Source File

SOURCE=.\InetRaiting\hashtable.h
# End Source File
# Begin Source File

SOURCE=.\InetRaiting\md5.h
# End Source File
# Begin Source File

SOURCE=.\InetRaiting\md5c.c
# End Source File
# Begin Source File

SOURCE=.\InetRaiting\nonport.c
# End Source File
# Begin Source File

SOURCE=.\InetRaiting\nonport.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\InetRaiting\gp.h
# End Source File
# Begin Source File

SOURCE=.\IR.h
# End Source File
# Begin Source File

SOURCE=.\InetRaiting\IR_Main.cpp
# End Source File
# Begin Source File

SOURCE=.\InetRaiting\GP.lib
# End Source File
# End Group
# Begin Source File

SOURCE=.\ChkInet.cpp
# End Source File
# Begin Source File

SOURCE=.\Const.lst
# End Source File
# Begin Source File

SOURCE=.\ConstStr.cpp
# End Source File
# Begin Source File

SOURCE=.\ConstStr.h
# End Source File
# Begin Source File

SOURCE=.\CTables.h
# End Source File
# Begin Source File

SOURCE=.\Danger.cpp
# End Source File
# Begin Source File

SOURCE=.\ExConst.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtDial.cpp
# End Source File
# Begin Source File

SOURCE=.\HiBars.cpp
# End Source File
# Begin Source File

SOURCE=.\Http\HttpComm.cpp
# End Source File
# Begin Source File

SOURCE=.\Http\HttpComm.h
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\Mine.cpp
# End Source File
# Begin Source File

SOURCE=.\NewILogin.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialogs\NewLogin.h
# End Source File
# Begin Source File

SOURCE=.\Select.cpp
# End Source File
# Begin Source File

SOURCE=.\SelProp.cpp
# End Source File
# Begin Source File

SOURCE=.\ShipTrace.cpp
# End Source File
# Begin Source File

SOURCE=.\Sort.h
# End Source File
# Begin Source File

SOURCE=.\stRecog.cpp
# ADD CPP /Zi
# End Source File
# Begin Source File

SOURCE=.\StringHash.h
# End Source File
# Begin Source File

SOURCE=.\StringsHash.cpp
# End Source File
# Begin Source File

SOURCE=.\tcomp.TXT
# End Source File
# Begin Source File

SOURCE=.\testserver.cpp
# End Source File
# Begin Source File

SOURCE=.\WaveList.lst
# End Source File
# Begin Source File

SOURCE=.\Waves.cpp
# End Source File
# End Target
# End Project
