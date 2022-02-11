//#include <sdk_tplus.h>
//#include <stdlib.h>
//#include "Menu.h"
//#include "appel.h"
//#include "emv.h"
//
//void smartCard(void){
//	//SmartCard
//	Telium_File_t *smc;
//	//insert Return
//	int iKey, iRet, iCt, iLen, iSta;
//	T_GL_HWIDGET screen;
//	T_GL_HWIDGET document;
//	HISTORIC atr;
//	char display[51]; //display
//	char print[1000]; //print
//	byte snd[262]; //send
//	byte rsp[262]; //response
//	char *pcMsg;
//	byte p;  // Printer line index
//
//	smc = Telium_Fopen("printer", "card");
//	pcMsg = "checking error!";
//
//		EMV_UI_MessageInsertCard();
//
//		iSta = Telium_Ttestall(CAM0, 10);
//		if(iSta != 0)
//
//		//ikey will use the check function
//
//		iLen=0;
//		iRet = Telium_EMV_power_on(smc, &atr);
//
//}
