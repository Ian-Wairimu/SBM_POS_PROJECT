#include <sdk_tplus.h>
#include "Menu.h"
#include "emv.h"

static T_GL_HGRAPHIC_LIB __EMV_UI_goalHandle;
static Telium_File_t *__EMV_UI_displayDriver;
static Telium_File_t *__EMV_UI_keyboardDriver;
static Telium_File_t *__EMV_UI_touchDriver;


//T_GL_HGRAPHIC_LIB EMV_UI_Handle(void)
//{
//	if (__EMV_UI_goalHandle == NULL)
//	{
//		__EMV_UI_goalHandle = GL_GraphicLib_Create();
//	}
//
//	return __EMV_UI_goalHandle;

void EMV_UI_Destroy(void)
{
	if (__EMV_UI_goalHandle != NULL) {
		GL_GraphicLib_Destroy(__EMV_UI_goalHandle);
		__EMV_UI_goalHandle = NULL;
	}
}

void EMV_UI_Open(void)
{
	if (__EMV_UI_displayDriver == NULL)
		__EMV_UI_displayDriver = Telium_Fopen("DISPLAY", "w*");
	if (__EMV_UI_keyboardDriver == NULL)
		__EMV_UI_keyboardDriver = Telium_Fopen("KEYBOARD", "r*");
	if (__EMV_UI_touchDriver == NULL)
		__EMV_UI_touchDriver = Telium_Fopen("TSCREEN", "r*");
}

//! \brief Close the GOAL interface (close drivers ...).
void EMV_UI_Close(void)
{
	if (__EMV_UI_displayDriver != NULL)
	{
		Telium_Fclose(__EMV_UI_displayDriver);
		__EMV_UI_displayDriver = NULL;
	}
	if (__EMV_UI_keyboardDriver != NULL)
	{
		Telium_Fclose(__EMV_UI_keyboardDriver);
		__EMV_UI_keyboardDriver = NULL;
	}
	if (__EMV_UI_touchDriver != NULL)
	{
		Telium_Fclose(__EMV_UI_touchDriver);
		__EMV_UI_touchDriver = NULL;
	}
}
