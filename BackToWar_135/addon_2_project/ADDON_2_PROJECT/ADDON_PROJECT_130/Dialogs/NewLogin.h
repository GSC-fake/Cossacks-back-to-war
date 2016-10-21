bool ProcessMessages();
bool ProcessNewInternetLogin(){
	DialogsSystem DSS(0,0);

	SQPicture Back("Interface\\Background_Wizard.bmp");

	LocalGP WBT("Interface\\LogWizard");
	LocalGP BTNS("Interface\\Login");
	DSS.addPicture(NULL,0,0,&Back,&Back,&Back);
	/*
	LocalGP BOR2("Interface\\Bor2");
	DSS.ProcessDialogs();
	DSS.RefreshView();
	DarkScreen();
	DarkScreen();
	ShowCentralMessage(GetTextByID("LOADING"),BOR2.GPID);
	*/
	
	char REQ[1024];
	char REQ1[1024];
	char DATA[512]="";
	ResFile F=RReset("Internet\\Cash\\login.cmd");
	if(F!=INVALID_HANDLE_VALUE){
		int sz=RFileSize(F);
		if(sz>511)sz=511;
		RBlockRead(F,REQ1,sz);
		REQ1[sz]=0;
		RClose(F);
	}else return false;
	F=RReset("Internet\\Cash\\LGDTA.LOG");
	if(F!=INVALID_HANDLE_VALUE){
		int sz=RFileSize(F);
		if(sz>511)sz=511;
		RBlockRead(F,DATA,sz);
		DATA[sz]=0;
		RClose(F);
	};
	sprintf(REQ,REQ1,DATA);
	//sprintf(REQ,"GW|LW_new|LW_file&Internet/cml/log.cml");
	//sprintf(REQ,"LF|LW_new|LW_file&req.txt");
	RunExplorer(2,REQ,0,0,1024,768);
	ItemChoose=-1;
	if(SetAccessKey){
		for(int i=0;i<8;i++)SetAccessKey(i,"");
	};
	char* AKEY="";
	ACCESS[0]=0;
	bool pal=0;
	int t0=GetTickCount();
	do{
		ProcessMessages();
		DSS.ProcessDialogs();
		ProcessExplorer(2);
		DSS.RefreshView();
		if(GetAccessKey)AKEY=GetAccessKey(2);
		if(!pal){
			SlowLoadPalette("2\\agew_1.pal");
			pal=1;
		};
		//if(t0&&GetTickCount()-t0>4000){
		//	t0=0;
		//	ExplorerOpenRef(2,"LF|LW_tbl&RTYEWQ&26&uuu&ttt&0&0&jhgjhgjh&1&1&ghfhgfhgf&2&2&jhgjhgjhg&ghqfghfd&jhgjhgjh&jkgnbcnbvc&uuiuyi&jhggjh&ghfhgfhgf&uuu&ttt&jhgjhgjhg&ghqfghfd&jhgjhgjh&jkgnbcnbvc&uuiuyi&jhggjh&ghfhgfhgf&uuu&ttt&jhgjhgjhg&ghqfghfd&jhgjhgjh&jkgnbcnbvc&uuiuyi&jhggjh&ghfhgfhgf&uuu&ttt&jhgjhgjhg&ghqfghfd&jhgjhgjh&jkgnbcnbvc&uuiuyi&jhggjh&ghfhgfhgf&uuu&ttt&jhgjhgjhg&ghqfghfd&jhgjhgjh&jkgnbcnbvc&uuiuyi&jhggjh&ghfhgfhgf&uuu&ttt&jhgjhgjhg&ghqfghfd&jhgjhgjh&jkgnbcnbvc&uuiuyi&jhggjh&ghfhgfhgf&uuu&ttt&jhgjhgjhg&ghqfghfd&jhgjhgjh&jkgnbcnbvc&uuiuyi&jhggjh&ghfhgfhgf&uuu&ttt&jhgjhgjhg&ghqfghfd&jhgjhgjh&jkgnbcnbvc&uuiuyi&jhggjh&ghfhgfhgf&uuu&ttt&jhgjhgjhg&ghqfghfd&jhgjhgjh&jkgnbcnbvc&uuiuyi&jhggjh&ghfhgfhgf&uuu&ttt&jhgjhgjhg&ghqfghfd&jhgjhgjh&jkgnbcnbvc&uuiuyi&jhggjh&ghfhgfhgf&uuu&ttt&jhgjhgjhg&ghqfghfd&jhgjhgjh&jkgnbcnbvc&uuiuyi&jhggjh&ghfhgfhgf&uuu&ttt&jhgjhgjhg&ghqfghfd&jhgjhgjh&jkgnbcnbvc&uuiuyi&jhggjh&ghfhgfhgf&uuu&ttt&jhgjhgjhg&ghqfghfd&jhgjhgjh&jkgnbcnbvc&uuiuyi&jhggjh&ghfhgfhgf&uuu&ttt&jhgjhgjhg&ghqfghfd&jhgjhgjh&jkgnbcnbvc&uuiuyi&jhggjh&ghfhgfhgf&uuu&ttt&jhgjhgjhg&ghqfghfd&jhgjhgjh&jkgnbcnbvc&uuiuyi&jhggjh&ghfhgfhgf&uuu&ttt&jhgjhgjhg&ghqfghfd&jhgjhgjh&jkgnbcnbvc&uuiuyi&jhggjh&ghfhgfhgf&uuu&ttt&jhgjhgjhg&ghqfghfd&jhgjhgjh&jkgnbcnbvc&uuiuyi&jhggjh&ghfhgfhgf&uuu&ttt&jhgjhgjhg&ghqfghfd&jhgjhgjh&jkgnbcnbvc&uuiuyi&jhggjh&ghfhgfhgf&uuu&ttt&jhgjhgjhg&ghqfghfd&jhgjhgjh&jkgnbcnbvc&uuiuyi&jhggjh&ghfhgfhgf&uuu&ttt&jhgjhgjhg&ghqfghfd&jhgjhgjh&jkgnbcnbvc&uuiuyi&jhggjh&ghfhgfhgf&uuu&ttt&jhgjhgjhg&ghqfghfd&jhgjhgjh&jkgnbcnbvc&uuiuyi&jhggjh&ghfhgfhgf");
		//};
	}while(ItemChoose==-1&&AKEY[0]==0);
	if(!strcmp(AKEY,"#CANCEL"))AKEY[0]=0;
	if(SetAccessKey){
		for(int i=0;i<8;i++)SetAccessKey(i,AKEY);
	};
	strcpy(ACCESS,AKEY);

	DSS.ProcessDialogs();
	ProcessExplorer(2);
	DSS.RefreshView();

	return AKEY[0]!=0;
};