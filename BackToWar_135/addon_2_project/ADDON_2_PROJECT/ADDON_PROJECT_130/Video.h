extern MCIDEVICEID wAVIDeviceID;
extern MCIDEVICEID wMIDDeviceID;
void PlayAVI(HWND hwnd,LPCSTR mfile,int Top);
void PlayMIDI (HWND hwnd,LPCSTR mfile);
void CloseAVI (HWND hwnd);
void CloseMIDI(HWND hwnd);
LPSTR GetCDROMWithFile(LPSTR FN);