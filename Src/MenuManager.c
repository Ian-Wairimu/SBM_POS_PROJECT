#include <sdk_tplus.h>

int Application_Request_Data(char * Narration, word KeySaveLocation, int lenField, char * mask){
	int amt = 0;
	int i = 0;
	char exponent[4];
	char dataEntered[100];
	char tcMask[200];
	char currencyLabel[3 + 1] ;
	const char entryMask[] = "/d/d/d,/d/d/d,/d/d/D";
	const char entryMask1[] = "/d/d/d,/d/d/d,/d/d/D./D";
	const char entryMask2[] = "/d/d/d,/d/d/d,/d/d/D./D/D";
	const char PercentMask[] = "/d/D./D/D";
	card Exp = 0;

	memset(currencyLabel, 0, sizeof(currencyLabel));
	memset(dataEntered, 0, sizeof(dataEntered));
	memset(exponent, 0, sizeof(exponent));
	memset(tcMask, 0, sizeof(tcMask));

	for (i=0; i<(lenField + 1); i++)
		strcat(tcMask, mask);


	if (KeySaveLocation == appBillerSurcharge) {
		memset(currencyLabel, 0, sizeof(currencyLabel));
		strcpy(currencyLabel,"%");
		ret = GL_Dialog_Amount(hGoal, NULL, Narration, PercentMask, dataEntered, sizeof(dataEntered) - 1, currencyLabel, GL_ALIGN_RIGHT, 2 * GL_TIME_MINUTE);
	} else if ((KeySaveLocation != traAmt) && (KeySaveLocation != traOtherAmt) && (KeySaveLocation != traCashbackAmt) && (KeySaveLocation != traDepositAmt)) {
		ret = GL_Dialog_Text(hGoal, "", Narration, tcMask, dataEntered, sizeof(dataEntered), GL_TIME_MINUTE);
	} else {
		switch (Exp) {
		case 1:
			ret = GL_Dialog_Amount(hGoal, "ENTER AMOUNT", Narration, entryMask1, dataEntered, sizeof(dataEntered) - 1, currencyLabel, GL_ALIGN_RIGHT, 2 * GL_TIME_MINUTE);
			break;
		case 2:
			ret = GL_Dialog_Amount(hGoal, "ENTER AMOUNT", Narration, entryMask2, dataEntered, sizeof(dataEntered) - 1, currencyLabel, GL_ALIGN_RIGHT, 2 * GL_TIME_MINUTE);
			break;
		default:
			ret = GL_Dialog_Amount(hGoal,"ENTER AMOUNT", Narration, entryMask, dataEntered, sizeof(dataEntered) - 1, currencyLabel, GL_ALIGN_RIGHT, 2 * GL_TIME_MINUTE);
			break;
		}
		if (!ret) {
			goto lblKO;
		}
	}

	ret = strlen(dataEntered);

	mapPut(KeySaveLocation, dataEntered, ret );

	lblKO:
	return ret;
}
