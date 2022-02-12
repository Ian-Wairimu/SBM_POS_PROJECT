//cashBack menu
#include <sdk_tplus.h>
#include "Menu.h"
#include <stdlib.h>
#include "appel.h"


int cashBackAmt(void);

int cashBackMenuDisplay(void){
	ulong entry;
	int ret;
	char amount[50] = "00000";
	//currency
	char curr[4] = "KSH";
	float amtConv = 0.00;
	sscanf(amount, "%f", &amtConv);

	memset(amount, 0, sizeof(amount));

	lblAmount:
	entry = GL_Dialog_Amount(mGoal, NULL, "Enter Amount :", "/d/d/d/D./D/D", amount, sizeof(amount), curr, GL_ALIGN_LEFT, GL_TIME_MINUTE);
	CHECK((entry != GL_KEY_CANCEL) && (entry != GL_RESULT_INACTIVITY) , cancelled);
	if(strlen(amount) == NULL){
			entry = GL_Dialog_Message(mGoal, "AMOUNT","AMOUNT CANNOT BE NULL!!!" , GL_ICON_ERROR, GL_BUTTON_NONE, 1000);
			goto lblAmount;
	}
		//=============================================
		//it will check if the input amount is greater that 5000
		//and if it is greater it will throw an exception
		if(amtConv > 5000.00){
			entry = GL_Dialog_Message(mGoal, "AMOUNT","AMOUNT MORE THAN LIMIT!!!" , GL_ICON_ERROR, GL_BUTTON_NONE, 1000);
			goto lblAmount;
		}
		//============================================
				//prompt the user to insert card
		else {
			cashBackAmt();
//			entry = GL_Dialog_Message(mGoal, "AMOUNT","INSERT/SWIPE CARD" , GL_ICON_INFORMATION, GL_BUTTON_NONE, 1000);
			return EXIT_SUCCESS;
				}
	if(ret == -1){
		goto cancelled;
		}
		cancelled:
		GL_Dialog_Message(mGoal, NULL, "CANCELLED!!", GL_ICON_ERROR, GL_BUTTON_NONE, 2 * GL_TIME_SECOND);
		return -1;

	return EXIT_SUCCESS;
}
int cashBackAmt(void){
	ulong entry;
	int ret;
	char cash[100] = "000000";
	char curr[4] = "KSH";

	memset(cash, 0, sizeof(cash));

	lblCashBack:
	entry = GL_Dialog_Amount(mGoal, NULL, "Enter CashBack Amount :", "/d/d/d/d/d/D./D/D", cash, sizeof(cash), curr, GL_ALIGN_LEFT, GL_TIME_MINUTE);
	CHECK((entry != GL_KEY_CANCEL) && (entry != GL_RESULT_INACTIVITY) , cancelled);
	if(strlen(cash) == NULL){
		entry = GL_Dialog_Message(mGoal, "AMOUNT","AMOUNT CANNOT BE NULL!!!" , GL_ICON_ERROR, GL_BUTTON_NONE, 1000);
		goto lblCashBack;
		}
	else {
		entry = GL_Dialog_Message(mGoal, "AMOUNT","INSERT/SWIPE CARD" , GL_ICON_INFORMATION, GL_BUTTON_NONE, 1000);
		saleMenuPassword();
		return EXIT_SUCCESS;
	}
	if(ret == -1){
		goto cancelled;
		}
		cancelled:
		GL_Dialog_Message(mGoal, NULL, "CANCELLED!!", GL_ICON_ERROR, GL_BUTTON_NONE, 2 * GL_TIME_SECOND);
		return -1;
	return EXIT_SUCCESS;
}
