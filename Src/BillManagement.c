//bill management menu
#include <sdk_tplus.h>
#include <stdlib.h>
#include "Menu.h"

//maximum length of object
int billingAmount(void);
//sizeDate
static const char szDate[] = "Date:%.2s/%.2s/%.2s  %.2s:%.2s\n";
//billing menu number
int billMenuDisplay(void){

	char billNo[50] = "0000000";

	memset(billNo, 0, sizeof(billNo));

	ulong entry;

	//Return
	int ret;

	lblBill:
	entry = GL_Dialog_Text(mGoal, NULL, "Enter Bill :", "/d/d/d/d/d/d/d/d", billNo, sizeof(billNo) - 1, GL_TIME_MINUTE);
	CHECK((entry != GL_KEY_CANCEL) && (entry != GL_RESULT_INACTIVITY) , cancelled);
	//control flow of my bill validation number input
	//===============================================
	//checks where the bill is null and will throw an error if it will be null
	if(strlen(billNo) == NULL){
		entry = GL_Dialog_Message(mGoal, "BILL NUMBER","BILL NUMBER CANNOT BE NULL!!!" , GL_ICON_ERROR, GL_BUTTON_NONE, 1000);
		goto lblBill;
		}
	//===============================================
	//gave my bill number an input size on integer = 6
	//hence will validate if the length f the bill number
	//is less than 6 and throw an exception
	else if (strlen(billNo) < 5){

		 Beep(0x09,0x03,5,BEEP_ON|BEEP_WAIT|BEEP_OFF);
		 Beep(0x08,0x03,5,BEEP_ON|BEEP_WAIT|BEEP_OFF);
		 Beep(0x09,0x03,5,BEEP_ON|BEEP_WAIT|BEEP_OFF);
		 Beep(0x08,0x03,5,BEEP_ON|BEEP_WAIT|BEEP_OFF);
		 Beep(0x09,0x03,5,BEEP_ON|BEEP_WAIT|BEEP_OFF);
		 Beep(0x08,0x03,5,BEEP_ON|BEEP_WAIT|BEEP_OFF);

		entry = GL_Dialog_Message(mGoal, "BILL NUMBER","Bill NO TO SMALL!!!" , GL_ICON_ERROR, GL_BUTTON_NONE, 1000);
		goto lblBill;
		}
	//=================================================
	//will through a validating message if the bill number will be equal to 6
	//============================================
	//will check if the bill is not null and range = 6 if its not
	//it will call the billMenuPassword() function
	//to prompt the user to insert a password
	else{
		entry = GL_Dialog_Message(mGoal, "BILL NUMBER PROCESSING","VALIDATING BILL NUMBER!" , GL_ICON_INFORMATION, GL_BUTTON_NONE, 2 * 1000);
		billingAmount();
		return EXIT_SUCCESS;
		}

	if(ret == -1){
		goto cancelled;
	}
	//check if the GL_key_cancel has been hit and if it has been hit it will cancel
	cancelled:
	GL_Dialog_Message(mGoal, NULL, "BILL NUMBER CANCLLED!!", GL_ICON_ERROR, GL_BUTTON_NONE, 2 * GL_TIME_SECOND);
	return -1;
}
//billing amount
int billingAmount(void){
	//currency
	char curr[4] = "KSH";
	char amount[100] = "00000000000";
	memset(amount, 0, sizeof(amount));

	float billAmount;
	sscanf(amount, "%f", &billAmount);

	ulong entry;
	int ret;

	lblBillAmount:
	entry = GL_Dialog_Amount(mGoal, "AMOUNT", "Enter amount :", "/d/d/d,/d/d/D./D/D", amount, sizeof(amount) - 5, curr, GL_ALIGN_LEFT, GL_TIME_MINUTE);
	CHECK((entry != GL_KEY_CANCEL) && (entry != GL_RESULT_INACTIVITY) , cancelled);

		if(strlen(amount) == NULL){
				entry = GL_Dialog_Message(mGoal, "AMOUNT","AMOUNT CANNOT BE NULL!!!" , GL_ICON_ERROR, GL_BUTTON_NONE, 1000);
				goto lblBillAmount;
			}
			//============================================
		else if (strlen(amount) != NULL){
			entry = GL_Dialog_Message(mGoal, "BILL NUMBER PROCESSING", "VALIDATING TRANSACTION!" , GL_ICON_INFORMATION, GL_BUTTON_NONE, 2 * 1000);
			return EXIT_SUCCESS;
		}
		else{
			  Telium_Date_t date;
			  Telium_File_t *hPrinter;
			  hPrinter = Telium_Fopen("PRINTER", "w-*"); // Open printer driver
				     if (hPrinter != NULL)
				     {
				         Telium_Pprintf("**********BILL AMOUNT**********\n");
				         Telium_Read_date(&date); // Print date and time
				         Telium_Pprintf(szDate, date.day, date.month, date.year, date.hour, date.minute);
				         Telium_Pprintf("Bill Amount: %s\n", amount);
				         Telium_Pprintf("Bill No: %s\n"); //cardDetails);
				         Telium_Ttestall(PRINTER, 0);

				         Telium_Fclose(hPrinter); // Close printer driver
		}
		//check if the transaction is cancelled
			if(ret == -1){
					goto cancelled;
				}
				//check if the GL_key_cancel has been hit and if it has been hit it will cancel
				cancelled:
				GL_Dialog_Message(mGoal, NULL, "CANCELLED!!", GL_ICON_ERROR, GL_BUTTON_NONE, 2 * GL_TIME_SECOND);
//				billMenuDisplay();
				return -1;
		}
}
