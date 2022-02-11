#include <sdk_tplus.h>
#include "emv.h"
#include "Menu.h"


void EMV_UI_MessageInsertCard(void){
	EMV_UI_Open();
	GL_Dialog_Message(mGoal, "AMOUNT","AMOUNT CANNOT BE NULL!!!" , GL_ICON_ERROR, GL_BUTTON_NONE, 1000);
	EMV_UI_Close();
}
void EMV_UI_MessageRemoveCard(void){
	EMV_UI_Open();
	GL_Dialog_Message(mGoal, "AMOUNT","AMOUNT CANNOT BE NULL!!!" , GL_ICON_ERROR, GL_BUTTON_NONE, 1000);
	EMV_UI_Close();

}
void EMV_UI_MessageNoRemainingPin(void){
	EMV_UI_Open();
	GL_Dialog_Message(mGoal, "AMOUNT","AMOUNT CANNOT BE NULL!!!" , GL_ICON_ERROR, GL_BUTTON_NONE, 1000);
	EMV_UI_Close();

}
void EMV_UI_MessagePleaseWait(void){
	EMV_UI_Open();
	GL_Dialog_Message(mGoal, "AMOUNT","AMOUNT CANNOT BE NULL!!!" , GL_ICON_ERROR, GL_BUTTON_NONE, 1000);
	EMV_UI_Close();

}
void EMV_UI_MessageWrongPin(void){
	EMV_UI_Open();
	GL_Dialog_Message(mGoal, "AMOUNT","AMOUNT CANNOT BE NULL!!!" , GL_ICON_ERROR, GL_BUTTON_NONE, 1000);
	EMV_UI_Close();

}
