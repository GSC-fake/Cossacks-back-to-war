#include <windows.h>
#include <stdlib.h>
#include "Hash.h"
typedef unsigned char byte;

LocalHash::LocalHash(){
	NItems=0;
	MaxItems=0;
	Items=NULL;
};

void LocalHash::Clear(){
	if(Items)free(Items);
	Items=NULL;
	NItems=0;
	MaxItems=0;
};
void LocalHash::AddToHash(LocalHashItem* Item){
	if(NItems>=MaxItems){
		NItems+=16;
		Items=(LocalHashItem*)realloc(Items,MaxItems*sizeof LocalHashItem);
	};
	Items[NItems]=*Item;
	NItems++;
};
void LocalHash::Delete(char* ID){
	for(int i=0;i<NItems;i++)if(!strcmp(Items[i].ID,ID)){
		if(i<NItems-1)memcpy(Items+i,Items+i+1,(NItems-i-1)*sizeof LocalHashItem);
		NItems--;
		i--;
	};
};
LocalHash::~LocalHash(){
	Clear();
};
byte CalculateHashValue(char* S){
	byte s=0;
	int L=strlen(S);
	for(int i=0;i<L;i++)s+=S[i];
	return s;
};
void GlobalHash::AddToHash(char* ID,char* Message,DWORD Value){
	byte v=CalculateHashValue(ID);
	LocalHashItem HI;
	HI.ID=new char[strlen(ID)+1];
	strcpy(HI.ID,ID);
	HI.Message=new char[strlen(Message)+1];
	strcpy(HI.Message,Message);
	HI.Value=Value;
	Hash[v].AddToHash(&HI);
	GlobalList.AddToHash(&HI);
};
bool GlobalHash::GetHashItem(char* ID,LocalHashItem** Item){
	byte v=CalculateHashValue(ID);
	int N=Hash[v].NItems;
	LocalHashItem* LIST=Hash[v].Items;
	for(int i=0;i<N;i++)if(!strcmp(LIST[i].ID,ID)){
		*Item=LIST+i;
		return true;
	};
	*Item=NULL;
	return false;
};
int GlobalHash::FindItem(char* ID,int StartIndex,LocalHashItem** Item){
	int N=GlobalList.NItems;
	LocalHashItem* LIST=GlobalList.Items;
	for(int i=StartIndex;i<N;i++)if(!strcmp(LIST[i].ID,ID)){
		*Item=LIST+i;
		return i+1;
	};
	*Item=NULL;
	return -1;
};
void GlobalHash::Clear(){
	for(int i=0;i<GlobalList.NItems;i++){
		free(GlobalList.Items[i].ID);
		free(GlobalList.Items[i].Message);
	};
	GlobalList.Clear();
	for(i=0;i<256;i++)Hash[i].Clear();
};
GlobalHash::GlobalHash(){

};
GlobalHash::~GlobalHash(){
	Clear();
};