
#include "DShowPlay.h"

  HWND      ghApp;
  HINSTANCE ghInst;
  HMENU     ghMenu;

  LONG      evCode;
  LONG      evParam1;
  LONG      evParam2;

  PDShowPlay StartFile (LPCSTR lpszFileName, HWND hNotifyWnd)
    { 
	  HRESULT		hr;
      WCHAR			wFile[MAX_PATH];
	  PDShowPlay	pDSP=NULL;

	  pDSP = new TDShowPlay;

	  CoInitialize(NULL);

	  pDSP->pif=NULL;
	  pDSP->pigb=NULL;
	  pDSP->pimc=NULL;
	  pDSP->pimex=NULL;
	  pDSP->pivw=NULL;
	  strcpy(pDSP->szFileName,lpszFileName);
	  pDSP->hNotifyWnd=hNotifyWnd;

      MultiByteToWideChar( CP_ACP, 0, pDSP->szFileName, -1, wFile, MAX_PATH );

      hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&pDSP->pigb);

      if (SUCCEEDED(hr))

      { 
        pDSP->pigb->QueryInterface(IID_IMediaControl, (void **)&pDSP->pimc);
        pDSP->pigb->QueryInterface(IID_IMediaEventEx, (void **)&pDSP->pimex);
        pDSP->pigb->QueryInterface(IID_IVideoWindow, (void **)&pDSP->pivw);

        hr = pDSP->pigb->RenderFile(wFile, NULL);

		pDSP->pivw->put_FullScreenMode(OATRUE);
		pDSP->pivw->put_AutoShow(OATRUE);

        pDSP->pimex->SetNotifyWindow((OAHWND)pDSP->hNotifyWnd, WM_GRAPHNOTIFY, 0);

        if (SUCCEEDED(hr))
          pDSP->pimc->Run();

		return pDSP;
      }
	  else
		  {
				delete pDSP;
				pDSP=NULL;
				return NULL;
		  };
    }


  BOOL StopFile(PDShowPlay pDSP)
	  {
          if (pDSP->pimc)
           pDSP->pimc->Stop();

          if (pDSP->pivw)
           pDSP->pivw->put_Visible(OAFALSE);

		  HELPER_RELEASE(pDSP->pivw);
          HELPER_RELEASE(pDSP->pif);
          HELPER_RELEASE(pDSP->pigb);
          HELPER_RELEASE(pDSP->pimc);
          HELPER_RELEASE(pDSP->pimex);

		  delete pDSP;

		  pDSP=NULL;

		  CoUninitialize();

		  return TRUE;
	  }


// Add to your message map
/*
  HRESULT   hr;
  LONG      evCode;
  LONG      evParam1;
  LONG      evParam2;
..................................

          case WM_GRAPHNOTIFY:

			  while (SUCCEEDED(pDSP->pimex->GetEvent(&evCode, &evParam1, &evParam2, 0)))

              {
                hr = pDSP->pimex->FreeEventParams(evCode, evParam1, evParam2);

                if ((EC_COMPLETE == evCode) || (EC_USERABORT == evCode))
					StopFile(pDSP);
              
              } 

 */