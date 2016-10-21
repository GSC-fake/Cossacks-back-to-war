//#define CHSYN



#ifdef CHSYN
#define MaxUns 2000000
#define maxUline 500000
#else
#define MaxUns 100
#define maxUline 5
#endif
typedef char* lpCHAR;
char* its(int i);
struct RandSlot{
	char* FileName;
	int Line;
	int Param;
	int rpos;
	int Type;
};
class Syncro{
public:
	RandSlot RSL[maxUline];
	int NSlots;
	/*
	char UnsBuf[MaxUns];
	int UnsPos;
	*/
	FILE* Outf;
	/*
	int Lines[maxUline];
	int NLines;
	int GetPlace(int Size);
	void Add0(char* str);
	void Add(char* str);
	void Add(char* str,char* p1);
	void Add(char* str,char* p1,char* p2);
	void Add(char* str,char* p1,char* p2,char* p3);
	void Add(char* str,char* p1,char* p2,char* p3,char* p4);
	void Add(char* str,char* p1,char* p2,char* p3,char* p4,char* p5);
	void Add(char* str,char* p1,char* p2,char* p3,char* p4,char* p5,char* p6);
	void Add(char* str,char* p1,char* p2,char* p3,char* p4,char* p5,char* p6,char* p7);
	void Add(char* str,char* p1,char* p2,char* p3,char* p4,char* p5,char* p6,char* p7,char* p8);
	*/
	void Clear();
	void Save();
	void Copy(Syncro* Syn);
	Syncro();
	~Syncro();
};
extern Syncro SYN;
extern Syncro SYN1;
extern word rpos;
//void addrand(int i);