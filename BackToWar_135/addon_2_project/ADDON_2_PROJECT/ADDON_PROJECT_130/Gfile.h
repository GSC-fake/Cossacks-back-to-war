class GFILE{
	byte Buf[16384];
	int NBytesRead;
	int BufPos;
	int GlobalPos;
	int Size;
	ResFile F;
public:
	FILE* rf;
	bool RealText;
	GFILE();
	~GFILE();
	bool Open(char* Name);
	void Close();
	int ReadByte();
	int CheckByte();
	//standart functions
	int Gscanf(char* Mask,va_list args);
	int Ggetch();
};
#ifndef CEXPORT
#define CEXPORT _declspec(dllexport)
#endif
CEXPORT GFILE* Gopen(char* Name,char* Mode);
CEXPORT int Gscanf(GFILE* F,char* mask,...);
CEXPORT int Ggetch(GFILE* F);
CEXPORT void Gprintf(GFILE* F,const char *format,...);
CEXPORT void Gclose(GFILE* F);