//sale menu
#include <sdk_tplus.h>
#include "Menu.h"
#include <stdlib.h>
#include "appel.h"
#include "emv.h"
//maximum length of object


int saleMenuDisplay(void){

	char inputAmount[50] = "0000.00";

	memset(inputAmount, 0, sizeof(inputAmount));

	float amtConv = 0.00;

	ulong entry;
	int ret;

	//currency
	char curr[4] = "KSH";

	//============================================
	//display a dialog that will prompt user to enter amount
	entry = GL_Dialog_Amount(mGoal, "AMOUNT", "Enter amount :", "/d,/d/d/D./D/D", inputAmount, sizeof(inputAmount), curr, GL_ALIGN_LEFT, GL_TIME_MINUTE);
	CHECK((entry != GL_KEY_CANCEL) && (entry != GL_RESULT_INACTIVITY) , cancelled);
	//=============================================
	//will check if it is null and throw an exception
	if(strlen(inputAmount) == NULL){
		entry = GL_Dialog_Message(mGoal, "AMOUNT","AMOUNT CANNOT BE NULL!!!" , GL_ICON_ERROR, GL_BUTTON_NONE, 1000);
		return EXIT_SUCCESS;
	}
	//=============================================
	//it will check if the input amount is greater that 5000
	//and if it is greater it will throw an exception
	sscanf(inputAmount, "%f", &amtConv);
	if((amtConv/100) > 5000.00 || (amtConv/100) == 5000.00){
		entry = GL_Dialog_Message(mGoal, "AMOUNT","AMOUNT MORE THAN LIMIT!!!" , GL_ICON_ERROR, GL_BUTTON_NONE, 1000);
		return EXIT_SUCCESS;
			}
	//============================================
	//prompt the user to insert card
	else {
		entry = GL_Dialog_Message(mGoal, "AMOUNT","INSERT/SWIPE CARD" , GL_ICON_INFORMATION, GL_BUTTON_NONE, 1000);
		saleMenuPassword();
		return EXIT_SUCCESS;
					}
	if(ret == -1){
			goto cancelled;
		}
		//check if the GL_key_cancel has been hit and if it has been hit it will cancel
		cancelled:
		GL_Dialog_Message(mGoal, NULL, "CANCELLED!!", GL_ICON_ERROR, GL_BUTTON_NONE, 2 * GL_TIME_SECOND);
		return -1;

	return EXIT_SUCCESS;
}
int saleMenuPassword(void){
	char password[100];
	char pmask[256] = "/d/d/d/d";
	ulong entry;
	int ret;
	memset(password, 0, sizeof(password));

	//display a dialog that will prompt user to enter password
//	smartCard();
	entry = GL_Dialog_Password(mGoal, "PASSWORD", "Enter Password :", pmask, password, sizeof(password), GL_TIME_MINUTE);
	CHECK((entry != GL_KEY_CANCEL) && (entry != GL_RESULT_INACTIVITY) , cancelled);

		if (strlen(password) == NULL) {
			Beep(0x09,0x03,5,BEEP_ON|BEEP_WAIT|BEEP_OFF);
			Beep(0x08,0x03,5,BEEP_ON|BEEP_WAIT|BEEP_OFF);
			Beep(0x09,0x03,5,BEEP_ON|BEEP_WAIT|BEEP_OFF);
			Beep(0x08,0x03,5,BEEP_ON|BEEP_WAIT|BEEP_OFF);

			entry = GL_Dialog_Message(mGoal, "PASSWORD"," PASSWORD CANNOT BE NULL!" , GL_ICON_ERROR, GL_BUTTON_NONE, 1000);
		return EXIT_SUCCESS;
			}
		else if (strlen(password) < 4) {
			entry = GL_Dialog_Message(mGoal, "PASSWORD","PASSWORD MUST BE \n EQUAL TO FOUR DIGITS!!" , GL_ICON_ERROR, GL_BUTTON_NONE, 1000);
		return EXIT_SUCCESS;
			}
		else{
			entry = GL_Dialog_Message(mGoal, "PASSWORD","VALIDATING PASSWORD!" , GL_ICON_INFORMATION, GL_BUTTON_NONE, 2 * 1000);
			return EXIT_SUCCESS;
		}

		if(ret == -1){
			goto cancelled;
		}
		cancelled:
		GL_Dialog_Message(mGoal, NULL, "PASSWORD CANCELLED!!", GL_ICON_ERROR, GL_BUTTON_NONE, 2 * GL_TIME_SECOND);
		return -1;

	return EXIT_SUCCESS;
}



